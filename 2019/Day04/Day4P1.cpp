#include "bits/stdc++.h"

using namespace std;

bool valid(int i) {
    string value = to_string(i);
    bool pair = false;
    for (int i = 0; i < value.length(); i++) {
        if (i != 0 && value[i] < value[i-1])
            return false;
        if (i != 0 && value[i] == value[i-1])
            pair = true;
    }
    return pair;
}

int main() {
    int minValue, maxValue;
    char temp;
    cin >> minValue >> temp >> maxValue;
    int count = 0;
    for (int i = minValue; i < maxValue+1; i++) {
        if (valid(i)) {
            count++;
        }
    }
    cout << count << endl;
    return 0;
}