#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 9;

void printGrid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) {
            return false;
        }
    }
  
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == num) {
            return false;
        }
    }
  
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
  
    return true;
}

bool solveSudoku(int grid[N][N]) {
    int row, col;
  
    bool isUnassigned = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isUnassigned = true;
                break;
            }
        }
        if (isUnassigned) {
            break;
        }
    }
  
    if (!isUnassigned) {
        return true;
    }
  
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
  
            if (solveSudoku(grid)) {
                return true;
            }
  
            grid[row][col] = 0;
        }
    }
  
    return false;
}

void generateRandomGrid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = 0;
        }
    }
  
    srand(time(0));
    int numValues = rand() % 15 + 20;
  
    while (numValues > 0) {
        int row = rand() % 9;
        int col = rand() % 9;
        int value = rand() % 9 + 1;
      
        if (isSafe(grid, row, col, value)) {
            grid[row][col] = value;
            numValues--;
        }
    }
}

int main() {
    int grid[N][N];
  
    cout << "Welcome to Sudoku Game!" << endl;
    cout << "Enter row, column, and value (separated by spaces) to fill the grid. Enter '0 0 0' to solve the Sudoku." << endl;
  
    generateRandomGrid(grid);
  
    while (true) {
        cout << endl << "Current Sudoku grid:" << endl;
        printGrid(grid);
      
        int row, col, value;
        cout << "Enter row, column, and value: ";
        cin >> row >> col >> value;
      
        if (row == 0 && col == 0 && value == 0) {
            if (solveSudoku(grid)) {
                cout << "Sudoku solved!" << endl;
                printGrid(grid);
            } else {
                cout << "No solution exists for the given Sudoku." << endl;
            }
            break;
        }
      
        if (row < 1 || row > N || col < 1 || col > N || value < 1 || value > 9) {
            cout << "Invalid input. Please try again." << endl;
            continue;
        }
      
        if (!isSafe(grid, row - 1, col - 1, value)) {
            cout << "Invalid move. The entered value conflicts with the existing grid." << endl;
            continue;
        }
      
        grid[row - 1][col - 1] = value;
    }
  
    return 0;
}
