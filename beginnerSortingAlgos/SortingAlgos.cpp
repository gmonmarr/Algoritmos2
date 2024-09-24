// C++ program to test the performance of different sorting algorithms
// Merge sort, Bubble sort, Quick sort, Stupid sort (BogoSort) and std::sort (Intro Sort)
// WARNING BOGO SORT IS VERY INEFFICIENT AND WILL TAKE A STUPID AMOUNT OF TIME TO SORT LARGE ARRAYS
// IT IS RECOMMENDED TO DISABLE (COMMENT) THE STUPID SORT SECTION IF TESTING ON LARGE ARRAYS 10+ ELEMENTS

// By default each sorting algorithm will be tested 500 times on an array of size n
// The average time of execution, variance and standard deviation will be calculated and displayed

#include <fstream>
#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>
#include <cstdlib> // For rand()

using namespace std;

// Merge Sort Functions
void merge(int A[], int p, int q, int r){
    int num1 = q - p + 1;
    int num2 = r - q;
    
    int L[num1 + 1];
    int R[num2 + 1];
    
    for (int i = 0; i < num1; i++){
        L[i] = A[p + i];
    }

    for (int j = 0; j < num2; j++){
        R[j] = A[q + j + 1];
    }

    L[num1] = numeric_limits<int>::max();
    R[num2] = numeric_limits<int>::max();

    for (int i = 0, j = 0, k = p; k <= r; k++){
        if (L[i] <= R[j]){
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
}

void merge_sort(int a[], int inicio, int fin){
    if (inicio < fin){
        int medio = floor((inicio + fin) / 2);
        merge_sort(a, inicio, medio);
        merge_sort(a, medio + 1, fin);
        merge(a, inicio, medio, fin);
    }
}

// Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Quick Sort Functions
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Stupid Sort (BogoSort)
bool isSorted(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i-1] > arr[i]) {
            return false;
        }
    }
    return true;
}

void shuffle(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int randomIndex = rand() % n;
        int temp = arr[i];
        arr[i] = arr[randomIndex];
        arr[randomIndex] = temp;
    }
}

void stupidSort(int arr[], int n) {
    while (!isSorted(arr, n)) {
        shuffle(arr, n);
    }
}

// Function to print the array
void print_array(int a[], int n){
    for (int i = 0; i < n; i++){
        cout << a[i] << endl;
    }
}

// Function to copy an array
void copy_array(int source[], int destination[], int n){
    for (int i = 0; i < n; i++) {
        destination[i] = source[i];
    }
}

