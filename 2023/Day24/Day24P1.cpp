#include "bits/stdc++.h"

using namespace std;

const long long minArea = 200000000000000;
const long long maxArea = 400000000000000;

struct hailStone {
    double slope;
    double intercept;
    double px, py, pz;
    double vx, vy, vz;
};

vector<hailStone> stones;


bool findIntersection(hailStone a, hailStone b) { //Returns true if intersection in range, false otherwise
    if (a.slope == b.slope) return false; //Parallel? Unless on same line, assuming that won't happen
    double newSlope = a.slope - b.slope;
    double newIntercept = b.intercept - a.intercept; 
    double xPos = newIntercept / newSlope; //Can't be 0, or they would be parallel
    double yPos = xPos * a.slope + a.intercept; //Doesn't matter which we use
    bool possible = minArea <= xPos && xPos <= maxArea && minArea <= yPos && yPos <= maxArea;
    bool validTime = ((xPos - a.px) / a.vx) >= 0 && ((xPos - b.px) / b.vx) >= 0;
    return possible && validTime;
}

int main() {
    while (!cin.eof()) {
        hailStone test;
        double px = -1, py, pz;
        double vx, vy, vz;
        char temp;
        cin >> px >> temp >> py >> temp >> pz >> temp;
        cin >> vx >> temp >> vy >> temp >> vz;
        if (px == -1) {
            break;
        }
        test.px = px;
        test.py = py;
        test.pz = pz;
        test.vx = vx;
        test.vy = vy;
        test.vz = vz;
        test.slope = vy / vx;
        test.intercept = py - (test.slope * px);
        stones.push_back(test);
    }

    long long answer = 0;
    for (int i = 0; i < stones.size(); i++) {
        for (int j = i+1; j < stones.size(); j++) {
            answer += findIntersection(stones[i], stones[j]);
        }
    }
    cout << answer << endl;
    return 0;
}