#include "bits/stdc++.h"

using namespace std;

vector<pair<int, int>> vertices;

int getArea() { //Assumes First and Last Vertex match
    int answer = 0;
    for (int i = 0; i < vertices.size() - 1; i++) {
        answer += ((vertices[i].first*vertices[i+1].second) - (vertices[i].second*vertices[i+1].first));
    }
    return abs(answer / 2);
}

int main() {
    int x = 0, y = 0;
    vertices.push_back(make_pair(x, y));
    int answer = 2;
    while (!cin.eof()) {
        string next = "";
        getline(cin, next);
        if (next == "")
            break;
        char direction;
        int distance;
        stringstream nstream(next);
        nstream >> direction >> distance;
        switch (direction) {
            case 'U':
                y -= distance;
                break;
            case 'R':
                x += distance;
                break;
            case 'D':
                y += distance;
                break;
            case 'L':
                x -= distance;
                break;
        }
        answer += distance;
        vertices.push_back(make_pair(x, y));
    }
    cout << getArea() + answer/2 << endl;
    return 0;
}