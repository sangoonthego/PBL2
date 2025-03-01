#include <windows.h>
#include <cctype>
#include "Account.cpp"
#include "Flight_Passenger.cpp"
#include "Flight.cpp"
#include "Airline_Brands.cpp"
//#include "Seat_Map.cpp"
void logIn();

vector<string> cities;

void readCities() {
    ifstream file("cities.txt"); 
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) { // Ensure no empty lines are added
                cities.push_back(line);
            }
        }
        file.close(); 
    } else {
        cerr << "Unable to open file 'cities.txt'" << endl; 
    }
}

int returnRole() {
    system("cls");
    cout << endl << endl;
    ifstream file("vietbay.txt"); 
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl; 
        }
        file.close(); 
    } else {
        cout << "Unable to open file" << endl; 
    }
    cout << endl << setw(75) << "Welcome To VietBay, please log-in" << endl; 
	bool valid = false;
	while (!valid) {
		string inputUsername;
	    string inputPassword;
	    cout << endl << setw(58)<< "Username: ";
	    cin >> inputUsername;
	    cout << setw(58) << "Password: ";
	    char ch;
	    while ((ch = _getch()) != 13) {
	        if (ch == 8) { 
	            if (!inputPassword.empty()) {
	                inputPassword.erase(inputPassword.size() - 1); 
	                cout << "\b \b";
	            }
	        } else {
	            inputPassword.push_back(ch);
	            cout << '*'; 
	        }
	    }
	    for (int i = 0; i < AccountList.size(); i++) {
	    	if (inputUsername == AccountList[i].getUserName() && inputPassword == AccountList[i].getPassWord()) {
	    		cout << endl << setw(67) << "Log-in successfully" << endl;
	    		valid = true;
                AccountList[i].Welcome();
	    		return AccountList[i].getRole();
			}
		}
		cout << endl << setw(85) << "Invalid username or password, please enter again" << endl;	
	}
    return -1;
}

void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

string toLowerCase(string str) {
   transform(str.begin(), str.end(), str.begin(), ::tolower);  
   return str;
}

string toUpperCase(string str) {
   transform(str.begin(), str.end(), str.begin(), ::toupper);  
   return str;
}

string trim(const string &s) {
    auto start = s.begin();
    while (start != s.end() && isspace(*start)) {
        start++;
    }

    auto end = s.end();
    do {
        end--;
    } while (distance(start, end) > 0 && isspace(*end));

    return string(start, end + 1);
}

string capitalizeFirstLetter(const string& str) {
    string result;
    toLowerCase(result);
    bool newWord = true;
    for (size_t i = 0; i < str.length(); ++i) {
        if (isalpha(str[i]) && newWord) {
            result += toupper(str[i]);
            newWord = false;
        } else if (isalpha(str[i])) {
            result += str[i];
        } else if (isspace(str[i])) {
            if (!newWord) {
                result += ' ';
                newWord = true;
            }
        }
    }
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    return result;
}

int checkInput(string s){
	if(s.empty()) return -1;
	for(char c:s){
		if(!isdigit(c)) 
        return -1;
	}
	if(s == "") 
        return -1;
	else if (s.length() > 2) 
        return -1;
	else return stoi(s);
}

bool isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12 || day < 1 || year < 1) return false;
    
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    // Leap year check for February
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        daysInMonth[1] = 29;
    }
    
    return day <= daysInMonth[month - 1];
}

void formatDate(string& input) {
    // Keep looping until valid input is entered
    while (true) {
        // Ask for user input
        cout << "Enter date of birth (DDMMYYYY), example 30122024 : ";
        getline(cin, input);

        // Validate the length of the input
        if (input.size() != 8) {
            cout << "Invalid date format. Please enter the date in DDMMYYYY format.\n";
            continue;  // Continue the loop if the format is incorrect
        }

        // Extract day, month, and year from the input string
        int day = stoi(input.substr(0, 2));
        int month = stoi(input.substr(2, 2));
        int year = stoi(input.substr(4, 4));

        // Check if the date is valid
        if (!isValidDate(day, month, year)) {
            cout << "Invalid date. Please check the day, month, and year values.\n";
            continue;  // Continue the loop if the date is invalid
        }

        input = to_string(day) + "-" + to_string(month) + "-" + to_string(year);
        break;  // Exit the loop once the date is valid
    }
}

