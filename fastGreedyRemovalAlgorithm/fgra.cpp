// La función de este programa es reducir un array de datos a un tamaño N
// se corre el programa con ./fgra <file path> <alpha> <N size> <output folder>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// alpha = m + 1
// m es la dimensión de datos (2D, 3D, 4D, etc)

// M es master array o init array
// N es el número para cual reducir el master array
/*
Input: M array , subset N, alpha
A = M 
Calculate matrix K , |K| = |A| x |A| 
K_ij = Potential energy distance between A[i] and A[j]
Calculate list r, 
r_i = r1 + r2 + r3 ... r_j, cuando i=j r=0

K Riesz alpha-energy = 1 / (distance between point a and b)^alpha

r_i = Summation of K_ij for all j in A minus r_i

while |A| > N do 
    find jworst = argmax(r) // find the worst element in r 
    
    for i = 1 to |A| do 
        ri = ri - K_ij_worst
    Delete jworst column and row from K
    Delete jworst element from r

    A = A - A[jworst] // remove the worst element from A

return A
*/

double eucledianDistance(const vector<double>& x, const vector<double>& y, int dimension) {
    double sum = 0;
    for (int i = 0; i < dimension; i++) {
        sum += pow(x[i] - y[i], 2);
    }
    return sqrt(sum);
}

double KRiesz(const vector<double>& x, const vector<double>& y, int dimension, double alpha) {
    return 1 / pow(eucledianDistance(x, y, dimension), alpha);
}

vector<vector<double> > fgra(int n, vector<vector<double> >& A, double alpha)  {
    // Init variables (kmatrix, r, mask)
    double Kmatrix[A.size()][A.size()];
    double r[A.size()];
    bool mask[A.size()];
    int numberOfDeletions = 0;
    fill_n(mask, A.size(), true);

    // Calculate Kmatrix
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A.size(); j++) {
            if (i != j) {
                Kmatrix[i][j] = KRiesz(A[i], A[j], A[i].size(), alpha);
            } else {
                Kmatrix[i][j] = 0;
            }
        }
    }

    // calculate r
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A.size(); j++) {
            r[i] += Kmatrix[i][j];
        }
    }

    // Main loop
    while ((A.size() - numberOfDeletions) > n) {
        // Find the worst element in r
        double worst = -1;
        int worstIndex = 0;
        for (int i = 0; i < A.size(); i++) {
            if (mask[i] && r[i] > worst) {
                worst = r[i];
                worstIndex = i;
            }
        }

        // Update r
        for (int i = 0; i < A.size(); i++) {
            if (mask[i]) {
                r[i] -= Kmatrix[i][worstIndex];
            }
        }

        // Delete worst element
        mask[worstIndex] = false;
        numberOfDeletions++;
    }

    // Create the result array
    vector<vector<double> > result;
    for (int i = 0; i < A.size(); i++) {
        if (mask[i]) {
            result.push_back(A[i]);
        }
    }

    return result;
}


int main(int argc, char *argv[]) {
    if (argc < 5) {
        cerr << "Usage: " << argv[0] << " <file path> <alpha> <N size> <output folder>" << endl;
        return 1;
    }

    string filePath = argv[1];
    int n = stoi(argv[2]);
    double alpha = stod(argv[3]);
    string outputFolder = argv[4];

    ifstream in(filePath);
    if (!in) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    if (!getline(in, line)) {
        cerr << "Error reading the first line of the file!" << endl;
        return 1;
    }

    // Read the first line to set dimensions
    istringstream firstLineStream(line);
    string hashtag; 
    int numEntries;
    int dimensions;
    if (!(firstLineStream >> hashtag >> numEntries >> dimensions)) {
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

    vector<vector<double> > result = fgra(n, A, alpha);

    // Generate the output file path
    string inputFileName = filePath.substr(filePath.find_last_of("/\\") + 1);
    string outputFilePath = outputFolder + "/reduced_array_" + inputFileName;

    ofstream out(outputFilePath);
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

    std::cout << "Reduced array written to '" << outputFilePath << "'" << endl;

    return 0;
}