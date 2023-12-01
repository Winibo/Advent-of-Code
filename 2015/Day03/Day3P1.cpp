#include "bits/stdc++.h"

using namespace std;

map<pair<int, int>, int> visited;

int main()
{
    string input;
    cin >> input;
    int x = 0, y = 0;
    visited[make_pair(0,0)] = 1;
    for (char dir : input) {
        switch (dir) {
            case '^':
                y++;
                break;
            case 'v':
                y--;
                break;
            case '>':
                x++;
                break;
            case '<':
                x--;
                break;
            default:
                cout << "Something broke" << endl;
        }
        visited[make_pair(x, y)]++;
    }
    int answer = 0;
    for (auto visit : visited) {
        answer++;
    }
    cout << answer << endl;
    return 0;
}