// void formatDate(string& input) {
//     while (true) {
//         if (input.size() != 8) {
//             cout << "Invalid date format. Please enter the date in DDMMYYYY format.\n";
//             return;
//         }

//         int day = stoi(input.substr(0, 2));
//         int month = stoi(input.substr(2, 2));
//         int year = stoi(input.substr(4, 4));
        
//         if (!isValidDate(day, month, year)) {
//             cout << "Invalid date. Please check the day, month, and year values.\n";
//             return;
//         }
//     }

    
//     // input = to_string(day) + "-" + to_string(month) + "-" + to_string(year);
// }

void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// void inputPassengerInfo(Flight_Passenger &passenger) {
//     string name;
//     string dob;
//     cout << "Enter passenger's name: ";
//     getline(cin, name);
//     cout << "Enter date of birth (DDMMYYYY): ";
//     getline(cin, dob);

//     passenger.setPassengerName(name);
//     passenger.setDob(dob);
// }

void inputPassengerInfo(Flight_Passenger &passenger) {
    string name, dob;
    int seatNumber;
    cout << "Enter passenger name: ";
    getline(cin, name);
    name = capitalizeFirstLetter(name);
    passenger.setPassengerName(name);
    
    // cout << "Enter date of birth (DDMMYYYY), example 30122024 : ";
    // getline(cin, dob);
    formatDate(dob);
    passenger.setDob(dob);
}


void printTicket(const Flight_Passenger &passenger) {
    cout << "-------------------------------------" << endl;
    cout << "             FLIGHT TICKET           " << endl;
    cout << "-------------------------------------" << endl;
    cout << "Ticket ID      : " << passenger.getTicketID() << endl;
    cout << "Flight ID      : " << passenger.getFlightID() << endl;
    cout << "Passenger Name : " << passenger.getPassengerName() << endl;
    cout << "Date of Birth  : " << passenger.getDob() << endl;
    cout << "Seat Number    : " << passenger.getSeatNumber() << endl;
    cout << "Seat Class     : " << (passenger.getSeatClass() == 0 ? "Economy" : "Business") << endl;
    cout << "Departure Time : " << passenger.getDepartureTime() << endl;
    cout << "Arrival Time   : " << passenger.getArrivalTime() << endl;
    cout << "Departure Dest : " << passenger.getDepartureDestination() << endl;
    cout << "Arrival Dest   : " << passenger.getArrivalDestination() << endl;
    cout << "-------------------------------------" << endl;
}

void saveTicketToFile(const Flight_Passenger &passenger) {
    ofstream file("ticket.txt", ios::app); 

    if (file.is_open()) {
        file << "Ticket ID      : " << passenger.getTicketID() << endl;
        file << "Flight ID      : " << passenger.getFlightID() << endl;
        file << "Passenger Name : " << passenger.getPassengerName() << endl;
        file << "Date of Birth  : " << passenger.getDob() << endl;
        file << "Seat Number    : " << passenger.getSeatNumber() << endl;
        file << "Seat Class     : " << (passenger.getSeatClass() == 0 ? "Economy" : "Business") << endl;
        file << "Departure Time : " << passenger.getDepartureTime() << endl;
        file << "Arrival Time   : " << passenger.getArrivalTime() << endl;
        file << "Departure Dest : " << passenger.getDepartureDestination() << endl;
        file << "Arrival Dest   : " << passenger.getArrivalDestination() << endl;
        file << "-------------------------------------";
        
        file.close();
        cout << "Ticket saved successfully.\n";
    } else {
        cout << "Error opening file for writing.\n";
    }
}

string getSeatLabel(int row, int col) {
    char colLetter = 'A' + col;  // Convert 0-based column to letter (A, B, C, etc.)
    int rowNumber = row + 1;     // Convert 0-based row to 1-based row (1, 2, 3, etc.)
    return string(1, colLetter) + to_string(rowNumber);
}



