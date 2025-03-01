#include "Account.h"
using namespace std;

vector<Account> AccountList;

void Read_Accounts() {
	ifstream file("accounts.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
        	int i = 0;
        	string info[3];
            stringstream ss(line);
            string word;
            while (ss >> word) {
                word.erase(remove(word.begin(), word.end(), ';'), word.end());
                word.erase(remove(word.begin(), word.end(), '|'), word.end());
                if (!word.empty()) {
                    info[i] = word;
                    i++;
                }
            }
            if (i == 3) {  
                int role = stoi(info[2]);  
                AccountList.push_back(Account(info[0], info[1], role)); 
            } 
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

