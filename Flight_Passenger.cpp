#include "Flight_Passenger.h"

Flight_Passenger::Flight_Passenger() {
    
}

Flight_Passenger::Flight_Passenger(string flight_id, string passenger_name, string dob, string seat_number, 
                                   int seat_class, int ticket_price, string departure_time, 
                                   string arrival_time, string departure_destination, string arrival_destination) 
    // : ticket_id(ticket_id), flight_id(flight_id), passenger_name(passenger_name), dob(dob), seat_number(seat_number),
    //   seat_class(seat_class), economy_price(economy_price), business_price(business_price), 
    //   departure_time(departure_time), arrival_time(arrival_time), departure_destination(departure_destination), 
    //   arrival_destination(arrival_destination) {}
{
    this->flight_id = flight_id;
    this->passenger_name = passenger_name;
    this->dob = dob;
    this->seat_number = seat_number;
    this->seat_class = seat_class;
    this->ticket_price = ticket_price;
    this->departure_time = departure_time;
    this->arrival_time = arrival_time;
    this->departure_destination = departure_destination;
    this->arrival_destination = arrival_destination;
    this->ticket_id = flight_id + "-" + seat_number;
}


void Read_Passenger() {
    
}