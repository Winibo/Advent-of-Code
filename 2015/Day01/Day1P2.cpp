#include "bits/stdc++.h"

using namespace std;

int main()
{
    string input;
    cin >> input;
    int currentFloor = 0;
    int step = 1;
    for (char x : input) {
        if (x == '(') {
            currentFloor++;
        } else {
            currentFloor--;
        }
        if (currentFloor < 0) {
            break;
        }
        step++;
    }
    cout << currentFloor << endl;
    cout << step;
    return 0;
}