int main(int argc, char *argv[]) {
    cout << "Testing on a size of " << argv[1] << " elements" << endl;

    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <array size>" << endl;
        return 1;
    }

    int listSize = atoi(argv[1]);

    // Create reverse sorted array
    int *arreglo = new int[listSize];
    for (int i = 0; i < listSize; i++) {
        arreglo[i] = listSize - i;
    }

    int *tempArray = new int[listSize]; // Temporary array for copying

    double rollingAverage = 0;
    double rollingVariance = 0;
    double stdDev = 0;
    double elapsed_time = 0;

    
    // Testing Merge Sort
    for (int i = 1; i < 501; i++){
        if (i % 100 == 0){
            cout << "Merge Sort - Prueba número: " << i << endl;
        }

        copy_array(arreglo, tempArray, listSize); // Copy original array to tempArray
        clock_t start = clock();
        merge_sort(tempArray, 0, listSize - 1); // Sort tempArray
        clock_t end = clock();

        double elapsed_time = double(end - start) / CLOCKS_PER_SEC;   

        double prevAverage = rollingAverage;
        rollingAverage += (elapsed_time - rollingAverage) / i;
        rollingVariance += (elapsed_time - prevAverage) * (elapsed_time - rollingAverage);
    }

    stdDev = sqrt(rollingVariance / 500);
    cout << fixed << setprecision(8);
    cout << "Merge Sort - Tiempo de ejecucción promedio: " << rollingAverage << " segundos" << endl;
    cout << "Varianza: " << rollingVariance / 500 << endl;
    cout << "Desviación estándar: " << stdDev << endl;

    // Reset statistics for the next sort
    rollingAverage = 0;
    rollingVariance = 0;

    // Testing Bubble Sort
    for (int i = 1; i < 501; i++){
        if (i % 100 == 0){
            cout << "Bubble Sort - Prueba número: " << i << endl;
        }

        copy_array(arreglo, tempArray, listSize); // Copy original array to tempArray
        clock_t start = clock();
        bubbleSort(tempArray, listSize); // Sort tempArray
        clock_t end = clock();

        double elapsed_time = double(end - start) / CLOCKS_PER_SEC;   

        double prevAverage = rollingAverage;
        rollingAverage += (elapsed_time - rollingAverage) / i;
        rollingVariance += (elapsed_time - prevAverage) * (elapsed_time - rollingAverage);
    }

    stdDev = sqrt(rollingVariance / 500);
    cout << "Bubble Sort - Tiempo de ejecucción promedio: " << rollingAverage << " segundos" << endl;
    cout << "Varianza: " << rollingVariance / 500 << endl;
    cout << "Desviación estándar: " << stdDev << endl;

    // Reset statistics for the next sort
    rollingAverage = 0;
    rollingVariance = 0;
    
    // Testing Quick Sort
    for (int i = 1; i < 501; i++){
        if (i % 100 == 0){
            cout << "Quick Sort - Prueba número: " << i << endl;
        }

        copy_array(arreglo, tempArray, listSize); // Copy original array to tempArray
        clock_t start = clock();
        quickSort(tempArray, 0, listSize - 1); // Sort tempArray
        clock_t end = clock();

        double elapsed_time = double(end - start) / CLOCKS_PER_SEC;   

        double prevAverage = rollingAverage;
        rollingAverage += (elapsed_time - rollingAverage) / i;
        rollingVariance += (elapsed_time - prevAverage) * (elapsed_time - rollingAverage);
    }

    stdDev = sqrt(rollingVariance / 500);
    cout << "Quick Sort - Tiempo de ejecucción promedio: " << rollingAverage << " segundos" << endl;
    cout << "Varianza: " << rollingVariance / 500 << endl;
    cout << "Desviación estándar: " << stdDev << endl;

    // Reset statistics for the next sort
    rollingAverage = 0;
    rollingVariance = 0;

    // Testing Stupid Sort (BogoSort)
    for (int i = 1; i < 501; i++){
        if (i % 100 == 0){
            cout << "Stupid Sort - Prueba número: " << i << endl;
        }

        copy_array(arreglo, tempArray, listSize); // Copy original array to tempArray
        clock_t start = clock();
        stupidSort(tempArray, listSize); // Sort tempArray
        clock_t end = clock();

        double elapsed_time = double(end - start) / CLOCKS_PER_SEC;   

        double prevAverage = rollingAverage;
        rollingAverage += (elapsed_time - rollingAverage) / i;
        rollingVariance += (elapsed_time - prevAverage) * (elapsed_time - rollingAverage);
    }

    stdDev = sqrt(rollingVariance / 500);
    cout << "Stupid Sort - Tiempo de ejecucción promedio: " << rollingAverage << " segundos" << endl;
    cout << "Varianza: " << rollingVariance / 500 << endl;
    cout << "Desviación estándar: " << stdDev << endl;

    // Reset statistics for the next sort
    rollingAverage = 0;
    rollingVariance = 0;

    // Testing std::Sort (Intro Sort) nLog(n)
    for (int i = 1; i < 501; i++){
        if (i % 100 == 0){
            cout << "std::Sort - Prueba número: " << i << endl;
        }

        copy_array(arreglo, tempArray, listSize); // Copy original array to tempArray
        clock_t start = clock();
        std::sort(tempArray, tempArray + listSize); // Sort tempArray
        clock_t end = clock();

        double elapsed_time = double(end - start) / CLOCKS_PER_SEC;   

        double prevAverage = rollingAverage;
        rollingAverage += (elapsed_time - rollingAverage) / i;
        rollingVariance += (elapsed_time - prevAverage) * (elapsed_time - rollingAverage);
    }

    stdDev = sqrt(rollingVariance / 500);
    cout << "std::Sort - Tiempo de ejecucción promedio: " << rollingAverage << " segundos" << endl;
    cout << "Varianza: " << rollingVariance / 500 << endl;
    cout << "Desviación estándar: " << stdDev << endl;

    rollingAverage = 0;
    rollingVariance = 0;

    // Simply inverting the list
    for (int i = 1; i < 501; i++){
        if (i % 100 == 0){
            cout << "Invertir arreglo - Prueba número: " << i << endl;
        }

        copy_array(arreglo, tempArray, listSize); // Copy original array to tempArray
        clock_t start = clock();
        reverse(tempArray, tempArray + listSize); // Sort tempArray
        clock_t end = clock();

        double elapsed_time = double(end - start) / CLOCKS_PER_SEC;   

        double prevAverage = rollingAverage;
        rollingAverage += (elapsed_time - rollingAverage) / i;
        rollingVariance += (elapsed_time - prevAverage) * (elapsed_time - rollingAverage);
    }

    stdDev = sqrt(rollingVariance / 500);
    cout << "Invertir arreglo - Tiempo de ejecucción promedio: " << rollingAverage << " segundos" << endl;
    cout << "Varianza: " << rollingVariance / 500 << endl;
    cout << "Desviación estándar: " << stdDev << endl;

    delete[] arreglo;
    delete[] tempArray;

    return 0;
}