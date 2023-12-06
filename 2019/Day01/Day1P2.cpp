#include "bits/stdc++.h"

using namespace std;

int main() {
    int answer = 0;
    while (!cin.eof()) {
        int next = 0;
        cin >> next;
        if (next == 0)
            break;
        while (next > 0) {
            next = max((next / 3 - 2), 0);
            answer += next;
            
        }
    }
    cout << answer << endl;
}