void displayCell(int row, int col, int startX, int startY, bool isSelected, bool isBooked) {
    int x = startX + col * 4;  // Calculate x position for the cell
    int y = startY + row;      // Calculate y position for the cell

    setCursorPosition(x, y);
    if (isSelected && isBooked) {
        setColor(10);            
        cout << "[";         
        setColor(7); 
        cout << "X";
        setColor(10);  
        cout << "] ";
        setColor(7);    
    } else if (isSelected) {
        setColor(10);            // Highlight color for the selected cell
        cout << "[";             // Display selected cell with indicator
        setCursorPosition(x + 2, y);
        cout << "] ";
        setColor(7);             // Reset to default color
    }  else if (isBooked) { 
        cout << "[X] ";          // Display a booked cell with 'X'
    } else { 
        cout << "[";             // Display opening bracket for unbooked cell
        setCursorPosition(x + 2, y);
        cout << "] ";
    }
}

void displaySeatGrid(int startX, int startY, int flightIndex) {
    // Print column labels (A, B, C, ...)
    setCursorPosition(startX - 3, startY - 1);
    cout << "   ";  // Indent to align with row labels
    for (int col = 0; col < cols; col++) {
        cout << " " << static_cast<char>('A' + col) << "  ";
    }
    cout << endl;

    // Print rows with row labels (1, 2, 3, ...)
    for (int row = 0; row < rows; row++) {
        setCursorPosition(startX - 4, startY + row);  // Move to the start of the row
        cout << setw(2) << (row + 1) << " ";          // Print row label
        cout << endl;
    }
}

void seatCursorSelect(int startX, int startY, int flightIndex, Flight_Passenger& passenger) {
    int currentRow = 0;   
    int currentCol = 0; 
    int prevRow = currentRow, prevCol = currentCol;
    bool selected = false;

    // Initial display of all seats
    displaySeatGrid(startX, startY, flightIndex);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            displayCell(i, j, startX, startY, (i == currentRow && j == currentCol), FlightList[flightIndex].seatMap[i][j]);
        }
    }

    while (!selected) {
        char ch = _getch(); 
        prevRow = currentRow;
        prevCol = currentCol;

        switch (ch) {
            case 72: // Up arrow key
                if (currentRow > 0) currentRow--;
                break;
            case 80: // Down arrow key
                if (currentRow < rows - 1) currentRow++;
                break;
            case 75: // Left arrow key
                if (currentCol > 0) currentCol--;
                break;
            case 77: // Right arrow key
                if (currentCol < cols - 1) currentCol++;
                break;
            case 13: // Enter key (attempt to select)
                if (FlightList[flightIndex].seatMap[currentRow][currentCol] == true) {
                    // Seat is already booked, prompt the user to select a different seat
                    setCursorPosition(55, startY + rows + 2);   
                    cout << "Seat (" << currentRow + 1 << ", " << currentCol + 1 << ") is already booked. Please choose another seat." << endl;
                } else {
                    FlightList[flightIndex].seatMap[currentRow][currentCol] = true;
                    setupNewSeatMap(FlightList[flightIndex].currentFile, FlightList[flightIndex]);
                    // Seat is available, confirm the selection
                    selected = true;
                }
                break;
            default:
                break;
        } 

        // Update the display if the cursor has moved to a new cell
        if (prevRow != currentRow || prevCol != currentCol) {
            displayCell(prevRow, prevCol, startX, startY, false, FlightList[flightIndex].seatMap[prevRow][prevCol]); 
            displayCell(currentRow, currentCol, startX, startY, true, FlightList[flightIndex].seatMap[currentRow][currentCol]);
        }
    }
    
    // Confirm the selected seat
    setCursorPosition(55, startY + rows + 2);  
    cout << "                                                                               ";
    setCursorPosition(72, startY + rows + 2);   
    cout << "You selected seat " << getSeatLabel(currentRow, currentCol) << endl;
    passenger.setSeatNumber(getSeatLabel(currentRow, currentCol));
}



// Function to display a seat cell
// void displayCell(int row, int col, int startX, int startY, bool isSelected, bool isBooked) {
//     int x = startX + col * 4;  // Calculate x position for the cell
//     int y = startY + row;      // Calculate y position for the cell

