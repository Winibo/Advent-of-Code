#include "bits/stdc++.h"

using namespace std;

vector<pair<int, int>> asteroids;

int main() {
    int x = 0, y = 0;
    while (!cin.eof()) {
        string row = "";
        getline(cin, row);
        stringstream rowstream(row);
        if (row == "")
            break;
        while (!rowstream.eof()) {
            char next = 'x';
            rowstream >> next;
            if (next == 'x')
                break;
            if (next == '#')
                asteroids.push_back(make_pair(x, y));
            x++;
        }
        x = 0;
        y++;
    }

    pair<int, int> best;
    int bestCount = 0;
    for (pair<int, int> asteroid : asteroids) {
        map<pair<int, int>, int> lines;
        for (pair<int, int> test : asteroids) {
            if (test.first == asteroid.first && test.second == asteroid.second)
                continue;
            int run = test.first - asteroid.first, rise = test.second - asteroid.second;
            int denom = gcd(run, rise);
            if (denom != 0) {
                run = run / denom;
                rise = rise / denom;
            }
            lines[make_pair(run, rise)] += 1;
        }
        if (lines.size() > bestCount) {
            best = asteroid;
            bestCount = lines.size();
        }
    }
    cout << best.first << ' ' << best.second << endl;
    cout << bestCount << endl;
    return 0;
}