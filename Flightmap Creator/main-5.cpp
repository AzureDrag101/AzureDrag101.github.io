//Author: Kosy Okafor
/* This program creates flight paths based on the request file*/
//Late Pass #1: Taking care of brother and many tests this week
#include <iostream>
#include <fstream>
#include <cassert>
#include "flightmap.h"
#include "type.h"

using namespace std;

int main() {
    FlightMapClass Map;
    ifstream c_file;
    ifstream f_file;
    ifstream request_file;

    c_file.open("cities.dat");  // opens cities.dat file
    assert(c_file);  // checks if file is opened correctly

    f_file.open("flight.dat");  // opens flights.dat file
    assert(f_file);  // checks if file is opened correctly

    Map.ReadCities(c_file);  // calls function to read cities.dat file
    Map.BuildMap(f_file);  // calls function to read and build the flight map with information from flights.dat file


    // Display all flight information
    cout << Map << endl;

    // Process flight requests from the requests.dat file
    string originCity, destinationCity;
    request_file.open("request.dat"); 
    assert(request_file);
    while (request_file >> originCity >> destinationCity) {
        Map.FindPath(originCity, destinationCity);
    }

    c_file.close();
    f_file.close();
    request_file.close();
    return 0;
}
