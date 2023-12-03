#include "bits/stdc++.h"

using namespace std;

vector<string> schematic;

vector<int> xdir = {0,  0, 1, -1, -1,  1, 1, -1};
vector<int> ydir = {1, -1, 0,  0, -1, -1, 1,  1};

map<pair<int, int>, vector<int>> gears;

int main() {
    while (!cin.eof()) {
        string row;
        getline(cin, row);
        if (row == "")
            break;
        schematic.push_back(row + '.');
    }
    long long answer = 0;
    for (int rowidx = 0; rowidx < schematic.size(); rowidx++) {
        string row = schematic[rowidx];
        int currentNumber = 0;
        vector<pair<int, int>> gearLocations;
        for (int colidx = 0; colidx < row.length(); colidx++) {
            char column = row[colidx];
           if (isdigit(column)) {
               currentNumber = (currentNumber * 10) + (column - '0');
               for (int diridx = 0; diridx < xdir.size(); diridx++) {
                    int xval = colidx + xdir[diridx];
                    int yval = rowidx + ydir[diridx];
                    if (yval < 0 || yval > schematic.size() -1)
                        continue; //Bounds check
                    if (xval < 0 || xval > schematic[yval].length() - 1)
                        continue; //Bounds check
                    char testValue = schematic[yval][xval];
                    if (testValue == '*') {
                        gearLocations.push_back(make_pair(xval, yval));
                        break;
                    }
               }
           } else {
                sort(gearLocations.begin(), gearLocations.end());
                pair<int, int> previous = make_pair(-1,-1);
                for (pair<int, int> x : gearLocations) {
                    if (x != previous)
                        gears[x].push_back(currentNumber);
                    previous = x;
                }
                gearLocations.clear();
                currentNumber = 0;
           }
        }
    }
    for (auto x : gears) {
        // cout << "Gear at: " << x.first.first << ' ' << x.first.second << endl;
        if (x.second.size() == 2) {
            // cout << "Adding: " << x.second[0] << '*' << x.second[1] << endl;
            answer += x.second[0] * x.second[1];
        }
    }
    cout << answer << endl;
}
