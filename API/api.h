#ifndef API
#define API

/* This is for the libcurl library */
size_t got_data(char *buffer, size_t itemsize, size_t nitems, void *ignorethis);

/* Crafts an API request to get the city's coordinates in a JSON from open-meteo */
void craftCoordinateRequest(char *_for, char *buffer);
/* Takes a correctly formatted URL and returns a pointer to the JSON string containing the cíty coordinates or weather data
   Returns NULL on failure */
char* makeRequest(char *URL);

#endif