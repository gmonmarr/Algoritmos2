// La función de este programa es reducir un array de datos a un tamaño N
// se corre el programa con ./fgra <folder1> <folder2>
// en el cual folder1 contiene los archivos a ser reducidos,
// y folder2 es el directorio donde se guardarán los archivos reducidos

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h> // For directory creation
#include <unistd.h> // For access function

using namespace std;

double eucledianDistance (const vector<double>& x, const vector<double>& y, int dimension) {
    double sum = 0;
    for (int i = 0; i < dimension; i++) {
        sum += pow(x[i] - y[i], 2);
    }
    return sqrt(sum);
}

double KRiesz(const vector<double>& x, const vector<double>& y, int dimension) {
    return 1 / pow(eucledianDistance(x, y, dimension), dimension + 1);
}

vector<vector<double> > fgra(int n, vector<vector<double> >& A) {
    double Kmatrix[A.size()][A.size()];
    double r[A.size()];
    bool mask[A.size()];
    int numberOfDeletions = 0;
    fill_n(mask, A.size(), true);

    // Calculate Kmatrix
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A.size(); j++) {
            if (i != j) {
                Kmatrix[i][j] = KRiesz(A[i], A[j], A[i].size());
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
        double worst = -1;
        int worstIndex = 0;
        for (int i = 0; i < A.size(); i++) {
            if (mask[i] && r[i] > worst) {
                worst = r[i];
                worstIndex = i;
            }
        }

        for (int i = 0; i < A.size(); i++) {
            if (mask[i]) {
                r[i] -= Kmatrix[i][worstIndex];
            }
        }

        mask[worstIndex] = false;
        numberOfDeletions++;
    }

    vector<vector<double> > result;
    for (int i = 0; i < A.size(); i++) {
        if (mask[i]) {
            result.push_back(A[i]);
        }
    }

    return result;
}

bool directoryExists(const string& path) {
    return access(path.c_str(), F_OK) == 0;
}

bool createDirectory(const string& path) {
    return mkdir(path.c_str(), 0755) == 0;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input directory path> <output directory path>" << endl;
        return 1;
    }

    std::cout << "Enter the size to reduce to (n): ";
    int n;
    cin >> n;

    string inputDir = argv[1];
    string outputDir = argv[2];

    // Check if output directory exists, create if it doesn't
    if (!directoryExists(outputDir)) {
        if (!createDirectory(outputDir)) {
            cerr << "Error creating output directory: " << outputDir << endl;
            return 1;
        }
    }

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(inputDir.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            string filename = ent->d_name;

            // Skip "." and ".." directories
            if (filename == "." || filename == "..") {
                continue;
            }

            string filepath = inputDir + "/" + filename;
            ifstream in(filepath.c_str());
            if (!in) {
                cerr << "Error opening file: " << filepath << endl;
                continue;
            }

            string line;
            if (!getline(in, line)) {
                cerr << "Error reading the first line of the file: " << filepath << endl;
                continue;
            }

            istringstream firstLineStream(line);
            string hashtag;
            int numEntries;
            int dimensions;
            if (!(firstLineStream >> hashtag >> numEntries >> dimensions)) {
                cerr << "Error: The first line does not contain two integers (numEntries and dimensions) in file: " << filepath << endl;
                continue;
            }

            vector<vector<double> > A;

            while (getline(in, line)) {
                if (!line.empty() && line[0] == '#') {
                    line = line.substr(1);
                }

                istringstream iss(line);
                vector<double> temp(dimensions);
                for (int i = 0; i < dimensions; i++) {
                    if (!(iss >> temp[i])) {
                        cerr << "Error reading data in file: " << filepath << endl;
                        return 1;
                    }
                }
                A.push_back(temp);
            }

            vector<vector<double> > result = fgra(n, A);

            string outputFilePath = outputDir + "/reduced_" + filename;
            ofstream out(outputFilePath.c_str());
            if (!out) {
                cerr << "Error creating output file: " << outputFilePath << endl;
                continue;
            }

            for (int i = 0; i < result.size(); i++) {
                for (int j = 0; j < result[i].size(); j++) {
                    out << result[i][j] << " ";
                }
                out << endl;
            }

            out.close();
            cout << "Reduced array written to '" << outputFilePath << "' from file: " << filepath << endl;
        }
        closedir(dir);
    } else {
        cerr << "Could not open directory: " << inputDir << endl;
        return 1;
    }

    return 0;
}
