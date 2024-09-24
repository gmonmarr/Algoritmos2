#include <iostream>
#include <vector>
#include <limits>
#include <fstream>

bool binarySearch(const std::vector<int>& A, int p, int r, int t) {
    if (p < r) {
        int mid = (p + r) / 2;
        if (A[mid] == t) {
            return true;
        } else if (t < A[mid]) {
            return binarySearch(A, p, mid - 1, t);
        } else {
            return binarySearch(A, mid + 1, r, t);
        }
    } else {
        return false;
    }
}

std::vector<int> createArray(int size) {
    std::vector<int> arr;
    for (int i = 1; i <= size; ++i) {
        arr.push_back(i);
    }
    return arr;
}

int main() {
    while (true) {
        int maxSize;
        std::cout << "Enter the maximum size of the array (enter 0 or a non-number to exit): ";
        std::cin >> maxSize;

        if (std::cin.fail() || maxSize == 0) {
            break;
        }

        std::ofstream outputFile("output.txt");

        if (!outputFile) {
            std::cerr << "Unable to open output file!" << std::endl;
            return 1;
        }

        std::vector<int> notFoundSizes;

        for (int size = 1; size <= maxSize; ++size) {
            if (size % 1000 == 0) {
                std::cout << "Processing size " << size << std::endl;
            }

            std::vector<int> arr = createArray(size);
            int target = 2;

            if (!binarySearch(arr, 0, arr.size() - 1, target)) {
                notFoundSizes.push_back(size);
            }
        }

        outputFile << "Sizes where 2 is not found:" << std::endl;
        for (int n : notFoundSizes) {
            outputFile << n << " = x" << std::endl;
        }

        outputFile.close();

        // Clear the input buffer in case of a non-numeric input
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Exiting program. Check output.txt for results." << std::endl;
    return 0;
}
