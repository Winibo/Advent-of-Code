#include "bits/stdc++.h"

using namespace std;

vector<string> currentMirror;

int solveRow(int reflectionLine) {
    if (reflectionLine >= currentMirror.size() - 1)
        return 0; //No horizontal mirroring
    for (int i = reflectionLine + 1; i < (reflectionLine + 1) * 2 && i < currentMirror.size(); i++) { //For every row
        if (currentMirror[reflectionLine - (i - reflectionLine - 1)] != currentMirror[i]) {
            return solveRow(reflectionLine + 1); //This ain't it
        }
    }
    // cout << "Horizontal Reflection at: " << reflectionLine << endl;
    return reflectionLine + 1;
}

string constructColumn(int column) {
    if (column >= currentMirror[0].size()) {
        cout << "Invalid Column: " << column << endl;
        return "";
    }
    string answer = "";
    for (int i = 0; i < currentMirror.size(); i++) {
        answer += currentMirror[i][column];
    }
    return answer;
}


int solveColumn(int reflectionLine) {
    if (reflectionLine >= currentMirror[0].length() - 1) {
        return 0; //No Vertical mirroring
    }
    for (int i = reflectionLine + 1; i < (reflectionLine + 1) * 2 && i < currentMirror[0].length(); i++) { //For every Column
        if (constructColumn(reflectionLine - (i - reflectionLine - 1)) != constructColumn(i)) {
            return solveColumn(reflectionLine + 1);
        }
    }
    // cout << "Vertical Reflection at: " << reflectionLine + 1 << endl;
    return reflectionLine + 1;
}
//Requires Exactly 1 endline after input or it breaks :(
int main() {
    long long rows = 0, columns;
    while (!cin.eof()) {
        string nextLine = "";
        getline(cin, nextLine);
        if (nextLine == "") {
            //Solve
            // cout << "Solving Row" << endl;
            rows += solveRow(0);
            // cout << "Solving Column" << endl;
            columns += solveColumn(0);
            currentMirror.clear();
            continue;
        }
        currentMirror.push_back(nextLine);
    }
    cout << (rows * 100) + columns << endl;
    return 0;
}