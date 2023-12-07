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
    int totalDistance = 0;
    while (!fwirestream.eof()) {
        char direction, temp;
        int length;
        fwirestream >> direction >> length >> temp;
        switch(direction) {
            case 'R':
                for (int i = 0; i < length; i++) {
                    x++;
                    totalDistance++;
                    // cout << "Adding: " << x << ',' << y << endl;
                    wire[make_pair(x,y)] = min(totalDistance, wire.find(make_pair(x, y)) != wire.end() ? wire[make_pair(x, y)] : INT_MAX);
                }
                break;
            case 'L':
                for (int i = 0; i < length; i++) {
                    x--;
                    totalDistance++;
                    // cout << "Adding: " << x << ',' << y << endl;
                    wire[make_pair(x,y)] = min(totalDistance, wire.find(make_pair(x, y)) != wire.end() ? wire[make_pair(x, y)] : INT_MAX);
                }
                break;
            case 'U':
                for (int i = 0; i < length; i++) {
                    y++;
                    totalDistance++;
                    // cout << "Adding: " << x << ',' << y << endl;
                    wire[make_pair(x,y)] = min(totalDistance, wire.find(make_pair(x, y)) != wire.end() ? wire[make_pair(x, y)] : INT_MAX);
                }
                break;
            case 'D':
                for (int i = 0; i < length; i++) {
                    y--;
                    totalDistance++;
                    // cout << "Adding: " << x << ',' << y << endl;
                    wire[make_pair(x,y)] = min(totalDistance, wire.find(make_pair(x, y)) != wire.end() ? wire[make_pair(x, y)] : INT_MAX);
                }
                break;
        }
    }
    x = 0; y = 0, totalDistance = 0;
    int closest = INT_MAX;
    while (!swirestream.eof()) {
        char direction, temp;
        int length;
        swirestream >> direction >> length >> temp;
        switch(direction) {
            case 'R':
                for (int i = 0; i < length; i++) {
                    x++;
                    totalDistance++;
                    if (wire.find(make_pair(x, y)) != wire.end()) {
                        // cout << "Checking: " << x << ',' << y << endl;
                        if (totalDistance + wire[make_pair(x, y)] < closest) {
                            closest = totalDistance + wire[make_pair(x, y)];
                        }
                    }
                }
                break;
            case 'L':
                for (int i = 0; i < length; i++) {
                    x--;
                    totalDistance++;
                    if (wire.find(make_pair(x, y)) != wire.end()) {
                        // cout << "Checking: " << x << ',' << y << endl;
                        if (totalDistance + wire[make_pair(x, y)] < closest) {
                            closest = totalDistance + wire[make_pair(x, y)];
                        }
                    }
                }
                break;
            case 'U':
                for (int i = 0; i < length; i++) {
                    y++;
                    totalDistance++;
                    if (wire.find(make_pair(x, y)) != wire.end()) {
                        // cout << "Checking: " << x << ',' << y << endl;
                        if (totalDistance + wire[make_pair(x, y)] < closest) {
                            closest = totalDistance + wire[make_pair(x, y)];
                        }
                    }
                }
                break;
            case 'D':
                for (int i = 0; i < length; i++) {
                    y--;
                    totalDistance++;
                    if (wire.find(make_pair(x, y)) != wire.end()) {
                        // cout << "Checking: " << x << ',' << y << endl;
                        if (totalDistance + wire[make_pair(x, y)] < closest) {
                            closest = totalDistance + wire[make_pair(x, y)];
                        }
                    }
                }
                break;
        }
    }
    cout << closest << endl;
    return 0;
}