//     setCursorPosition(x, y);
//     if (isSelected && isBooked) {
//         setColor(10);            
//         cout << "[";         
//         setColor(7); 
//         cout << "X";
//         setColor(10);  
//         cout << "] ";
//         setColor(7);    
//     } else if (isSelected) {
//         setColor(10);            // Highlight color for the selected cell
//         cout << "[";             // Display selected cell with indicator
//         setCursorPosition(x + 2, y);
//         cout << "] ";
//         setColor(7);             // Reset to default color
//     } else if (isBooked) { 
//         cout << "[X] ";          // Display a booked cell with 'X'
//     } else { 
//         cout << "[";             // Display opening bracket for unbooked cell
//         setCursorPosition(x + 2, y);
//         cout << "] ";
//     }
// }

// Function to display the seat grid with row and column labels


// void seatCursorSelect(int startX, int startY, int flightIndex, Flight_Passenger& passenger) {
//     int currentRow = 0;   
//     int currentCol = 0; 
//     int prevRow = currentRow, prevCol = currentCol;
//     bool selected = false;

//     // Initial display of all seats with labels
//     displaySeatGrid(startX, startY, flightIndex);

//     while (!selected) {
//         char ch = _getch(); 
//         prevRow = currentRow;
//         prevCol = currentCol;

//         switch (ch) {
//             case 72: // Up arrow key
//                 if (currentRow > 0) currentRow--;
//                 break;
//             case 80: // Down arrow key
//                 if (currentRow < rows - 1) currentRow++;
//                 break;
//             case 75: // Left arrow key
//                 if (currentCol > 0) currentCol--;
//                 break;
//             case 77: // Right arrow key
//                 if (currentCol < cols - 1) currentCol++;
//                 break;
//             case 13: // Enter key (attempt to select)
//                 if (FlightList[flightIndex].seatMap[currentRow][currentCol] == true) {
//                     // Seat is already booked, prompt the user to select a different seat
//                     setCursorPosition(55, startY + rows + 2);   
//                     cout << "Seat " << getSeatLabel(currentRow, currentCol) << " is already booked. Please choose another seat." << endl;
//                 } else {
//                     FlightList[flightIndex].seatMap[currentRow][currentCol] = true;
//                     setupNewSeatMap(FlightList[flightIndex].currentFile, FlightList[flightIndex]);
//                     // Seat is available, confirm the selection
//                     selected = true;
//                 }
//                 break;
//             default:
//                 break;
//         } 

//         // Update the display if the cursor has moved to a new cell
//         if (prevRow != currentRow || prevCol != currentCol) {
//             displayCell(prevRow, prevCol, startX, startY, false, FlightList[flightIndex].seatMap[prevRow][prevCol]); 
//             displayCell(currentRow, currentCol, startX, startY, true, FlightList[flightIndex].seatMap[currentRow][currentCol]);
//         }
//     }
    
//     // Confirm the selected seat
//     setCursorPosition(55, startY + rows + 2);  
//     cout << "                                                                               ";
//     setCursorPosition(72, startY + rows + 2);   
//     cout << "You selected seat " << getSeatLabel(currentRow, currentCol) << endl;
// }

void selectSeat(int flightIndex, Flight_Passenger& passenger) {
    system("cls");
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int consoleWidth, consoleHeight; 
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    } else {
        consoleWidth = 80;  
        consoleHeight = 25;  
    }

    int startX = (consoleWidth - cols * 4) / 2;   
    int startY = (consoleHeight - rows) / 2;     
    setCursorPosition(startX - 10, startY - 2);   
    cout << "Please select seat for flight " << FlightList[flightIndex].getFlightID();
    seatCursorSelect(72, startY, flightIndex, passenger);
    setCursorPosition(69, startY + rows + 3);
    cout << "Press any key to continue...";
    _getch();
    system("cls");
}

