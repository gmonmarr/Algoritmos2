// g++ -std=c++11 dijkstra.cpp -o dijkstra

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <fstream>
#include <sstream>

using namespace std;

class Node {
    public:
        int id;
        int distance;
        int predecessor;
        Node(int id) {
            this->id = id;
            this->distance = INT_MAX;
            this->predecessor = -1;
        }

        Node(int id, int distance) {
            this->id = id;
            this->distance = distance;
            this->predecessor = -1;
        }

        bool operator>(const Node& other) const {
            return this->distance > other.distance;
        }
};

// Function to execute Dijkstra's algorithm
void Dijkstra(int source, const vector<vector<int>>& input, vector<Node>& graph) {
    int n = input.size();  // Number of nodes
    vector<bool> visited(n, false);  // Track visited nodes
    priority_queue<Node, vector<Node>, greater<Node>> pq;  // Min-heap based on node distance

    // Initialize the priority queue with the source node
    pq.push(graph[source]);

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        // Skip this node if it has already been processed
        if (visited[current.id]) continue;

        visited[current.id] = true;

        // Update distances to neighboring nodes
        for (int i = 0; i < input[current.id].size(); i++) {
            if (input[current.id][i] != 0 && !visited[i]) {  // Check if there is an edge and if the node is unvisited
                int newDistance = current.distance + input[current.id][i];
                if (newDistance < graph[i].distance) {
                    graph[i].distance = newDistance;
                    graph[i].predecessor = current.id;
                    pq.push(graph[i]);
                }
            }
        }
    }
}

// Function to print the predecessor-successor matrix using original edge lengths and save to a file
void printPredecessorMatrix(const vector<Node>& graph, const vector<vector<int>>& input, int n, const string& outputFileName) {
    // Create and initialize the predecessor-successor matrix with zeros
    vector<vector<int>> predecessorMatrix(n, vector<int>(n, 0));

    // First run: Fill the matrix based on predecessor information
    for (int i = 0; i < n; i++) {
        if (graph[i].predecessor != -1) {
            predecessorMatrix[graph[i].predecessor][i] = input[graph[i].predecessor][i];  // Use original edge length
        }
    }

    // Second run: Also fill the matrix with connections from successors to predecessors
    for (int i = 0; i < n; i++) {
        if (graph[i].predecessor != -1) {
            predecessorMatrix[i][graph[i].predecessor] = input[i][graph[i].predecessor];  // Use original edge length
        }
    }

    // Write the predecessor-successor matrix to the output file
    ofstream outFile(outputFileName);
    if (outFile.is_open()) {
        outFile << "Matriz de adyacencia:\n";
        for (const auto& row : predecessorMatrix) {
            for (int val : row) {
                outFile << val << " ";
            }
            outFile << endl;
        }
        outFile.close();
        cout << "Predecessor-Successor matrix written to " << outputFileName << endl;
    } else {
        cerr << "Error opening file: " << outputFileName << endl;
    }
}

// Function to read an adjacency matrix from a file
vector<vector<int>> readMatrixFromFile(const string& filename) {
    ifstream infile(filename);
    string line;
    vector<vector<int>> matrix;
    bool isMatrix = false;

    while (getline(infile, line)) {
        if (line.find("Matriz de adyacencia:") != string::npos) {
            isMatrix = true;  // Start reading matrix after this line
            continue;
        }
        if (isMatrix) {
            vector<int> row;
            stringstream ss(line);
            int value;
            while (ss >> value) {
                row.push_back(value);
            }
            matrix.push_back(row);
        }
    }

    infile.close();
    return matrix;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input_filename> <output_filename>" << endl;
        return 1;
    }

    string inputFileName = argv[1];
    string outputFileName = argv[2];

    // Read the adjacency matrix from the input file
    vector<vector<int>> input = readMatrixFromFile(inputFileName);

    if (input.empty()) {
        cerr << "Failed to read the matrix from the file: " << inputFileName << endl;
        return 1;
    }

    int n = input.size();  // Number of nodes
    int source = 0;  // Source node (node 0)
    vector<Node> graph;  // Graph represented by a list of nodes

    // Initialize graph with all nodes
    for (int i = 0; i < n; i++) {
        if (i == source) {
            graph.push_back(Node(i, 0));  // Set source node's distance to 0
        } else {
            graph.push_back(Node(i));  // Other nodes start with max distance
        }
    }

    // Run Dijkstra's algorithm
    Dijkstra(source, input, graph);

    // Output the predecessor-successor matrix using original edge lengths and write to file
    printPredecessorMatrix(graph, input, n, outputFileName);

    return 0;
}
