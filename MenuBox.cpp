#include "MenuBox.h"
#include <iostream>
using namespace std;

void setCursorPosition(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawMenuBox(int x, int y, int width, int height){
    setCursorPosition(x, y);
    cout << char(201);  
    for (int i = 0; i < width - 2; i++){
        cout << char(205); 
    }
    cout << char(187);    

    for (int i = 0; i < height - 2; i++){
        setCursorPosition(x, y + i + 1);
        cout << char(186);
        setCursorPosition(x + width - 1, y + i + 1);
        cout << char(186); 
    }

    setCursorPosition(x, y + height - 1);
    cout << char(200);   
    for (int i = 0; i < width - 2; i++){
        cout << char(205); 
    }
    cout << char(188);    
}