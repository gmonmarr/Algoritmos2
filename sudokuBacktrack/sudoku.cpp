#include <iostream>
#include <vector>
#include <fstream>
#include <sstream> 
#include <unordered_set>

using namespace std;

// Function to check if a number is safe to place in a cell
bool isSafe(vector<vector<int> > &T, int row, int col, int n, int num) {
    // Check row
    for (int i = 0; i < n; i++) {
        if (T[row][i] == num) {
            return false;
        }
    }

    // Check column
    for (int i = 0; i < n; i++) {
        if (T[i][col] == num) {
            return false;
        }
    }

    // Check square
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (T[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    // If all checks pass, return true
    return true;
}

// Function to validate the input board
bool isValidBoard(vector<vector<int> > &T, int n) {
    // Check rows and columns
    for (int i = 0; i < n; i++) {
        unordered_set<int> rowSet, colSet;
        for (int j = 0; j < n; j++) {
            // Check row uniqueness
            if (T[i][j] != 0) {
                if (rowSet.find(T[i][j]) != rowSet.end()) {
                    return false;
                }
                rowSet.insert(T[i][j]);
            }
            // Check column uniqueness
            if (T[j][i] != 0) {
                if (colSet.find(T[j][i]) != colSet.end()) {
                    return false;
                }
                colSet.insert(T[j][i]);
            }
        }
    }

    // Check 3x3 subgrids
    for (int row = 0; row < n; row += 3) {
        for (int col = 0; col < n; col += 3) {
            unordered_set<int> gridSet;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int num = T[row + i][col + j];
                    if (num != 0) {
                        if (gridSet.find(num) != gridSet.end()) {
                            return false;
                        }
                        gridSet.insert(num);
                    }
                }
            }
        }
    }

    // If all checks pass, the board is valid
    return true;
}

// Function to solve the sudoku board
bool solveSudoku(vector<vector<int> > &T, int n) {
    int row, col;
    bool isEmpty = true;

    // Find an empty cell
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            if (T[row][col] == 0) {
                isEmpty = false;
                break;
            }
        }
        if (!isEmpty) {
            break;
        }
    }

    // If no empty cell is found, the board is solved
    if (isEmpty) {
        return true;
    }

    // Try to place a number in the empty cell
    for (int num = 1; num <= n; num++) {
        if (isSafe(T, row, col, n, num)) {
            T[row][col] = num;
            if (solveSudoku(T, n)) {
                return true;
            }
            T[row][col] = 0;
        }
    }

    // If no number can be placed, return false
    return false;
}

// Function to print the board
void printBoard(vector<vector<int> > &T, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << T[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char *argv[]) {
    // Check for valid number of arguments
    if (argc != 2) {
        cout << "Error: invalid number of arguments" << endl;
        return 1;
    }

    // Initialize variables
    // Read the input file
    string inputFile = argv[1];
    ifstream file(inputFile);
    string line;

    // Initialize the board 9 rows and 9 columns with 0
    vector<vector<int> > board(9, vector<int>(9, 0));

    // Read the sudoku board from the input file (comma-separated format)
    if (file.is_open()) {
        for (int i = 0; i < 9; i++) {
            getline(file, line);  // Read the entire line as a string
            stringstream ss(line); // Create a stringstream to parse the line
            string value;
            for (int j = 0; j < 9; j++) {
                if (getline(ss, value, ',')) { // Extract numbers separated by commas
                    board[i][j] = stoi(value); // Convert string to integer
                }
            }
        }
        file.close();
    } else {
        cout << "Error: could not open file" << endl;
        return 1;
    }

    // Check if the input board is valid
    if (!isValidBoard(board, 9)) {
        cout << "Error: invalid input board" << endl;
        return 1;
    }

    printBoard(board, 9);

    // Solve the sudoku board, and output the solution (or error)
    if (solveSudoku(board, 9)) {
        // Write solution to file
        ofstream file("solution.txt");
        if (file.is_open()) {
            for (int i = 0; i < 9; i++) {
                file << board[i][0];
                for (int j = 1; j < 9; j++) {
                    file << ", " << board[i][j];
                }
                file << endl;
            }
            file.close();
        }

        // Print solution to console
        printBoard(board, 9);
    } else {
        // Error message if no solution exists
        cout << "No solution exists" << endl;
    }

    return 0;
}