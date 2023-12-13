#include "bits/stdc++.h"

using namespace std;

vector<string> currentMirror;

int getDifferences(string a, string b) {
    int differences = 0;
    for (int i = 0; i < a.length(); i++) {
        if (a[i] != b[i])
            differences++;
    }
    return differences;
}


int solveRow(int reflectionLine) {
    bool smudges = true;
    if (reflectionLine >= currentMirror.size() - 1)
        return 0; //No horizontal mirroring
    for (int i = reflectionLine + 1; i < (reflectionLine + 1) * 2 && i < currentMirror.size(); i++) { //For every row
        string a = currentMirror[reflectionLine - (i - reflectionLine - 1)], b = currentMirror[i];
        if (a != b) {
            if (!smudges) {
                return solveRow(reflectionLine + 1); //This ain't it
            } else if (getDifferences(a, b) == 1) {
                smudges = false; //Use our smudge and continue
            } else {
                return solveRow(reflectionLine + 1);
            }
        }
    }
    if (smudges)
        return solveRow(reflectionLine + 1); //We *must* find the reflection that needs a smudge
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
    bool smudges = true;
    if (reflectionLine >= currentMirror[0].length() - 1) {
        return 0; //No Vertical mirroring
    }
    for (int i = reflectionLine + 1; i < (reflectionLine + 1) * 2 && i < currentMirror[0].length(); i++) { //For every Column
        string colA = constructColumn(reflectionLine - (i - reflectionLine - 1)), colB = constructColumn(i);
        if (colA != colB) {
            if (!smudges) {
                return solveColumn(reflectionLine + 1);
            } else if (getDifferences(colA, colB) == 1) {
                smudges = false; //Use our smudge to continue attempt
            } else {
                return solveColumn(reflectionLine + 1);
            }
        }
    }
    if (smudges)
        return solveColumn(reflectionLine + 1); //We *must* find a reflection that uses a smudge
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