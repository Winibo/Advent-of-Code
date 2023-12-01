#include "bits/stdc++.h"

using namespace std;

int main()
{
    string input;
    cin >> input;
    int currentFloor = 0;
    for (char x : input) {
        if (x == '(') {
            currentFloor++;
        } else {
            currentFloor--;
        }
    }
    cout << currentFloor;
    return 0;
}
