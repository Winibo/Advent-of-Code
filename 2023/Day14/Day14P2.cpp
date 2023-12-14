#include "bits/stdc++.h"

using namespace std;
struct rock {
    bool movable = false;
    int column;
    int row;
    // int idx = -1;
};


vector<string> dish;
vector<rock> rocks;

bool sortVert(rock a, rock b) {
    return a.row < b.row;
}

bool sortHorz(rock a, rock b) {
    return a.column < b.column;
}

bool sortBoth(rock a, rock b) {
    if (a.row != b.row)
        return a.row < b.row;
    return a.column < b.column;
}

void moveVertical(bool north = true) {
    if (north)
        sort(rocks.begin(),rocks.end(), sortVert);
    else 
        sort(rocks.rbegin(),rocks.rend(), sortVert);
    vector<int> columnStop(dish[0].length(), north ? 0 : dish.size() - 1);
    for (rock& x : rocks) {
        if (x.movable) {
            x.row = columnStop[x.column];
        }
        columnStop[x.column] = north ? (x.row + 1) : (x.row - 1);
    }
}

void moveHorizontal(bool west = true) { //Remember east is right
    if (west)
        sort(rocks.begin(),rocks.end(), sortHorz);
    else
        sort(rocks.rbegin(), rocks.rend(), sortHorz);
    vector<int> columnStop(dish.size(), west ? 0 : dish[0].length() - 1);
    for (rock& x : rocks) {
        if (x.movable) {
            x.column = columnStop[x.row];
        }
        columnStop[x.row] = west ? (x.column + 1) : (x.column - 1);
    }
}


int main() {
    int row = 0;
    while (!cin.eof()) {
        string newLine = "";
        getline(cin, newLine);
        if (newLine == "")
            break;
        dish.push_back(newLine);
        for (int i = 0; i < newLine.length(); i++) {
            if (newLine[i] == 'O') {
                rock newRock;
                newRock.movable = true;
                newRock.column = i;
                newRock.row = row;
                // newRock.idx = rocks.size();
                rocks.push_back(newRock);
            } else if (newLine[i] == '#') {
                rock newRock;
                newRock.column = i;
                newRock.row = row;
                rocks.push_back(newRock);
            }
        }
        row++;
    }
    vector<pair<vector<rock>,int>> previous;
    for (int i = 0; i < 1000000000; i++) {
        if (i % 100 == 0)
            cout << "Iteration: " << i << endl;
        moveVertical(); //Move all rocks North
        moveHorizontal(); //Move all rocks West
        moveVertical(false); //Move all rocks South
        moveHorizontal(false); //Move all rocks East
        sort(rocks.begin(), rocks.end(), sortBoth);
        for (auto prev : previous) {
            bool match = true;
            for (int j = 0; j < rocks.size(); j++) {
                if (rocks[j].row != prev.first[j].row || rocks[j].column != prev.first[j].column) {
                    match = false;
                    break;
                }
            }
            if (match) {
                cout << "Found match" << endl;
                cout << "Iterations: " << prev.second << ' ' << i << endl;
                int remainingIterations = (1000000000 - i - 1) % (i - prev.second);
                int answer = 0;
                for (rock x : previous[prev.second + remainingIterations].first) {
                    if (x.movable)
                        answer += dish.size() - x.row;
                }
                cout << answer << endl;
                return 0;
            }
        }
        previous.push_back(make_pair(rocks, i));
    }
    
    int answer = 0;
    for (rock x : rocks) {
        if (x.movable) {
            answer += dish.size() - x.row;
        }
    }
    cout << answer << endl;
    return 0;
}