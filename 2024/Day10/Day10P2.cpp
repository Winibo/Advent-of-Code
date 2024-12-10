#include <bits/stdc++.h>

using namespace std;

vector<string> topMap;

int getTrails(int row, int column, int height = 0) {
    int trails = 0;
    if (row < 0 || row >= topMap.size()) return 0;
    if (column < 0 || column >= topMap[0].length()) return 0;
    if (topMap[row][column] - '0' == height) {
        if (height == 9) {
            return 1;
        } else {
            trails += getTrails(row + 1, column, height + 1);
            trails += getTrails(row - 1, column, height + 1);
            trails += getTrails(row, column + 1, height + 1);
            trails += getTrails(row, column - 1, height + 1);
        }
    }
    return trails;
}


int main()
{
    while (!cin.eof()) {
        string line;
        getline(cin, line);
        topMap.push_back(line);
    }
    int trails = 0;
    for (int i = 0; i < topMap.size(); i++) {
        for (int j = 0; j < topMap.size(); j++) {
            trails += getTrails(i, j);
        }
    }
    cout << trails << endl;
    return 0;
}