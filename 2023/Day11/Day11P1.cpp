#include "bits/stdc++.h"

using namespace std;

vector<string> universe;

vector<pair<int, int>> galaxyLocations; //Stored row, column

long long taxicab(int first, int second) {
    pair<int, int> a = galaxyLocations[first], b = galaxyLocations[second];
    return abs(a.first - b.first) + abs(a.second - b.second);
}


int main() {
    while (!cin.eof()) {
        string nextLine = "";
        getline(cin, nextLine);
        if (nextLine == "")
            break;
        
        if (nextLine.find('#') == string::npos)
            universe.push_back(nextLine); //Add additional blank row
        universe.push_back(nextLine); //Add row
    }
    //Expand Columns
    //Note this is in reverse since we have to insert data
    for (int column = universe[0].size() - 1; column >= 0; column--) {
        bool expandColumn = true;
        for (int row = 0; row < universe.size(); row++) {
            if (universe[row][column] == '#') {
                expandColumn = false;
                break;
            }
        }
        if (expandColumn) {
            for (int row = 0; row < universe.size(); row++) {
                universe[row] = universe[row].substr(0, column + 1) + universe[row].substr(column, string::npos);
            }
        }
    }
    for (int row = 0; row < universe.size(); row++) {
        for (int column = 0; column < universe[row].size(); column++) {
            if (universe[row][column] == '#') {
                galaxyLocations.push_back(make_pair(row, column));
            }
        }
    }
    //Shortest path is taxicab distance
    long long answer = 0;
    for (int i = 0; i < galaxyLocations.size(); i++) {
        for (int j = i + 1; j < galaxyLocations.size(); j++) { //Don't double count
            answer += taxicab(i, j);
        }
    }
    cout << answer << endl;
    return 0;
}