#include <bits/stdc++.h>

using namespace std;

map<char, vector<pair<int, int>>> antenna;

map<pair<int, int>, bool> antipodes;

void getAntipodes(vector<pair<int,int>>& locations, int rows, int columns) {
    for (int i = 0; i < locations.size(); i++) {
        for (int j = i + 1; j < locations.size(); j++) {
            pair<int, int> diff = make_pair(locations[i].first - locations[j].first, locations[i].second - locations[j].second);
            diff.first = diff.first / gcd(diff.first, diff.second);
            diff.second = diff.second / gcd(diff.first, diff.second);
            pair<int, int> a = locations[i];
            pair<int, int> b = locations[j];
            while (a.first >= 0 && a.first <= rows && a.second >= 0 && a.second <= columns) {
                antipodes[a] = true;
                a.first += diff.first;
                a.second += diff.second;
            }
            while (b.first >= 0 && b.first <= rows && b.second >= 0 && b.second <= columns) {
                antipodes[b] = true;
                b.first -= diff.first;
                b.second -= diff.second;
            }
        }
    }
}

int main()
{
    int row = 0, column = 0;
    while (!cin.eof()) {
        string line;
        getline(cin, line);
        for (int column = 0; column < line.length(); column++) {
            if (line[column] == '.') continue;
            antenna[line[column]].push_back(make_pair(row, column));
        }
        column = line.length();
        row++;
    }
    
    for (auto x : antenna) {
        vector<pair<int, int>> data = x.second;
        getAntipodes(data, row - 1, column - 1);
    }
    cout << antipodes.size() << endl;
    return 0;
}