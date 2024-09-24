#include <iostream>
#include <vector>
#include <limits>

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
        int size;
        std::cout << "Enter the size of the array (enter 0 or a non-number to exit): ";
        std::cin >> size;

        if (std::cin.fail() || size == 0) {
            break;
        }

        std::vector<int> arr = createArray(size);
        int target;
        std::cout << "Enter the number to search for: ";
        std::cin >> target;

        if (binarySearch(arr, 0, arr.size() - 1, target)) {
            std::cout << "Found " << target << " in the array." << std::endl;
        } else {
            std::cout << target << " is not in the array." << std::endl;
        }

        // Clear the input buffer in case of a non-numeric input
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Exiting program." << std::endl;
    return 0;
}
