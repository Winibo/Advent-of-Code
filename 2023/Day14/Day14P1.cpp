#include "bits/stdc++.h"

using namespace std;
struct rock {
    bool movable = false;
    int column;
    int row;
};


vector<string> dish;
vector<rock> rocks;

bool sortVert(rock a, rock b) {
    return a.row < b.row;
}

bool sortHorz(rock a, rock b) {
    return a.column < b.column;
}

void moveVertical(bool north = true) {

    sort(rocks.begin(),rocks.end(), sortVert);
    vector<int> columnStop(dish[0].length(), 0);
    for (rock& x : rocks) {
        if (x.movable) {
            x.row = columnStop[x.column];
        }
        columnStop[x.column] = x.row + 1;
    }
}

void moveHorizontal(bool east = true) { //Remember east is right

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
    moveVertical(); //Move all rocks north
    // sort(rocks.begin(),rocks.end(), sortHorz);
    int answer = 0;
    for (rock x : rocks) {
        if (x.movable) {
            // cout << "Rock: " << x.row << ' ' << x.column << endl;
            // cout << "Load: " << dish.size() - x.row << endl;
            answer += dish.size() - x.row;
        }
    }
    cout << answer << endl;
    return 0;
}