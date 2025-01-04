#include <bits/stdc++.h>

using namespace std;

int main()
{
    set<vector<int>> locks;
    set<vector<int>> keys;
    
    while (!cin.eof()) {
        bool lock;
        string lockLine;
        getline(cin, lockLine); // First line, determines key/lock
        vector<int> heights(5, 0);
        lock = lockLine == "#####" ? true : false;
        for (int i = 0; i < 5; i++) { // Each lock/key is 5 high
            getline(cin, lockLine);
            for (int j = 0; j < 5; j++) {
                if (lockLine[j] == '#') heights[j]++; // Increase height if there's a #
            }
        }
        getline(cin, lockLine); // Last line, unneeded
        getline(cin, lockLine); // Clear the blank line between locks/keys
        if (lock) locks.insert(heights);
        else keys.insert(heights);
    }
    
    long long answer = 0;
    for (vector<int> lock : locks) {
        for (vector<int> key : keys) {
            bool valid = true;
            for (int i = 0; i < 5; i++) {
                if (key[i] + lock[i] > 5) {
                    valid = false;
                    break;
                }
            }
            if (valid) answer++;
        }
    }
    cout << answer << endl;
    return 0;
}