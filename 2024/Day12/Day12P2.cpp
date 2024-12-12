#include <bits/stdc++.h>

using namespace std;

vector<string> garden;

int getSide(int row, int column, int direction, char value, map<tuple<int, int, int>, bool>& visited) {
    if (visited[make_tuple(row,column,direction)] == true) {
        return 0;
    }
    // Return 0 if we've counted this side already or are out of bounds
    if (row < 0 || row >= garden.size() || column < 0 || column >= garden[0].length()) {
        return 0;
    }
    // Return 0 if we're in a different range
    if (garden[row][column] != value) {
        return 0;
    }
    int nRow = row, nCol = column;
    switch (direction) {
        case 0: // Up
            nRow -= 1;
            break;
        case 1: // Down
            nRow += 1;
            break;
        case 2: // Left
            nCol -= 1;
            break;
        case 3: // Right
            nCol += 1;
            break;
    }
    // Return 0 if it's not a side
    if (!(nRow < 0 || nRow >= garden.size() || nCol < 0 || nCol >= garden[0].length() || garden[nRow][nCol] != value)) {
        return 0;
    }
    visited[make_tuple(row,column,direction)] = true;
    // Add everything in the same direction to the visited list, so we don't double count
    switch (direction) {
        case 0: // Travel left and right
        case 1:
            getSide(row, column + 1, direction, value, visited);
            getSide(row, column - 1, direction, value, visited);
            break;
        case 2: // Travel up and down
        case 3:
            getSide(row + 1, column, direction, value, visited);
            getSide(row - 1, column, direction, value, visited);
            break;
    }
    return 1;
}

pair<long long, long long> getPrice(int row, int column, char value, map<pair<int, int>, bool>& seen, map<tuple<int, int, int>, bool>& visited) {
    int dr[4] = {0, 0,1,-1};
    int dc[4] = {1,-1,0, 0};
    if (seen[make_pair(row, column)] == true) {
        return make_pair(0,0); //Already Counted
    }
    pair<long long, long long> data = make_pair(0, 0); // Area, Perimeter
    if (garden[row][column] != value) {
        return data;
    }
    seen[make_pair(row, column)] = true;
    data.first += 1;
    for (int i = 0; i < 4; i++) {
        int adjRow = row + dr[i], adjCol = column + dc[i];
        data.second += getSide(row, column, i, value, visited);
        if (adjRow < 0 || adjRow >= garden.size() || adjCol < 0 || adjCol >= garden[0].length() || garden[adjRow][adjCol] != value) {
            continue;
        }
        pair<long long, long long> tempData = getPrice(adjRow, adjCol, value, seen, visited);
        data.first += tempData.first;
        data.second += tempData.second;
    }
    return data;
}

int main()
{
    while (!cin.eof()) {
        string temp;
        getline(cin, temp);
        garden.push_back(temp);
    }
    long long price = 0;
    for (int i = 0; i < garden.size(); i++) {
        for (int j = 0; j < garden[0].length(); j++) {
            if (garden[i][j] == '.') continue;
            map<tuple<int, int, int>, bool> visited;
            map<pair<int, int>, bool> seen;
            auto temp = getPrice(i, j, garden[i][j], seen, visited);
            cout << garden[i][j] << ':' << temp.first * temp.second << endl;
            for (auto x : seen) {
                if (!x.second) continue;
                garden[x.first.first][x.first.second] = '.';
            }
            price += temp.first * temp.second;
        }
    }
    cout << price << endl;
    return 0;
}