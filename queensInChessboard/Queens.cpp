#include <iostream>
#include <vector>

using namespace std;

bool isSafe(vector<vector<int> > &T, int row, int col, int n) {
    for (int i = 1; i < row; i++) {
        if (T[i][col] == 1) {
            return false;
        }
    }
    for (int i = row, j = col; i >= 1 && j >= 1; i--, j--) {
        if (T[i][j] == 1) {
            return false;
        }
    }
    for (int i = row, j = col; i >= 1 && j <= n; i--, j++) {
        if (T[i][j] == 1) {
            return false;
        }
    }
    

    return true;
}

bool solveQueensProblem(vector<vector<int> > &T, int row, int n) {  
    int col;
    if (row == n+1) {
        return true;
    }
    for (int col = 1; col <= n; col++) {
        if (isSafe(T, row, col, n)) {
            T[row][col] = 1;
            if (solveQueensProblem(T, row+1, n)) {
                return true;
            }
            T[row][col] = 0;
        }
    }
    return false;
}

void printBoard(vector<vector<int> > & T) {
    for (int i = 1; i < T.size(); i++) {
        for (int j = 1; j < T.size(); j++) {
            cout << T[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Give n: ";
    cin >> n;
    cout << endl;
    //int n = 8; // Change n to adjust for different board sizes

    vector<vector<int> > Tablero(n+1, vector<int>(n+1, 0));

    if (solveQueensProblem(Tablero, 0, n)) {
        cout << "Solution:" << endl;
        printBoard(Tablero);
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}
