#include "bits/stdc++.h"

using namespace std;

map<pair<int, int>, int> visited;

int main()
{
    string input;
    cin >> input;
    int x = 0, y = 0;
    int x2 = 0, y2 = 0;
    visited[make_pair(0,0)] = 1;
    bool santa = true;
    for (char dir : input) {
        switch (dir) {
            case '^':
                if (santa)
                    y++;
                else
                    y2++;
                break;
            case 'v':
                if (santa)
                    y--;
                else
                    y2--;
                break;
            case '>':
                if (santa)
                    x++;
                else
                    x2++;
                break;
            case '<':
                if (santa)
                    x--;
                else
                    x2--;
                break;
            default:
                cout << "Something broke" << endl;
        }
        if (santa)
            visited[make_pair(x, y)] = visited[make_pair(x, y)] + 1;
        else
            visited[make_pair(x2, y2)] = visited[make_pair(x2, y2)] + 1;
        santa = !santa;
    }
    int answer = 0;
    for (auto visit : visited) {
        answer++;
    }
    cout << answer << endl;
    return 0;
}
