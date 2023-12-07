#include "bits/stdc++.h"

using namespace std;

bool valid(int i) {
    string value = to_string(i);
    bool pair = false, currentPair = false;
    for (int i = 0; i < value.length(); i++) {
        if (i != 0 && value[i] < value[i-1])
            return false;
        if (i != 0 && value[i] == value[i-1])
            currentPair = true;
        if (i != 0 && i != 1 && value[i] == value[i-1] && value[i] == value[i-2])
            currentPair = false;
        if (i != 0 && (value[i] != value[i-1] || i == value.length()-1) && !pair)
            pair = currentPair;
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