#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <climits>  // For INT_MAX to represent infinity

using namespace std;

const int INF = INT_MAX;  // Infinity representation

// Function to print the shortest path using the predecessor matrix
void printPath(const vector<vector<int>>& pred, int start, int end) {
    if (start == end) {
        cout << start + 1 << " ";  // Adjusting for 1-based index
        return;
    }
    if (pred[start][end] == -1) {
        cout << "No path exists";
        return;
    }
    printPath(pred, start, pred[start][end]);
    cout << end + 1 << " ";  // Adjusting for 1-based index
}

// Function to implement Floyd-Warshall algorithm
void floydWarshall(vector<vector<int>>& w, vector<vector<int>>& pred) {
    int n = w.size();

    // Initialize dp and pred matrices
    vector<vector<int>> dp = w;  // Copy the weight matrix w to dp

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                dp[i][j] = 0;  // Distance to itself is 0
                pred[i][j] = i;  // No predecessor for self-loop
            } else if (w[i][j] != INF) {
                pred[i][j] = i;  // Direct edge, predecessor is i
            } else {
                pred[i][j] = -1;  // No direct edge
            }
        }
    }

    // Floyd-Warshall algorithm
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dp[i][k] != INF && dp[k][j] != INF && dp[i][k] + dp[k][j] < dp[i][j]) {
                    dp[i][j] = dp[i][k] + dp[k][j];
                    pred[i][j] = pred[k][j];  // Update predecessor
                }
            }
        }
    }

    // Output the results
    cout << "Shortest path distances (dp):" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dp[i][j] == INF)
                cout << "INF ";
            else
                cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nPredecessor matrix (pred):" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << pred[i][j] << " ";
        }
        cout << endl;
    }

    // Allow user to input two nodes for shortest path query
    int start, end;
    cout << "\nEnter the starting node (1-based index): ";
    cin >> start;
    cout << "Enter the ending node (1-based index): ";
    cin >> end;

    // Adjust input to 0-based index
    start--;
    end--;

    // Output the shortest path and distance
    cout << "\nShortest path from node " << start + 1 << " to node " << end + 1 << ":\n";
    if (dp[start][end] == INF) {
        cout << "No path exists between the nodes." << endl;
    } else {
        cout << "Path: ";
        printPath(pred, start, end);
        cout << "\nDistance: " << dp[start][end] << endl;
    }
}

// Function to read adjacency matrix from a file
vector<vector<int>> readAdjacencyMatrix(const string& filename) {
    ifstream file(filename);
    string line;
    vector<vector<int>> matrix;

    if (file.is_open()) {
        while (getline(file, line)) {
            // Skip the "Matriz de adyacencia:" line
            if (line.find("Matriz de adyacencia:") != string::npos) {
                continue;
            }

            stringstream ss(line);
            vector<int> row;
            int value;

            // Parse each integer in the line
            while (ss >> value) {
                if (value == 0) {
                    row.push_back(INF);  // Treat 0 as no edge, except self-loop
                } else {
                    row.push_back(value);
                }
            }

            matrix.push_back(row);
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }

    return matrix;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    string filename = argv[1];
    vector<vector<int>> w = readAdjacencyMatrix(filename);

    if (w.empty()) {
        cerr << "Error: Empty or invalid file format." << endl;
        return 1;
    }

    int n = w.size();
    vector<vector<int>> pred(n, vector<int>(n, -1));  // Initialize predecessor matrix

    // Run the Floyd-Warshall algorithm
    floydWarshall(w, pred);

    return 0;
}
