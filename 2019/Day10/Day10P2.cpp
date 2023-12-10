#include "bits/stdc++.h"

using namespace std;

vector<pair<int, int>> asteroids;

pair<int, int> best;

bool thetaSort(double a, double b) {
    if (a < -1.5708 && b < -1.5708)
        return a < b;
    if (a >= -1.5708 && b >= -1.5708)
        return a < b;
    if (a < -1.5708)
        return false;
    return true;
}

bool rSort(pair<int, int> a, pair<int, int> b) {
    return hypot(a.first, a.second) < hypot(b.first, b.second);
}

bool manhattanSort(pair<int, int> a, pair<int, int> b) {
    int aDistance = abs(a.first - best.first) + abs(a.second - best.second);
    int bDistance = abs(b.first - best.first) + abs(b.second - best.second);
    return aDistance < bDistance;
}

int main() {
    int x = 0, y = 0;
    while (!cin.eof()) {
        string row = "";
        getline(cin, row);
        stringstream rowstream(row);
        if (row == "")
            break;
        while (!rowstream.eof()) {
            char next = 'x';
            rowstream >> next;
            if (next == 'x')
                break;
            if (next == '#')
                asteroids.push_back(make_pair(x, y));
            x++;
        }
        x = 0;
        y++;
    }

    map<double,int> bestLines;
    int bestCount = 0;
    for (pair<int, int> asteroid : asteroids) {
        map<double, int> lines;
        for (pair<int, int> test : asteroids) {
            if (test.first == asteroid.first && test.second == asteroid.second)
                continue;
            double angle = atan2(test.second - asteroid.second,  test.first - asteroid.first);
            lines[angle] += 1;
        }
        if (lines.size() > bestCount) {
            best = asteroid;
            bestCount = lines.size();
            bestLines = lines;
        }
    }
    cout << best.first << ' ' << best.second << endl;
    cout << bestCount << endl;

    int vaporized = 0;
    int rotations = 0;
    double correctAngle = 0;
    vector<double> angles;
    for (auto x : bestLines) {
        angles.push_back(x.first);
    }
    sort(angles.begin(), angles.end(), thetaSort); //Sort angles
    while (vaporized < 200) {
        for (double angle : angles) {
            if (rotations < bestLines[angle])
                vaporized++;
            if (vaporized == 200) {
                correctAngle = angle;
                break;
            }
        }
        if (vaporized == 200)
            break;
        rotations++;
    }
    //Find all asteroids with that angle
    vector<pair<int, int>> matchedLine;
    for (pair<int, int> test : asteroids) {
        double angle = atan2(test.second - best.second,  test.first - best.first);
        if (angle == correctAngle) {
            matchedLine.push_back(make_pair(test.first, test.second)); //Find all asteroids on that line
        }
    }
    // for (pair<int, int> asteroid : matchedLine) {
    //     cout << asteroid.first << ' ' << asteroid.second << endl;
    // }
    //This part might be wrong, only had 1 value along the line for my input
    sort(matchedLine.begin(), matchedLine.end(), rSort);

    cout << matchedLine[rotations].first*100 + matchedLine[rotations].second << endl;
    return 0;
}