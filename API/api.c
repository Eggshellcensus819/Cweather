#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

struct responseBuff {
    char *string;
    size_t size;
};

size_t got_data(void *buffer, size_t size, size_t nmemb, void *userp) {
    size_t fullsize = size * nmemb;
    struct responseBuff *rbuff = (struct responseBuff *)userp;

    char *ptr = realloc(rbuff->string, rbuff->size + fullsize + 1);

    if (ptr == NULL) {
        fprintf(stderr, "realloc failed in got_data.\n");
        exit(1);
    }

    rbuff->string = ptr;
    memcpy(&(rbuff->string[rbuff->size]), buffer, fullsize);
    rbuff->size += fullsize;
    rbuff->string[rbuff->size] = '\0';

    return fullsize;
}

void craftCoordinateRequest(char *_for, char *buffer) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Curl initialisation failed while trying to craft API request.\n");
        exit(1);
    }

    /* Automatically formats cities with spaces, like "New York" correctly for the request */
    char *formatted_city = curl_easy_escape(curl, _for, 0);

    char template[256] = "";
    strncat(template, "https://geocoding-api.open-meteo.com/v1/search?name=", sizeof(template) - strlen(template) - 1);
    strncat(template, formatted_city, sizeof(template) - strlen(template) - 1);

    /* Here we check if the end part of the API request would still fit into the string */
    if (strlen(template) >= 248) { 
        fprintf(stderr, "City name takes too much space from the API request.\n");
        curl_free(formatted_city);
        curl_easy_cleanup(curl);
        exit(1);
    }

    strncat(template, "&count=1", sizeof(template) - strlen(template) - 1);
    strncpy(buffer, template, 256);
    buffer[255] = '\0';

    curl_free(formatted_city);
    curl_easy_cleanup(curl);
}

char* makeRequest(char *URL) {
    CURL *curl = curl_easy_init();

    if (!curl) {
        fprintf(stderr, "Curl initialisation failed while trying to get city coordinates/weather data.\n");
        return NULL;
    }

    struct responseBuff chunk;
    chunk.string = malloc(1);
    chunk.size = 0;
    
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, URL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, got_data);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Fetching coordinates/weather data failed.\n");
            free(chunk.string);
            curl_easy_cleanup(curl);
            return NULL;
        }
    }

    return chunk.string;
}