// g++ -o manz manz.cpp    
// ./manz <input_file>

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Function to preprocess the string by inserting '#' between each character
string preprocess(const string &s) {
    string result = "#";
    for (size_t i = 0; i < s.size(); ++i) {
        result += s[i];
        result += "#";
    }
    return result;
}

// Manacher's algorithm to find the longest palindromic substring
pair<int, int> longestPalindrome(const string &s) {
    string T = preprocess(s);
    int n = T.size();
    vector<int> P(n, 0);

    int center = 0, right = 0;

    for (int i = 1; i < n; i++) {
        int mirror = 2 * center - i;

        if (i < right) {
            P[i] = min(right - i, P[mirror]);
        }

        while (i + P[i] + 1 < n && i - P[i] - 1 >= 0 && T[i + P[i] + 1] == T[i - P[i] - 1]) {
            P[i]++;
        }

        if (i + P[i] > right) {
            center = i;
            right = i + P[i];
        }
    }

    int maxLength = 0, centerIndex = 0;
    for (int i = 0; i < n; i++) {
        if (P[i] > maxLength) {
            maxLength = P[i];
            centerIndex = i;
        }
    }

    int start = (centerIndex - maxLength) / 2;
    return make_pair(start, maxLength);
}

// Function to calculate the Z-array for a given string
vector<int> calculateZ(const string &s) {
    int n = s.size();
    vector<int> Z(n, 0);

    int L = 0, R = 0;

    for (int i = 1; i < n; i++) {
        if (i <= R) {
            Z[i] = min(R - i + 1, Z[i - L]);
        }

        while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]]) {
            Z[i]++;
        }

        if (i + Z[i] - 1 > R) {
            L = i;
            R = i + Z[i] - 1;
        }
    }

    return Z;
}

// Function to replace \n and \t with spaces and keep track of their positions
pair<string, map<int, char> > replaceNewlinesAndTabs(const string &s) {
    string modifiedString;
    map<int, char> specialChars; // To store positions of '\n' and '\t'

    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '\n') {
            specialChars[modifiedString.size()] = '\n';
            modifiedString += ' ';
        } else if (s[i] == '\t') {
            specialChars[modifiedString.size()] = '\t';
            modifiedString += ' ';
        } else {
            modifiedString += s[i];
        }
    }

    return make_pair(modifiedString, specialChars);
}

// Function to generate HTML output with all palindrome occurrences highlighted based on the Z-array
// Function to generate HTML output with all palindrome occurrences highlighted based on the Z-array
void generateHtml(const string &s, const vector<int> &Z, int palindromeLength, const map<int, char> &specialChars) {
    ofstream outFile("output.html");
    if (!outFile.is_open()) {
        cerr << "Error: Could not open output.html for writing" << endl;
        return;
    }

    outFile << "<html><body><p style='white-space: pre-wrap;'>";  // Ensure we handle newlines and spaces properly

    // Traverse through the string, checking Z-array and highlighting matches
    for (size_t i = 0; i < s.size(); ++i) {
        // Check if we should start highlighting at this index based on the Z-array
        if (Z[i+palindromeLength] >= palindromeLength) {
            outFile << "<span style='color: red; font-weight: bold;'>";
            // Output the palindrome portion
            for (int j = 0; j < palindromeLength; ++j) {
                // Check for special characters (\n, \t) during the highlighting
                if (specialChars.find(i + j) != specialChars.end()) {
                    if (specialChars.find(i + j)->second == '\n') {
                        outFile << "<br>";
                    } else if (specialChars.find(i + j)->second == '\t') {
                        outFile << "&nbsp;&nbsp;&nbsp;&nbsp;";  // Treat tab as four spaces
                    }
                } else {
                    // Handle regular spaces and characters
                    if (s[i + j] == ' ') {
                        outFile << "&nbsp;";
                    } else {
                        outFile << s[i + j];
                    }
                }
            }
            outFile << "</span>";  // End the highlighting
            i += palindromeLength - 1;  // Skip ahead by the length of the palindrome
        } else {
            // Output non-highlighted characters with special character handling
            if (specialChars.find(i) != specialChars.end()) {
                if (specialChars.find(i)->second == '\n') {
                    outFile << "<br>";
                } else if (specialChars.find(i)->second == '\t') {
                    outFile << "&nbsp;&nbsp;&nbsp;&nbsp;";
                }
            } else {
                if (s[i] == ' ') {
                    outFile << "&nbsp;";
                } else {
                    outFile << s[i];
                }
            }
        }
    }

    outFile << "</p></body></html>";
    outFile.close();
    cout << "HTML output has been saved to output.html" << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    // Read input string from file
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file " << argv[1] << endl;
        return 1;
    }

    string original, line;
    while (getline(inputFile, line)) {
        original += line + "\n";  // Preserve original newlines
    }
    inputFile.close();

    // Replace newlines and tabs with spaces and track their locations
    pair<string, map<int, char> > result = replaceNewlinesAndTabs(original);
    string modifiedString = result.first;
    map<int, char> specialChars = result.second;

    // Call Manacher's algorithm to find the longest palindromic substring
    pair<int, int> longest = longestPalindrome(modifiedString);
    int start = longest.first;
    int length = longest.second;

    string longestPalin = modifiedString.substr(start, length);
    cout << "The longest palindromic substring is: '" << longestPalin << "'" << endl;

    // Prepend the longest palindrome to the original string before applying Z-algorithm
    string modifiedWithPalin = longestPalin + modifiedString;
    vector<int> Z = calculateZ(modifiedWithPalin);

    // Print the Z-array
    cout << "Z-array: ";
    for (int i = 0; i < Z.size(); i++) {
        cout << Z[i] << " ";
    }
    cout << endl;

    // Generate HTML output with all palindrome occurrences highlighted
    generateHtml(original, Z, length, specialChars);

    return 0;
}
