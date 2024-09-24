#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

class Result{

private:
    int low;
    int high;
    int sum;

public:
    Result(int low, int high, int sum){
        this->low = low;
        this->high = high;
        this->sum = sum;
    }

    Result(){
        this->low = 0;
        this->high = 0;
        this->sum = 0;
    }

    int get_low(){
        return low;
    }
    int get_high(){
        return high;
    }
    int get_sum(){
        return sum;
    }
};

Result find_max_crossing_subarray(int *A, int low, int mid, int high){
    int maxLeft = 0;
    int maxRight = 0;

    int leftSum = numeric_limits<int>::min();
    int sum = 0;

    for (int i = mid; i >= low; i--){
        sum += A[i];
        if (sum > leftSum){
            leftSum = sum;
            maxLeft = i;
        }
    }

    int rightSum = numeric_limits<int>::min();
    sum = 0;

    for (int j = mid + 1; j <= high; j++){
        sum += A[j];
        if (sum > rightSum){
            rightSum = sum;
            maxRight = j;
        }
    }

    return Result(maxLeft, maxRight, leftSum + rightSum);
}

Result find_maximum_subarray(int *A, int low, int high){
    Result leftResult, rightResult, crossResult;

    if (high == low){
        return Result(low, high, A[low]);
    } else{
        int mid = ceil((low + high) / 2);

        leftResult = find_maximum_subarray(A, low, mid);
        rightResult = find_maximum_subarray(A, mid + 1, high);
        crossResult = find_max_crossing_subarray(A, low, mid, high);

        if (leftResult.get_sum() >= rightResult.get_sum() && leftResult.get_sum() >= crossResult.get_sum()){
            return leftResult;
        } else if (rightResult.get_sum() >= leftResult.get_sum() && rightResult.get_sum() >= crossResult.get_sum()){
            return rightResult;
        } else{
            return crossResult;
        }
    }
}

int main(int argc, char *argv[]){
    int n, i;
    string s;
    ifstream in(argv[1]);
    getline(in, s);
    n = stoi(s);
    int *arreglo = new int[n];
    i = 0;
    while (getline(in, s))
    {
        arreglo[i] = stoi(s);
        cout << arreglo[i] << endl;
        i++;
    }

    Result result = find_maximum_subarray(arreglo, 0, n - 1);
    cout << "La suma del máximo subarray es: " << result.get_sum() << endl;

    return 0;
}