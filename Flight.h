#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
const int rows = 10;
const int cols = 5;

class Flight {
public:
    string flight_id;
    int airline_brand_id;
    int economy_price;
    int business_price;
    string departure_time;
    string arrival_time;
    string departure_destination;
    string arrival_destination;
    bool seatMap[rows][cols];
    string currentFile;
    
    Flight(string flight_id, int airline_brand_id, int economy_price, int business_price, 
           string departure_time, string arrival_time, string departure_destination, string arrival_destination) ;
        //    : flight_id(flight_id), airline_brand_id(airline_brand_id), economy_price(economy_price), 
        //      business_price(business_price), departure_time(departure_time), arrival_time(arrival_time), 
        //      departure_destination(departure_destination), arrival_destination(arrival_destination) {} 

    string getFlightID() const { return flight_id; }
    int getAirlineBrandID() const { return airline_brand_id; }
    int getEconomyPrice() const { return economy_price; }
    int getBusinessPrice() const { return business_price; }
    string getDepartureTime() const { return departure_time; }
    string getArrivalTime() const { return arrival_time; }
    string getDepartureDestination() const { return departure_destination; }
    string getArrivalDestination() const { return arrival_destination; }      
    void Display_Flight();
    void Create_Flight();
    //void Read_Flights();
};

#endif