int arrowSelect(int MAX_OPTION) {
    bool selected = false;
	int current = 1;
    int x = 41, y = 4;        
    int prevX = x, prevY = y;    
    setColor(10);
    while (!selected) {
        setCursorPosition(prevX, prevY);
        cout << "   "; 
        setCursorPosition(prevX + 36, prevY);
        cout << "   "; 
		
		if (current == 1) {
			setCursorPosition(x , y);
		    cout << ">>>";
		    setCursorPosition(x + 36, y);
		    cout << "<<<";
		}
		if (current == MAX_OPTION) {
			setCursorPosition(x , y);
		    cout << ">>>";
		    setCursorPosition(x + 36, y);
		    cout << "<<<";
		}
        char ch = _getch();
        prevX = x; 
        prevY = y;
        switch (ch) {
            case 72:
                if (current > 1) {
                	current-= 1;
                    y-=2;	
				}
                break;
            case 80: 
                if (current < MAX_OPTION) {
                	current+= 1;
                	y+=2;
				}
                break;
            case 13:
            	selected = true;
            	break;
            default:
                break;
        }
        setCursorPosition(x, y);
        cout << ">>>";
        setCursorPosition(x + 36, y);
        cout << "<<<";
    }
    setColor(7);
    setCursorPosition(0, 0); 
    return current;
}

void drawMenuBox(int x, int y, int width, int height) {
    setCursorPosition(x, y);
    cout << char(201);  
    for (int i = 0; i < width - 2; i++) {
        cout << char(205); 
    }
    cout << char(187);    
    for (int i = 0; i < height - 2; i++) {
        setCursorPosition(x, y + i + 1);
        cout << char(186);
        setCursorPosition(x + width - 1, y + i + 1);
        cout << char(186); 
    }
    setCursorPosition(x, y + height - 1);
    cout << char(200);   
    for (int i = 0; i < width - 2; i++) {
        cout << char(205); 
    }
    cout << char(188);    
}

void drawButton(int x, int y, string label, bool isSelected){
	setCursorPosition(x, y);
	if(isSelected){
		setColor(10);
		cout << "[ " << label << " ]";
		setColor(7);
	} else{
		cout << "[ " << label << " ]";
	}
}


void displayFlightTable() {
    int x = 2, y = 2;
    int rowHeight = 2;
    cout << "+-------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|" << right << setw(11) << "FlightID"
         << setw(18) << "AirlineBrand"
         << setw(18) << "EconomyPrice"
         << setw(19) << "BusinessPrice"
         << setw(19) << "DepartureTime"
         << setw(17) << "ArrivalTime"
         << setw(16) << "Departure"
         << setw(16) << "Arrival|"<< endl;
    cout << "+-------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    for (int i = 0; i < FlightList.size(); i++) {       
        FlightList[i].Display_Flight();
        cout << "+-------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    }
}


// void displayFlightTable() {
//    int x = 2, y = 2;
//    int rowHeight = 3; // Ensure sufficient row height
//    drawMenuBox(x, y, 115, 10);
   
//    // Print the table header
//    setCursorPosition(x + 2, y + 1);
//    cout << left << setw(11) << "FlightID" 
//         << setw(15) << "AirlineBrand" 
//         << setw(15) << "EconomyPrice" 
//         << setw(15) << "BusinessPrice" 
//         << setw(17) << "DepartureTime" 
//         << setw(17) << "ArrivalTime" 
//         << setw(12) << "Departure" 
//         << setw(20) << "Arrival";

//    // Iterate through flight list and display rows
//    for (int i = 0; i < FlightList.size(); i++) {
//        int currentY = y + (i + 1) * rowHeight + 1; // Dynamically calculate row position
//        drawMenuBox(x, currentY, 115, 3);
//        setCursorPosition(x + 2, currentY + 1);

//        string departureDest = FlightList[i].getDepartureDestination();
//        if (departureDest.length() > 12) departureDest = departureDest.substr(0, 9) + "...";

//        string arrivalDest = FlightList[i].getArrivalDestination();
//        if (arrivalDest.length() > 11) arrivalDest = arrivalDest.substr(0, 8) + "...";

//        // Print the flight information with proper formatting
//        cout << right << setw(5) << FlightList[i].getFlightID() 
//             << setw(12) << FlightList[i].getAirlineBrandID() 
//             << setw(16) << FlightList[i].getEconomyPrice() 
//             << setw(15) << FlightList[i].getBusinessPrice() 
//             << setw(16) << FlightList[i].getDepartureTime() 
//             << setw(16) << FlightList[i].getArrivalTime() 
//             << setw(18) << departureDest 
//             << setw(11) << arrivalDest;
//    }
// }

