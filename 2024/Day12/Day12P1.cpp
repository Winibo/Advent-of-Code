#include <bits/stdc++.h>

using namespace std;

vector<string> garden;

pair<long long, long long> getPrice(int row, int column, char value, map<pair<int, int>, bool>& seen) {
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
        if (adjRow < 0 || adjRow >= garden.size() || adjCol < 0 || adjCol >= garden[0].length() || garden[adjRow][adjCol] != value) {
            data.second++;
            continue;
        }
        pair<long long, long long> tempData = getPrice(adjRow, adjCol, value, seen);
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
            map<pair<int, int>, bool> seen;
            auto temp = getPrice(i, j, garden[i][j], seen);
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