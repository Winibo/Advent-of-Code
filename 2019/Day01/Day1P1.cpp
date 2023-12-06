#include "bits/stdc++.h"

using namespace std;

int main() {
    int answer = 0;
    while (!cin.eof()) {
        int next = 0;
        cin >> next;
        if (next == 0)
            break;
        answer += next / 3 - 2;
    }
    cout << answer;
}