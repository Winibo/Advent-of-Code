#include "bits/stdc++.h"

using namespace std;

vector<pair<long long, long long>> vertices;

long long convertHex(string hexValue) {
    stringstream result;
    result << hex << hexValue;
    long long finalResult;
    result >> finalResult;
    return finalResult;
}

long long getArea() { //Assumes First and Last Vertex match
    long long answer = 0;
    for (int i = 0; i < vertices.size() - 1; i++) {
        answer += ((vertices[i].first*vertices[i+1].second) - (vertices[i].second*vertices[i+1].first));
    }
    return abs(answer / 2);
}

int main() {
    int x = 0, y = 0;
    vertices.push_back(make_pair(x, y));
    long long answer = 2;
    while (!cin.eof()) {
        string next = "";
        getline(cin, next);
        if (next == "")
            break;
        char direction;
        long long distance;
        string hexValue;
        stringstream nstream(next);
        nstream >> direction >> distance >> hexValue;
        direction = hexValue[hexValue.length() - 2];
        hexValue = hexValue.substr(2,hexValue.length() - 4);
        distance = convertHex(hexValue);
        switch (direction) {
            case '3':
                y -= distance;
                break;
            case '0':
                x += distance;
                break;
            case '1':
                y += distance;
                break;
            case '2':
                x -= distance;
                break;
        }
        answer += distance;
        vertices.push_back(make_pair(x, y));
    }
    cout << getArea() + answer/2 << endl;
    return 0;
}