
#include <iostream>
#include <vector>
#include <algorithm>    //Needed for begin() and end()

using namespace std;

void oddNumbers(vector<int> v){
    cout << "OddNumbers" << endl;
    for_each(v.cbegin(), v.cend(),[](int number){
        if(number % 2 != 0){
            cout << number << " ";
        }
    });
    cout << endl;
}

void multOddTwo(vector<int> v){
    for_each(v.begin(), v.end(), [](int &number){
        if(number%2!=0){
            number *= 2;
        }
    });
    cout << "multOddTwo" << endl;
    for (auto x : v) { cout << x << " ";};
    cout << endl;
}

void changeSize(vector<int> v){
    for_each(v.begin(), v.end(), [&v](int &element){
        element += v.size();
    });
    cout << "changeSize" << endl;
    for (auto x : v) { cout << x << " ";};
    cout << endl;
}


void ownFunc(vector<int> v){
    int outsideData = 100;
    cout << "ownFunc" << endl;
    [&outsideData]{
        cout << outsideData << endl;
        outsideData=200;
        cout << outsideData << endl;
    }();
}

void lambdas(){
    vector<int> v = {1, 3, 4, 5, 6, 7, 8, 9};
    // printing v
    cout << "vector v:" << endl;
    for (auto x : v) { cout << x << " ";};
    cout << endl;

    oddNumbers(v);
    multOddTwo(v);
    changeSize(v);
    ownFunc(v);

}

int main(int argc, const char * argv[]) {
    
    lambdas();
    
    return 0;
}