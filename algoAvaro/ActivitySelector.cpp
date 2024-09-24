#include <iostream>
#include <vector>

using namespace std;
class Activity{
    private:
        int s;
        int f;
    
    public:
        Activity(int _s, int _f){
            s = _s;
            f = _f;
        }

        int get_s(){
            return s;
        }

        int get_f(){
            return f;
        }

};

vector<Activity> greedy_activity_selector(vector<Activity> Sel){
    int n;
    n = Sel.size();

    vector<Activity> A;
    A.push_back(Sel[0]);
    int k = 1;

    for(int m = 2; m < n; m++){
        if(Sel[m].get_s() >= Sel[k].get_f()){
            A.push_back(Sel[m]);
            k = m;
        }
    }

    return A;
}


int main(){
    vector<Activity> S;
    S.push_back(Activity(1, 4));
    S.push_back(Activity(3, 5));
    S.push_back(Activity(0, 6));
    S.push_back(Activity(5, 7));
    S.push_back(Activity(3, 9));
    S.push_back(Activity(5, 9));
    S.push_back(Activity(6, 10));
    S.push_back(Activity(8, 11));
    S.push_back(Activity(8, 12));
    S.push_back(Activity(2, 14));
    S.push_back(Activity(12, 16));

    vector<Activity> A = greedy_activity_selector(S);
    for(int i = 0; i < A.size(); i++){
        cout << "s = " << A[i].get_s() << " f = " << A[i].get_f() << endl;
    }

    return 0;
}