void displayMenu(int x, int y) {
   drawMenuBox(x, y, 50, 11); 
   setCursorPosition(x + 15, y + 2);
   cout << "Book ticket";  
   setCursorPosition(x + 15, y + 4);
   cout << "Cancel ticket"; 
   setCursorPosition(x + 15, y + 6);
   cout << "Exchange ticket"; 
   setCursorPosition(x + 15, y + 8);
   cout << "Exit"; 
}

void displayBenefitsTable() {
    cout << "+----------------------------------------+----------------------------------------+" << endl;
    cout << "| " << "\033[1;31m" << "ECONOMY BENEFITS" << "\033[0m" << setw(25) << "| " << "\033[1;31m" << "BUSINESS BENEFITS" << "\033[0m" << setw(23) << "|" << endl;
    cout << "+----------------------------------------+----------------------------------------+" << endl;

    cout << "| " << "Affordable ticket price" << setw(18) << "| " << "Spacious seats with extra legroom" << setw(7) << "|" << endl;
    cout << "| " << "Standard legroom" << setw(25) << "| " << "Complimentary gourmet meals" << setw(13) << "|" << endl;
    cout << "| " << "Complimentary snacks" << setw(21) << "| " << "Exclusive lounge access" << setw(17) << "|" << endl;
    cout << "| " << "Access to basic entertainment" << setw(12) << "| " << "Premium in-flight entertainment" << setw(9) << "|" << endl;

    cout << "+----------------------------------------+----------------------------------------+" << endl;
}

void selectTicketType(int flightIndex, Flight_Passenger& passenger) {
	string ticketType;
    bool inputed = false;
	displayBenefitsTable();
	cout << endl << "Please select type of plane ticket (0: Economy, 1: Business): ";
	while(!inputed) {
        getline(cin, ticketType);
        if (ticketType.empty()) {
            continue;
        }
        int check = checkInput(ticketType);
        if (check == 0) {
            passenger.setSeatClass(check);
            passenger.setTicketPrice(FlightList[flightIndex].getEconomyPrice());
            cout << "You selected Economy class ticket!!!" << endl;
            cout << "Price: " << FlightList[flightIndex].getEconomyPrice() << endl;
            inputed = true;
            break;
        } else if (check == 1) {
            passenger.setSeatClass(check);
            passenger.setTicketPrice(FlightList[flightIndex].getBusinessPrice());
            cout << "You selected Business class ticket!!!" << endl;
            cout << "Price: " << FlightList[flightIndex].getBusinessPrice() << endl;
            inputed = true;
            break;
        } else if (check != 0 && check != 1) {
            cout << "Invalid selection. PLease select again (0 for Economy or 1 for Business): ";
        }
    }
}

// void selectFlights(){
//     string flightID;
//     bool flightFound = false;
//     displayFlightTable();  
//     cout << endl;
//     cout << "Enter Flight ID: ";
//     while(!flightFound) {
//         cin >> flightID;  
//         flightID = trim(flightID);  
//         flightID = toLowerCase(flightID);
//         int flightIndex = -1;
//         for (int i = 0; i < FlightList.size(); i++){
//             if (toLowerCase(FlightList[i].getFlightID()) == flightID){  
//                 flightFound = true;
//                 flightIndex = i;
//                 break;
//             }
//         }
//         if (flightFound) {
//             cout << endl << endl;
//             system("cls");
//             // string flightID = FlightList[flightIndex].getFlightID();
//             // string departureTime = FlightList[flightIndex].getDepartureTime();
//             // string arrivalTime = FlightList[flightIndex].getArrivalTime();
//             // string departureDest = FlightList[flightIndex].getDepartureDestination();
//             // string arrivalDest = FlightList[flightIndex].getArrivalDestination();
//             // Flight_Passenger passenger(0, "", "", "", 0, 0, 0, 0, "", "", "", "");
//             Flight_Passenger passenger(0, FlightList[flightIndex].getFlightID(), "", "", "", 0, 0, 0, flightID, "", "", 0, 0, 0, 0, 
//                                        FlightList[flightIndex].getDepartureTime(), FlightList[flightIndex].getArrivalTime(),
//                                        FlightList[flightIndex].getDepartureDestination(), FlightList[flightIndex].getArrivalDestination());
//             selectTicketType(flightIndex, passenger);  
//             selectSeat(flightIndex, passenger);
//             inputPassengerInfo(passenger);
//             printTicket(passenger);
//         } else {
//             cout << "Invalid flight ID. Please enter again: ";
//         }
//     }
// }

