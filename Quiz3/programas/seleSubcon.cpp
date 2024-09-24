#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

double d(const vector<double>& x, const vector<double>& y, int k) {
    double sum = 0;
    for (int i = 0; i < k; i++) {
        sum += pow(x[i] - y[i], 2);
    }
    return sqrt(sum);
}

double U(const vector<vector<double> >& S, int k) {
    double sum = 0;
    for (int i = 0; i < S.size(); i++) {
        for (int j = 0; j < S.size(); j++) {
            if (i == j) continue;
            sum += 1 / pow(d(S[i], S[j], k), k + 1);
        }
    }
    return sum;
}

int C(const vector<vector<double> >& A) {
    int k = A[0].size();
    double worstX = -1;
    int worstIndex = 0;
    double currentX;
    for (int i = 0; i < A.size(); i++) {
        vector<vector<double> > temp = A;
        temp.erase(temp.begin() + i);
        currentX = U(A, k) - U(temp, k);
        if (currentX > worstX) {
            worstX = currentX;
            worstIndex = i;
        }
    }
    return worstIndex;
}

vector<vector<double> > algoritmo(int n, vector<vector<double> >& A) {
    int deletions = 0;
    while (A.size() > n) {
        int worst = C(A);
        cout << "Deleted index: " << worst << " Value: ";
        for (double val : A[worst]) {
            cout << val << " ";
        }
        cout << endl;

        A.erase(A.begin() + worst);
        deletions++;
        if (deletions % 10 == 0) {
            cout << deletions << " deletions performed." << endl;
        }
    }
    return A;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <file path>" << endl;
        return 1;
    }

    ifstream in(argv[1]);
    if (!in) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    cout << "Enter the size to reduce to (n): ";
    int n;
    cin >> n;

    string line;
    if (!getline(in, line)) {
        cerr << "Error reading the first line of the file!" << endl;
        return 1;
    }

    // Read the first line to set dimensions
    istringstream firstLineStream(line);
    int numEntries;
    int dimensions;
    if (!(firstLineStream >> numEntries >> dimensions)) {
        cerr << "Error: The first line does not contain two integers (numEntries and dimensions)." << endl;
        return 1;
    }

    vector<vector<double> > A;

    while (getline(in, line)) {
        if (!line.empty() && line[0] == '#') {
            line = line.substr(1); // Remove the leading '#'
        }

        istringstream iss(line);
        vector<double> temp(dimensions);
        for (int i = 0; i < dimensions; i++) {
            if (!(iss >> temp[i])) {
                cerr << "Error reading data." << endl;
                return 1;
            }
        }
        A.push_back(temp);
    }

    // Print the received array with debugging information
    cout << "Received array:" << endl;
    for (int i = 0; i < A.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < A[i].size(); j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    vector<vector<double> > result = algoritmo(n, A);

    // Write the result to a text file
    ofstream out("after.txt");
    if (!out) {
        cerr << "Error creating output file!" << endl;
        return 1;
    }

    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            out << result[i][j] << " ";
        }
        out << endl;
    }

    out.close();

    cout << "Reduced array written to 'reduced_array.txt'" << endl;

    return 0;
}
