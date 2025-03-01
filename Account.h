#include <string>
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <algorithm>
using namespace std;

class Account {
private:
    string username;
    string password;
    int role;
    int account_id;
public:
	string getUserName() const { return username; }
	string getPassWord() const { return password; }
	int getRole() const { return role; }
    Account(string a, string b, int i) {
        username = a;
        password = b;
        role = i;
    }
    void Welcome() {
        if (role == 1) {
            cout << setw(61) << "Welcome Admin " << username << endl;  
        } else {
            cout << setw(61) << "Welcome User " << username << endl;  
        }
        cout << "\n" << setw(77) << "Press any key to continue to website" << endl;
        system("pause > nul");  
    }
    void Read_Accounts();
    int logIn();
};