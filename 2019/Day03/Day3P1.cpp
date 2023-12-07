#include "bits/stdc++.h"

using namespace std;


map<pair<int, int>, int> wire;

int main() {
    int x = 0, y = 0;
    string firstWire, secondWire;
    getline(cin, firstWire);
    getline(cin, secondWire);
    stringstream fwirestream(firstWire);
    stringstream swirestream(secondWire);
    while (!fwirestream.eof()) {
        char direction, temp;
        int length;
        fwirestream >> direction >> length >> temp;
        switch(direction) {
            case 'R':
                for (int i = 0; i < length; i++) {
                    x++;
                    // cout << "Adding: " << x << ',' << y << endl;
                    wire[make_pair(x,y)] += 1;
                }
                break;
            case 'L':
                for (int i = 0; i < length; i++) {
                    x--;
                    // cout << "Adding: " << x << ',' << y << endl;
                    wire[make_pair(x,y)] += 1;
                }
                break;
            case 'U':
                for (int i = 0; i < length; i++) {
                    y++;
                    // cout << "Adding: " << x << ',' << y << endl;
                    wire[make_pair(x,y)] += 1;
                }
                break;
            case 'D':
                for (int i = 0; i < length; i++) {
                    y--;
                    // cout << "Adding: " << x << ',' << y << endl;
                    wire[make_pair(x,y)] += 1;
                }
                break;
        }
    }
    x = 0; y = 0;
    int closest = INT_MAX;
    while (!swirestream.eof()) {
        char direction, temp;
        int length;
        swirestream >> direction >> length >> temp;
        switch(direction) {
            case 'R':
                for (int i = 0; i < length; i++) {
                    x++;
                    if (wire.find(make_pair(x, y)) != wire.end()) {
                        // cout << "Checking: " << x << ',' << y << endl;
                        if (abs(x) + abs(y) < closest) {
                            closest = abs(x) + abs(y);
                        }
                    }
                }
                break;
            case 'L':
                for (int i = 0; i < length; i++) {
                    x--;
                    if (wire.find(make_pair(x, y)) != wire.end()) {
                        // cout << "Checking: " << x << ',' << y << endl;
                        if (abs(x) + abs(y) < closest) {
                            closest = abs(x) + abs(y);
                        }
                    }
                }
                break;
            case 'U':
                for (int i = 0; i < length; i++) {
                    y++;
                    if (wire.find(make_pair(x, y)) != wire.end()) {
                        // cout << "Checking: " << x << ',' << y << endl;
                        if (abs(x) + abs(y) < closest) {
                            closest = abs(x) + abs(y);
                        }
                    }
                }
                break;
            case 'D':
                for (int i = 0; i < length; i++) {
                    y--;
                    if (wire.find(make_pair(x, y)) != wire.end()) {
                        // cout << "Checking: " << x << ',' << y << endl;
                        if (abs(x) + abs(y) < closest) {
                            closest = abs(x) + abs(y);
                        }
                    }
                }
                break;
        }
    }
    cout << closest << endl;
    return 0;
}