# Welcome to Cweather, a simple weather API program!

## 🧠 Cweather taught me...
* How to handle API requests in C
* How to safely handle data fetched from the internet to avoid buffer overflows
* How to use the libcurl and cJSON libraries in C

## What does Cweather do?
**Cweather** is a super simple weather program that tells you the current temperature and wind speed of the given city. Example output for the program:
```text
--- Weather Data for 'Helsinki' ---

Temperature: 21.40°C, it's warm outside 🌡️
Wind Speed:  18.00 km/h, it's breezy outside 🍃

------------------------------------
```

## How to get and use Cweather
1. Clone this git repo or download the source code zip file
2. Navigate to the project's root and run the command `make`
3. Then you can run `./cweather [city]` where city can be any city in the world of your choosing.
**NOTE:** The program can also handle cities whose names contain spaces like "New York", "Los Angeles", or "Buenos Aires", just put the name parts in order after the command `./cweather`

When you want to clean the workspace, run `make clean` and all .o files will be deleted along with the executable "cweather"
