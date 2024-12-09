
#include <bits/stdc++.h>

using namespace std;

int main()
{
    string filesystem;
    cin >> filesystem;
    map<int, pair<int, int>> result;
    int right = filesystem.length() - 1;
    if (filesystem.length() % 2 == 0) {
        right -= 1;
    }
    int finalBlockNum = ((filesystem.length() + 1) / 2) - 1;
    map<int, int> offsets;
    while (finalBlockNum >= 0) {
        int finalBlockSize = filesystem[right] - '0';
        int left = 1, location = filesystem[0] - '0';
        bool moved = false;
        while (left < right) {
            if (filesystem[left] - '0' >= finalBlockSize) {
                for (auto x : offsets) {
                    if (x.first <= location) {
                        location += x.second;
                    }
                }
                filesystem[left] = filesystem[left] - finalBlockSize;
                result[location] = make_pair(finalBlockSize, finalBlockNum);
                moved = true;
                offsets[location] = finalBlockSize;
                break;
            }
            location += filesystem[left] - '0';
            location += filesystem[left + 1] - '0';
            left += 2;
        }
        if (!moved) {
            location = location - finalBlockSize;
            for (auto x : offsets) {
                if (x.first <= location) {
                    location += x.second;
                }
            }
            result[location] = make_pair(finalBlockSize, finalBlockNum);
        }
        right = right - 2;
        finalBlockNum--;
    }
    long long answer = 0;
    for (auto x : result) {
        for (int i = 0; i < x.second.first; i++) {
            answer += x.second.second * (x.first + i);
        }
    }
    cout << answer << endl;
    return 0;
}