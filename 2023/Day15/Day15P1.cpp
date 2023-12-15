#include "bits/stdc++.h"

using namespace std;

long long fHash(string in) {
    long long result = 0;
    for (char x : in) {
        result += x;
        result *= 17;
        result %= 256;
    }
    return result;
}


int main() {
    long long answer = 0;
    while (!cin.eof()) {
        string next = "";
        getline(cin, next, ',');
        answer += fHash(next);
    }
    cout << answer << endl;
    return 0;
}