#include "bits/stdc++.h"

using namespace std;

vector<string> schematic;

vector<int> xdir = {0,  0, 1, -1, -1,  1, 1, -1};
vector<int> ydir = {1, -1, 0,  0, -1, -1, 1,  1};

int main() {
    while (!cin.eof()) {
        string row;
        getline(cin, row);
        if (row == "")
            break;
        schematic.push_back(row);
    }
    int answer = 0;
    for (int rowidx = 0; rowidx < schematic.size(); rowidx++) {
        string row = schematic[rowidx];
        int currentNumber = 0;
        bool currentValid = false;
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
                    if (testValue != '.' && !isdigit(testValue)) {
                        currentValid = true;
                        break;
                    }
               }
           } else {
                if (currentValid) {
                    // cout << "Adding: " << currentNumber << endl;
                    answer += currentNumber;
                }
                currentValid = false;
                currentNumber = 0;
           }
        }
        if (currentNumber != 0 && currentValid) {
            answer += currentNumber;
        }
    }
    cout << answer << endl;
}
