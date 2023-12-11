#include "bits/stdc++.h"

using namespace std;

vector<string> universe;

vector<pair<long long, long long>> galaxyLocations; //Stored row, column

long long expansionAmount = 999999;

long long taxicab(int first, int second) {
    pair<long long, long long> a = galaxyLocations[first], b = galaxyLocations[second];
    return abs(a.first - b.first) + abs(a.second - b.second);
}


int main() {

    long long rowOffset = 0;
    while (!cin.eof()) {
        string nextLine = "";
        getline(cin, nextLine);
        if (nextLine == "")
            break;
        int location = nextLine.find('#');
        if (location == string::npos) {
            rowOffset += expansionAmount;
        }
        while (location != string::npos) {
            galaxyLocations.push_back(make_pair(universe.size() + rowOffset, location)); //Column still wrong
            location = nextLine.find('#', location + 1);
        }
        universe.push_back(nextLine); //Add row
    }
    //Account for column expansion
    long long columnOffset = 0;
    for (int column = 0; column < universe[0].size(); column++) {
        bool expandColumn = true;
        for (int row = 0; row < universe.size(); row++) {
            if (universe[row][column] == '#') {
                expandColumn = false;
                break;
            }
        }
        if (expandColumn) {
            for (int galaxy = 0; galaxy < galaxyLocations.size(); galaxy++) {
                if (galaxyLocations[galaxy].second > column + columnOffset) {
                    galaxyLocations[galaxy].second += expansionAmount; //Expand all columns
                }
            }
            columnOffset += expansionAmount;
        }
    }
    //Find galaxies
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