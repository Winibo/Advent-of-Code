#include <bits/stdc++.h>

using namespace std;

map<long long, long long> lookup;

int main()
{
    while (!cin.eof()) {
        long long temp;
        cin >> temp;
        lookup[temp] += 1;
    }
    
    for (int i = 0; i < 75; i++) {
        map<long long, long long> newStones;
        for (auto stone : lookup) {
            if (stone.first == 0) {
                newStones[1] += stone.second;
            } else if (to_string(stone.first).length() % 2 == 0) {
                string sStone = to_string(stone.first);
                newStones[stoi(sStone.substr(0,sStone.length() / 2))] += stone.second;
                newStones[stoi(sStone.substr(sStone.length() / 2, string::npos))] += stone.second;
            } else {
                newStones[stone.first * 2024] += stone.second;
            }
        }
        lookup = newStones;
    }
    long long answer = 0;
    for (auto x : lookup) {
        answer += x.second;
    }
    cout << answer << endl;
    return 0;
}