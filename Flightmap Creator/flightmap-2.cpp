// Implementation file for FlightMapClass class


#include "flightmap.h"
#include "type.h"
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stack>
#include <iterator>
using namespace std;

// implement the methods of the flightMap class here
 
 // default constructor
 FlightMapClass::FlightMapClass()
 {
 }

// destructor
FlightMapClass::~FlightMapClass()
{
    delete[] FlightMap;
}

// copy constructor
FlightMapClass::FlightMapClass(const FlightMapClass & f)
{
    FlightMap = new list<flightRec>;
    num_cities = f.num_cities;
    cities = f.cities;
    *FlightMap = *(f.FlightMap);
}

// function for reading in the cities.dat file
void FlightMapClass::ReadCities(ifstream& cities_file)
{
    string city;  // variable for storing a string

    cities_file >> num_cities;  // reads in total number of cities in file
    num_cities += 1;

    // for loop that reads file until fully read
    for(int i = 0; i < num_cities; i++){

        getline(cities_file, city);  // reads a city
        cities.push_back(city);  // pushes city back into the vector of cities
    }

    sort(cities.begin(), cities.end());  // sorts vector of cities in alphabetical order
}

// this function reads information from a list of flight information and builds the flight map
void FlightMapClass::BuildMap(ifstream& flight_file)
{
    // variables, structs, and list
    int flightNum, price, index;
    string origin, destination;
    flightRec flight;
    FlightMap = new list<flightRec>[num_cities];  // initialize the flight map as an array of lists, dynamically allocates space
    vector<flightRec> flights;  // temporary vector for reading in information
    
    while(flight_file >> flightNum >> origin >> destination >> price){
        // reads in the flights.dat file
        flight.flightNum = flightNum;
        flight.origin = origin;
        flight.destination = destination;
        flight.price = price;

        // pushes the struct to the back of vector
        flights.push_back(flight);
        flight_file.ignore(100, '\n');  // ignores certain characters
    }

    // loop for adding the flights in vector to the origin city in the flight map
    for(auto& flight:flights){
        // finds index for the origin city in each struct and adds flight to the flight map
        index = find(cities.begin(), cities.end(), flight.origin) - cities.begin();
        FlightMap[index].push_back(flight);  // pushes the flight back into the list

    }
    for(int i = 0; i < num_cities; i++){
        FlightMap[i].sort();
    }
    
}

// new functions
// this function checks if a city is within the cities that BlueSky Airline serves
bool FlightMapClass::CheckCity(string cityname) const
{
    // for loop for finding the city in an array
    for(int i = 0; i < num_cities; i++){
        if(cityname == cities[i]){
            return true;  // returns true if city is in the array
        }
    }
    return false;  // returns false if city is not in the array
}

// this function displays the header for the flight information of one sequence path; did not use it for displaying all cities
void FlightMapClass::DisplayAllCities() const
{
    cout << "Flight# " << setw(5) << "From" << setw(15) << "To" << setw(18) << "Cost" << endl;
}

// this function marks a city as visited
void FlightMapClass::MarkVisited(int city)
{
    visited.insert(visited.begin() + city + 1, true);  // inserts true into the vector
    visited.erase(visited.begin() + city);  // erases the number before the inserted number so vector is always at a constant size
    
}

// this function clears marks on all cities
void FlightMapClass::UnvisitAll()
{
    // checks if cities array is not empty then erases entire visited vector
    if(!cities.empty()){
        visited.assign(num_cities, false);
    }
}

// this function checks if a city has been visited or not
bool FlightMapClass::IsVisited(int city) const
{
    // checks within the visited vector to see if city is visited or not
    if(visited.at(city)){
        return true;
    } else {
        return false;
    }
    
}

// this function determines if the next adjacent city is unvisited
bool FlightMapClass::GetNextCity(string fromCity, string &nextCity)
{
    // loop to check entire array of cities for the origin city index
    for(int i = 0; i < num_cities; i++){
        auto it = FlightMap[i].begin();  // iterator points at the origin city index in FlightMap list

        // checks if the iterator is pointing at the origin city
        if(it->origin == fromCity){
            // checks if the next city is unvisited and returns true if it is
            if(IsVisited(GetCityNumber(nextCity)) == false){
                return true;  // returns true
            }
        }
    }
    return false;  // returns false if otherwise
}

// this function gets the city number index of a given city
int FlightMapClass::GetCityNumber(string cityName) const
{
    // loop goes through entire cities array   
    for(int i = 0; i < num_cities; i++){
        // checks if city name matches the index
        if(cityName == cities[i]){
            return i;  //returns index of city
        }
    }
    
    return 0;  //returns nothing if it doesn't exist (this is only here to make the function work)
}

// this function gets the city name destination of a given index
string FlightMapClass::GetCityName(int cityNumber) const
{
    auto it = FlightMap[cityNumber].begin();  // iterator points towards the index in flightmap list
    return it->destination;  // returns the destination name

    
}

