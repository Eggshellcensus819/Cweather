#ifndef JSON
#define JSON

/* Parses the JSON containing the coordinates for a city and writes that data to the longitude and latitude floats */
void parseCoordinates(float *longitude, float *latitude, char *coordinateJSON);
/* Parses the city weather data from the given JSON and writes the temperature and windspeed to the two float arguments */
void parseWeatherData(float *temp, float *wspeed, char *weatherDataJSON);

#endif