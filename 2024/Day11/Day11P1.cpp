#include <bits/stdc++.h>

using namespace std;

vector<long long> stones;

int main()
{
    while (!cin.eof()) {
        long long temp;
        cin >> temp;
        stones.push_back(temp);
    }
    
    for (int i = 0; i < 25; i++) {
        vector<long long> newStones;
        for (long long stone : stones) {
            if (stone == 0) {
                newStones.push_back(1);
            } else if (to_string(stone).length() % 2 == 0) {
                string sStone = to_string(stone);
                newStones.push_back(stoi(sStone.substr(0,sStone.length() / 2)));
                newStones.push_back(stoi(sStone.substr(sStone.length() / 2, string::npos)));
            } else {
                newStones.push_back(stone * 2024);
            }
        }
        stones = newStones;
    }
    cout << stones.size() << endl;
    return 0;
}