// this function determines if there is a sequence of flights between two cities and displays them
void FlightMapClass::FindPath(string originCity, string destinationCity)
{
    // variables, stacks
    stack<string> aStack;
    stack<string> temp;  // temporary stack used for displaying stack info
    string topCity, nextCity, newCity;
    bool success;
    int cityNum = GetCityNumber(originCity);
    int total = 0;
    int price, flightNum=0;

    UnvisitAll();  // calls function to empty out the visited vector
    // pushes the first city into the stack and gets the destination city name
    aStack.push(originCity);
    nextCity = GetCityName(cityNum);
    MarkVisited(cityNum);  // marks the first city as visited
    topCity = aStack.top();  // points toward the top of the stack

    // Displays header for initial sequence
    cout << "Request is to fly from " << originCity << " to " << destinationCity << ".\n";
    // checks if the origin or destination city exists
    if(!CheckCity(originCity) || !CheckCity(destinationCity)){
        // displays an invalid message and ends the findpath function
        if(!CheckCity(originCity)){
            cout << "Sorry, BlueSky airline does not serve " << originCity << ".\n" << endl;
        } else if (!CheckCity(destinationCity)){
            cout << "Sorry, BlueSky airline does not serve " << destinationCity << ".\n" << endl;
        }
        return;
    }
    
    // loop to determine the sequence of flights
    while(!aStack.empty() && (topCity != destinationCity)){

        // iterator loop to find if the destination city is within the destinations of the first city
        for(auto it = FlightMap[GetCityNumber(topCity)].begin(); it != FlightMap[GetCityNumber(topCity)].end(); it++){
            // checks if it is within the origin city and displays accordingly
            if(it->destination == destinationCity && it->origin == originCity){
                cout << "Bluesky airline serves between these two cities.\n" << "The flight itinerary is: " << endl;
                DisplayAllCities();
                cout << it->flightNum << left << setw(10 - (to_string(flightNum)).length()) << "" << setw(5) << it->origin << setw(6) << "" << setw(10) << it->destination << right << setw(7) << '$' << it->price << endl;
                cout << setw(43) << "Total: $" << it->price << '\n' << endl;
                return;  // ends the findpath function
            }
        }
        // determines if the next city is unvisited
        success = GetNextCity(topCity, nextCity);
        if(!success){
            aStack.pop();
            // checks to see if the stack is empty and displays no flight itinerary
            if(aStack.empty()){
                cout << "Bluesky airline does not fly from " << originCity << " to " << destinationCity << ".\n" << endl;
                break;  // ends loop
            }
        } else {  // pushes the next city into stack if found unvisited and mark visited
            aStack.push(nextCity);
            MarkVisited(GetCityNumber(nextCity));
        }
        topCity = aStack.top();  // gets info from top of stack
        int topCityNum = GetCityNumber(topCity);

        // iterator loop to get the next city and makes sure that it does not revisit a city
        auto it = FlightMap[topCityNum].begin();
        if(topCity != destinationCity){
            while(it != FlightMap[topCityNum].end() && IsVisited(GetCityNumber(it->destination))){
                
                advance(it, 1);  // increments iterator by one until it finds a unvisited city
            
            }
        }
        
        nextCity = it->destination;
        
    }
    // reverses the stack by pushing all content into another stack
    if(!aStack.empty()){
        while(!aStack.empty()){
            topCity = aStack.top();
            aStack.pop();
            temp.push(topCity);
        }
        // display header for a flight itinerary
        cout << "Bluesky airline serves between these two cities.\n" << "The flight itinerary is: \n";
        DisplayAllCities();
        
        // loop for displaying the flight itinerary
        while(!temp.empty()){
            topCity = temp.top();
            temp.pop();
            // checks if stack is empty
            if(!temp.empty()){
                newCity = temp.top();
            } else {
                // outputs the total cost of flight itinerary and ends
                cout << setw(43) << "Total: $" << total << '\n' << endl;
                return;
            }

            price = GetPrice(topCity, newCity);
            total += price;
            flightNum = GetFlightNum(topCity);
            // displays one flight sequence in itinerary
            cout << left << flightNum << setw(9 - (to_string(flightNum)).length()) <<  "" << setw(5) << topCity << setw(17 - topCity.length()) << "" << setw(16) << newCity << right << '$' << price << endl;
            
        }
    }

}

// this function gets the flight number of a given city
int FlightMapClass::GetFlightNum(string cityName) const
{
    auto it = FlightMap[GetCityNumber(cityName)].begin();
    return it->flightNum;
}

// this function gets the price of a given city
int FlightMapClass::GetPrice(string cityName, string newCity) const
{
    for(auto it = FlightMap[GetCityNumber(cityName)].begin(); it != FlightMap[GetCityNumber(cityName)].end(); it++){
        if(it->destination == newCity){
            return it->price;
        }
    }
    return 0;
}


// friend function for displaying the flight information in a formatted table
ostream& operator << (ostream & os, const FlightMapClass & f)
{
    // Header for the table
    os << setw(13) << "Origin: " << setw(25) << "Destination" << setw(10) << "Flight" << setw(9) << "Price\n" << "===========================================================" << endl;

    // for loop of sorting all flights inside a list in alphabetical order
    for(int i = 0; i < f.num_cities; i++){
        f.FlightMap[i].sort();  // sorts the linked list of nodes

        // checks if the end has been reached and the first input of cities.dat is skipped then runs
        if(i != f.num_cities && i != 0){ 
            os << "From " << f.cities[i] << " to: ";  // displays the origin city

            // checks if the origin city does not have any flights and displays accordingly
            if(f.FlightMap[i].size() == 0 && i != 0){
                os << setw(23 - f.cities[i].length()) << "Empty\n";  // displays no flight

            }
        }

        // for loop iterator starting at the beginning of the flight map and ending at the end
        for(auto it = f.FlightMap[i].begin(); it != f.FlightMap[i].end(); it++){
            
            // checks if first destination city was outputted
            if(it != f.FlightMap[i].begin()){
                // formatted output for any destination cities after the first city
                os << left << setw(27) << "" << setw(16) << it->destination << setw(8) << it->flightNum << right << '$' << it->price << endl;

            } else {
                // formatted output for the first destination city
                os << setw(17 - f.cities[i].length()) << "" << left << setw(16) << it->destination  << setw(4) << it->flightNum << right << setw(5) << '$' << it->price << endl;

            }
        }
    }
    return os;
}