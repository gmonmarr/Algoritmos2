#include <fstream>
#include <iostream>


using namespace std;

// Definir Tuple como una clase para contener la respuesta, es decir, el mínimo y el máximo del arreglo.

struct Tuple{
    int min;
    int max;
    Tuple(int min, int max){
        this->min = min;
        this->max = max;
    }
    int get_min(){
        return min;
    }
    int get_max(){
        return max;
    }
};

class Tuple maximin(int *A, int low, int high){
    if (low == high){
        return Tuple(A[low], A[low]);

    } else if (low == (high + 1)){
        if (A[low] < A[high]){
            return Tuple(A[low], A[high]);
        }
        else{
            return Tuple(A[high], A[low]);
        }

    } else{
        int mid = (low + high) / 2;
        Tuple left = maximin(A, low, mid);
        Tuple right = maximin(A, mid + 1, high);
        if (left.get_min() < right.get_min()){
            if (left.get_max() < right.get_max()){
                return Tuple(left.get_min(), right.get_max());
            }
            else{
                return Tuple(left.get_min(), left.get_max());
            }
        }
        else{
            if (left.get_max() < right.get_max()){
                return Tuple(right.get_min(), right.get_max());
            }
            else{
                return Tuple(right.get_min(), left.get_max());
            }
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
  
  while (getline(in, s)){
    arreglo[i] = stoi(s);
    cout << arreglo[i] << endl;
    i++;
  }

  Tuple result = maximin(arreglo, 0, n - 1);
  cout << "El mínimo del arreglo es: " << result.get_min() << " y el máximo es: " << result.get_max() << endl;

  return 0;
}