void selectFlights() {
    string flightID;
    bool flightFound = false;
    displayFlightTable();  
    cout << endl;
    cout << "Enter Flight ID: ";

    while (!flightFound) {
        cin >> flightID;  
        flightID = trim(flightID);  
        flightID = toLowerCase(flightID); 

        int flightIndex = -1;
        for (int i = 0; i < FlightList.size(); i++) {

            if (toLowerCase(FlightList[i].getFlightID()) == flightID) {
                flightFound = true;
                flightIndex = i;
                break;
            }
        }

        if (flightFound) {
            cout << endl << endl;
            system("cls");
            string flightID = FlightList[flightIndex].getFlightID();
            string departureTime = FlightList[flightIndex].getDepartureTime();
            string arrivalTime = FlightList[flightIndex].getArrivalTime();
            string departureDest = FlightList[flightIndex].getDepartureDestination();
            string arrivalDest = FlightList[flightIndex].getArrivalDestination();
            int economyPrice = FlightList[flightIndex].getEconomyPrice();
            int businessPrice = FlightList[flightIndex].getBusinessPrice();
            Flight_Passenger passenger;
            passenger.setFlightID(flightID);
            passenger.setDepartureTime(departureTime);
            passenger.setArrivalTime(arrivalTime);
            passenger.setDepartureDestination(departureDest);
            passenger.setArrivalDestination(arrivalDest);
            selectTicketType(flightIndex, passenger);  
            selectSeat(flightIndex, passenger);
            inputPassengerInfo(passenger);
            printTicket(passenger);
        } else {
            cout << "Invalid flight ID. Please enter again: ";
        }
    }
}


void BookTicket(){
    cout << setw(70) << "Booking ticket..." << endl;
}

void CancelTicket(){
    cout << setw(70) << "Cancelling ticket..." << endl;
}

void ExchangeTicket(){
    cout << setw(70) << "Exchanging ticket..." << endl;
}

void Exit() {
    setCursorPosition(25, 17);  
    cout << endl << setw(90) << "Exiting account, press any key to return to Log-in screen" << endl;
    system("pause > nul");  
}

void UserChoice() {
    int number;
    bool exitMenu = false;
    while (!exitMenu) {
        system("cls");  
        displayMenu(35, 2);  
        setCursorPosition(25, 15);  
        cout << setw(28) << "\033[1;31m" << "Please select your option" << "\033[0m"; 
        number = arrowSelect(4);

        switch (number) {
            case 1:
                selectFlights();
                break;
            case 2:
                CancelTicket();
                break;
            case 3:
                ExchangeTicket();  
                break;
            case 4:
                exitMenu = true;  
                Exit();
                break;
            default:
                cout << setw(60) << "Invalid choice. Please choose again!!!" << endl;
                break;
        }
        if (!exitMenu) {
            cout << endl << setw(40) << "Press any key to return to the menu..." << endl;
            system("pause > nul");  
        }
    }
    logIn();
}

void displayAdminMenu(int x, int y) {
   drawMenuBox(x, y, 50, 13); 
   setCursorPosition(x + 11, y + 2);
   cout << "Add Flight";  
   setCursorPosition(x + 11, y + 4);
   cout << "Delete Flight"; 
   setCursorPosition(x + 11, y + 6);
   cout << "Show Revenue and Flight Info"; 
   setCursorPosition(x + 11, y + 8);
   cout << "Change Flight Info"; 
   setCursorPosition(x + 11, y + 10);
   cout << "Exit"; 
}

