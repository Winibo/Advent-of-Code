#include "bits/stdc++.h"

using namespace std;

vector<string> mapGrid;

map<pair<int, int>, vector<int>> visited; //Row, Column order, stores direction of travel

void followPath(pair<int, int> start, int direction) { //Row, Column order, 0,1,2,3 -> N,E,S,W (U,R,D,L)
    //Repeat until we fall off the grid
    while (start.first >= 0 && start.first < mapGrid.size() && start.second >= 0 && start.second < mapGrid[0].length()) {
        for (int i : visited[start]) {
            if (i == direction)
                return; //Loop detection
        }
        visited[start].push_back(direction); //Add direction to list
        if (mapGrid[start.first][start.second] == '/') {
            switch (direction) {
                case 0:
                    direction = 1;
                    break;
                case 1:
                    direction = 0;
                    break;
                case 2:
                    direction = 3;
                    break;
                case 3:
                    direction = 2;
                    break;
            }
        } else if (mapGrid[start.first][start.second] == '\\') {
            switch (direction) {
                case 0:
                    direction = 3;
                    break;
                case 1:
                    direction = 2;
                    break;
                case 2:
                    direction = 1;
                    break;
                case 3:
                    direction = 0;
                    break;
            }
        } else if (mapGrid[start.first][start.second] == '|') {
            switch (direction) {
                case 1:
                case 3:
                    start.first--;
                    followPath(start, 0);
                    start.first += 2;
                    followPath(start, 2);
                    return; //Nothing more to do here
                case 0:
                case 2:
                    break;
            }
        } else if ((mapGrid[start.first][start.second] == '-')) {
            switch (direction) {
                case 0:
                case 2:
                    start.second--;
                    followPath(start, 3);
                    start.second += 2;
                    followPath(start, 1);
                    return; //Nothing more to do here
                case 1:
                case 3:
                    break;
            }
        }
        
        switch (direction) {
            case 0:
                start.first--;
                break;
            case 1:
                start.second++;
                break;
            case 2:
                start.first++;
                break;
            case 3:
                start.second--;
                break;
        }
    }
}


int main() {
    while (!cin.eof()) {
        string next = "";
        getline(cin, next);
        if (next == "")
            break;
        mapGrid.push_back(next);
    }
    int bestAnswer = 0;
    for (int row = 0; row < mapGrid.size(); row++) {
        //BOTH sides
        visited.clear();
        followPath(make_pair(row,0), 1);
        if (visited.size() > bestAnswer)
            bestAnswer = visited.size();
        visited.clear();
        followPath(make_pair(row,mapGrid[0].length() - 1), 3);
        if (visited.size() > bestAnswer)
            bestAnswer = visited.size();
    }
    for (int column = 0; column < mapGrid[0].length(); column++) {
        //BOTH sides
        visited.clear();
        followPath(make_pair(0,column), 2);
        if (visited.size() > bestAnswer)
            bestAnswer = visited.size();
        visited.clear();
        followPath(make_pair(mapGrid.size() - 1, column), 0);
        if (visited.size() > bestAnswer)
            bestAnswer = visited.size();
    }
    cout << bestAnswer << endl;
    return 0;
}