#include "Flight.h"
//#include "MenuBox.cpp"

string findSeatMapOfFlight(Flight&);

vector<Flight> FlightList;
Flight::Flight(string flight_id, int airline_brand_id, int economy_price, int business_price, string departure_time, string arrival_time, string departure_destination, string arrival_destination) {
    this->flight_id = flight_id;
    this->airline_brand_id = airline_brand_id;
    this->economy_price = economy_price;
    this->business_price = business_price;
    this->departure_time = departure_time;
    this->arrival_time = arrival_time;
    this->departure_destination = departure_destination;
    this->arrival_destination = arrival_destination;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 5; j++) {
            this->seatMap[i][j] = false;
        }
    }
    currentFile = findSeatMapOfFlight(*this);
}

void Flight::Display_Flight() {
    // cout << flight_id << " | " << airline_brand_id << " | " << economy_price << " | " << business_price << " | " << departure_time  << " | " << arrival_time << " | " << departure_destination << " | " << arrival_destination << endl;
    cout << "|" << setw(9) << right << flight_id
             << setw(15) << right << airline_brand_id
             << setw(19) << right << economy_price
             << setw(19) << right << business_price
             << setw(17) << right << departure_time
             << setw(19) << right << arrival_time
             << setw(20) << right << departure_destination
             << setw(15) << right << arrival_destination
             << "|" << endl;
}
void Flight::Create_Flight() {

}

void Read_Flights() {
	ifstream file("flights.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            int i = 0;
            string info[8];
            string delimiters = ";|,."; 
            size_t start = 0;  
            size_t end; 
            while ((end = line.find_first_of(delimiters, start)) != string::npos) {
                string segment = line.substr(start, end - start);
                if (!segment.empty()) {
                    info[i] = segment;
                    i++;
                }
                start = end + 1;  
            }
            if (start < line.length()) {
                string segment = line.substr(start);
                if (!segment.empty()) {
                    info[i] = segment;
                    i++;
                }
            }
            if (i == 8) {  
                string flight_id = (info[0]);
                int airline_brand_id = stoi(info[1]);
                int economy_price = stoi(info[2]);
                int business_price = stoi(info[3]);
                string departure_time = (info[4]);
                string arrival_time = (info[5]); 
                FlightList.push_back(Flight(flight_id, airline_brand_id, economy_price, business_price, departure_time, arrival_time, info[6], info[7])); 
                //FlightList.back().Display_Flight();
            } //else {
            	//cout << "Scanning failed, please check for wrong inputs" << endl;
//}
        }
        file.close();
        //selectFlights();
    } else {
        cout << "Unable to open file" << endl;
    }
}

string readFightId(const string& filename) {
    ifstream file(filename);
    string line;
    if (file.is_open()) { 
        getline(file, line);
        file.close();
    } else {
        cout << "Unable to open the file." << endl;
    }
    return line;
}

void setupNewSeatMap(const string& filename, const Flight& flight) {
    ofstream file(filename, ios::out);
    if (file.is_open()) {
        file << flight.getFlightID() << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                file << flight.seatMap[i][j] << " ";  
            }
            file << endl;  
        }
        file.close(); 
    } else {
        cout << "Unable to open the file." << endl;
    }
}

void getSeatMap(const string& filename, Flight& flight) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        int row = 0; 
        getline(file, line);  
        while (getline(file, line) && row < rows) {
            stringstream ss(line);
            int col = 0;
            bool value;
            while (ss >> value && col < cols) {
                flight.seatMap[row][col] = value;   
                col++;
            }
            row++;
        } 
        file.close();
    } else {
        cout << "Unable to open the file." << endl;
    }
}

string findSeatMapOfFlight(Flight& flight) {
    const int fileCount = 20;  // Number of files to check
    string filename;
    bool found = false;
    string emptyFile;

    // Step 1: Check each file for the flight ID
    for (int i = 1; i <= fileCount; i++) {
        filename = "SEATMAPS/seatmap" + to_string(i) + ".txt";  // Assuming filenames are file1.txt, file2.txt, etc.
        
        // Try to read the flight ID from the current file
        string idInFile = readFightId(filename);
        
        // Check if the file is empty
        if (idInFile.empty()) {
            // Store the first empty file if we find one
            if (emptyFile.empty()) {
                emptyFile = filename;
            }
        } else if (idInFile == flight.getFlightID()) {
            // Step 2: If the flight ID is found, load the seat map and return the filename
            getSeatMap(filename, flight);  // Load the seat map into the flight object
            return filename;               // Return the filename where the flight ID was found
        }
    }

    // Step 3: If flight ID is not found in any file, use the first empty file if available
    if (!emptyFile.empty()) {
        setupNewSeatMap(emptyFile, flight);  // Write the flight's seat map to the empty file
        return emptyFile;                    // Return the empty file used to store the new seat map
    } else {
        cout << "No available empty files to store the seat map." << endl;
        return "";  // Indicate no empty file was available
    }
}

// string Flight::getFlightID() const{
//    return flight_id; 
// }
// int Flight::getAirlineBrandID() const{ 
//    return airline_brand_id; 
// }
// int Flight::getEconomyPrice() const{ 
//    return economy_price; 
// }
// int Flight::getBusinessPrice() const{ 
//    return business_price; 
// }

// string Flight::getDepartureTime() const{ 
//    return departure_time; 
// }

// string Flight::getArrivalTime() const{ 
//    return arrival_time; 
// }

// string Flight::getDepartureDestination() const{ 
//     return departure_destination; 
// }

// string Flight::getArrivalDestination() const{ 
//     return arrival_destination; 
// }      
