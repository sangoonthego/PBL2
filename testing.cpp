#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

const int rows = 10;
const int cols = 5;

void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Display a single cell at the specified (row, col) position
void displayCell(int row, int col, int startX, int startY, bool isSelected) {
    int x = startX + col * 4;  // Calculate x position for the cell
    int y = startY + row;       // Calculate y position for the cell
    
    setCursorPosition(x, y);
    if (isSelected) {
        setColor(10);  // Highlight color for the selected cell
        cout << "[X] ";  // Display selected cell with indicator
        setColor(7);     // Reset to default color
    } else {
        cout << "[ ] ";  // Display a regular cell
    }
}

// Arrow selection function
void arrowSelect(int startX, int startY) {
    int currentRow = 0;   
    int currentCol = 0; 
    int prevRow = currentRow, prevCol = currentCol;
    bool selected = false;
     
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            displayCell(i, j, startX, startY, (i == currentRow && j == currentCol));
        }
    }

    while (!selected) {
        char ch = _getch(); 
        prevRow = currentRow;
        prevCol = currentCol;
        
        switch (ch) {
            case 72: // Up arrow key
                if (currentRow > 0) {
                    currentRow--;
                }
                break;
            case 80: // Down arrow key
                if (currentRow < rows - 1) {
                    currentRow++;
                }
                break;
            case 75: // Left arrow key
                if (currentCol > 0) {
                    currentCol--;
                }
                break;
            case 77: // Right arrow key
                if (currentCol < cols - 1) {
                    currentCol++;
                }
                break;
            case 13: // Enter key
                selected = true;
                break;
            default:
                break;
        } 
        if (prevRow != currentRow || prevCol != currentCol) {
            displayCell(prevRow, prevCol, startX, startY, false);   
            displayCell(currentRow, currentCol, startX, startY, true);   
        }
    }

    setCursorPosition(0, startY + rows + 2);   
    cout << "You selected cell (" << currentRow + 1 << ", " << currentCol + 1 << ")" << endl;
}

int main() { 
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

    arrowSelect(startX, startY);
    return 0;
}