void AddFlight() {
    system("cls");
    bool exit = false;
    string flight_id, departure_location, arrival_location;
    int airline_brand_id, economy_price, business_price; 
    string departure_time, arrival_time;
    cout << "Enter Flight ID: ";
    cin.ignore();
    getline(cin, flight_id);  
    flight_id = toUpperCase(flight_id);
    
    cout << "Enter Airline Brand ID: ";
    cin >> airline_brand_id;

    cout << "Enter Economy Price: ";
    cin >> economy_price;

    cout << "Enter Business Price: ";
    cin >> business_price;

    cin.ignore();
    cout << "Enter Departure Time: ";
    getline(cin, departure_time);

    cout << "Enter Arrival Time: ";
    getline(cin, arrival_time);

    cout << "Enter Departure Location: ";
    while (true) {
        getline(cin, departure_location);  
        departure_location = capitalizeFirstLetter(departure_location);
        cout << departure_location << endl;
        bool valid = false;
        for (const auto &city : cities) {
            if (departure_location == city) {
                valid = true;
                break;
            }
        }      
        if (valid) {
            break;
        } else {
            cout << "Invalid location, enter a valid departure location: ";
        }
    }

    cout << "Enter Arrival Location: ";
    while (true) {
        getline(cin, arrival_location);  
        arrival_location = capitalizeFirstLetter(arrival_location);
        bool valid = false;
        for (const auto &city : cities) {
            if (arrival_location == city) {
                if (arrival_location == departure_location) {
                    cout << "Arrival location cannot be the same as the departure location, enter again: ";
                    valid = false;
                } else {
                    valid = true;
                }
                break;
            }
        }
        if (valid) {
            break;
        } else if (arrival_location != departure_location) {
            cout << "Invalid location, please enter a valid arrival location: ";
        }
    }

    FlightList.push_back(Flight(flight_id, airline_brand_id, economy_price, business_price, departure_time, arrival_time, departure_location, arrival_location)); 
    cout << "NEW FLIGHT: " << endl;
    FlightList[FlightList.size() - 1].Display_Flight();
    // cout    << FlightList[FlightList.size() - 1].getFlightID() 
    //         << "       " << FlightList[FlightList.size() - 1].getAirlineBrandID() 
    //         << "       " << FlightList[FlightList.size() - 1].getEconomyPrice()
    //         << "       " << FlightList[FlightList.size() - 1].getBusinessPrice()
    //         << "       " << FlightList[FlightList.size() - 1].getDepartureTime()
    //         << "       " << FlightList[FlightList.size() - 1].getArrivalTime()
    //         << "       " << FlightList[FlightList.size() - 1].getDepartureDestination()
    //         << "       " << FlightList[FlightList.size() - 1].getArrivalDestination() << endl;
}

void DeleteFlight(){
    system("cls");
    string flightID;
    bool flightFound = false;
    displayFlightTable();  
    cout << endl;
    cout << "Enter Flight ID: ";
    while (!flightFound){
        cin >> flightID;  
        flightID = trim(flightID);  
        flightID = toLowerCase(flightID);
        for (int i = 0; i < FlightList.size(); i++) {
            if (toLowerCase(FlightList[i].getFlightID()) == flightID) {  
                flightFound = true;
                for (int j = i; j < FlightList.size() - 1; j++) {
                    FlightList[j] = FlightList[j + 1]; 
                }
                FlightList.pop_back();
                cout << "Flight successfully deleted!\n";
                return; 
            }
        }
        if (!flightFound) {
            cout << "Invalid flight ID. Please enter again: ";
        }
    }
}


void AdminChoice() {
    int number;
    bool exitMenu = false;
    while (!exitMenu) {
        system("cls");  
        displayAdminMenu(35, 2);  
        setCursorPosition(25, 15);  
        cout << setw(28) << "\033[1;31m" << "Please select your option" << "\033[0m"; 
        number = arrowSelect(5);

        switch (number) {
            case 1:
                AddFlight(); 
                break;
            case 2:
                DeleteFlight(); 
                break;
            case 3:
                ExchangeTicket();  
                break;
            case 4:
                // ChangeFlightInfo();
                break;
            case 5:
                exitMenu = true;  
                Exit();
                break;
            default:
                cout << setw(60) << "Invalid choice. Please choose again!!!" << endl;
                break;
        }

        if (!exitMenu) {
            cout << endl << setw(40) << "Press any key to return to the menu..." << endl;
            system("pause > nul");  
        }
    }
    logIn();
}

void logIn() {
    int i = returnRole();
    if (i == 0) {
        UserChoice();
	} else if (i == 1) { 
        AdminChoice();
    }
}

void initiateProgram() {
    readCities();   
    Read_Accounts();
    Read_Flights();
    logIn();
    // cout << "123231231";
}