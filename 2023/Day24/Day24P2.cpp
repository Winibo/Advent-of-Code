#include "bits/stdc++.h"

using namespace std;


//Any solution I did involving a system of equations would feel like (or be) cheating to me
//Since a: I don't know anything about matrices, and b: I'd either have to copy someone's answer, or use a solver (I do this to practice writing code, not practice using someone elses).
//Instead I brute force the solution. I still needed the aoc reddit's help to figure out how to achieve this though.
//In specific, My code is based on these observations https://old.reddit.com/r/adventofcode/comments/18pptor/2023_day_24_part_2java_is_there_a_trick_for_this/kepufsi/?context=3
//(I also cheat and assume that looking at 3 stones is sufficient since we know it is from the system of equations solution)

struct hailStone {
    double slope;
    double intercept;
    double px, py, pz;
    double vx, vy, vz;
};

vector<hailStone> stones;

const long long minVel = -1000;
const long long maxVel = 1000;

pair<long long, long long> findIntersection(hailStone a, hailStone b) { //Returns true if intersection in range, false otherwise
    if (a.slope == b.slope) {
        return make_pair(-1, -1);
    }
    
    double newSlope = a.slope - b.slope;
    double newIntercept = b.intercept - a.intercept; 
    long long xPos = newIntercept / newSlope; //Can't be 0, or they would be parallel
    long long yPos = xPos * a.slope + a.intercept; //Doesn't matter which we use
    bool validTime = ((xPos - a.px) / a.vx) >= 0 && ((xPos - b.px) / b.vx) >= 0;
    return make_pair(xPos, yPos);
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

    long long xVel, yVel, zVel; //Rock throw velocities

    for (xVel = minVel; xVel < maxVel; xVel++) {
        for (yVel = minVel; yVel < maxVel; yVel++) {
            hailStone a = stones[0]; //You may need to play around with these indices, 0,1,2 found no solution, but 0,2,3 does.
            a.vx -= xVel;
            a.vy -= yVel;
            a.slope = a.vy / a.vx;
            a.intercept = a.py - (a.slope * a.px);
            hailStone b = stones[2];
            b.vx -= xVel;
            b.vy -= yVel;
            b.slope = b.vy / b.vx;
            b.intercept = b.py - (b.slope * b.px);
            hailStone c = stones[3];
            c.vx -= xVel;
            c.vy -= yVel;
            c.slope = c.vy / c.vx;
            c.intercept = c.py - (c.slope * c.px);
            pair<long long, long long> xyInt = findIntersection(a, b); // Get collision point
            pair<long long, long long> xyInt2 = findIntersection(a, c);
            if (xyInt.first == -1 && xyInt.second == -1) { //Lines are parallel
                if (xyInt2.first == -1 && xyInt2.second == -1) {
                    cout << "All lines parallel? Skipping" << endl;
                    continue;
                }
                //We know the intersection should be valid from a,c
                xyInt = xyInt2;
            }
            if (((xyInt.first - a.px) / a.vx) < 0 || ((xyInt.first - b.px) / b.vx) < 0)
                continue; //Impossible, rocks collide at negative time
            if (((xyInt2.first - c.px) / c.vx) < 0 || xyInt.first != xyInt2.first || xyInt.second != xyInt2.second)
                continue; //Rock collides at negative time or we don't line up correctly
            //We have a solution that works for x and y. Check if there's a z that works
            for (zVel = minVel; zVel < maxVel; zVel++) {
                double collisionTimeA = (xyInt.first - a.px) / a.vx, collisionTimeB = ((xyInt.first - b.px) / b.vx), collisionTimeC = ((xyInt.first - c.px) / c.vx);
                if ((collisionTimeA*(a.vz - zVel) + a.pz) == (collisionTimeB*(b.vz - zVel) + b.pz) && (collisionTimeA*(a.vz - zVel) + a.pz) == (collisionTimeC*(c.vz - zVel) + c.pz)) {
                    //We have an answer
                    cout << "Velocity: " << xVel << ' ' << yVel << ' ' << zVel << endl;
                    a = stones[0];
                    long long xPos = (a.px + (collisionTimeA * a.vx)) - (collisionTimeA * xVel), yPos = (a.py + (collisionTimeA * a.vy)) - (collisionTimeA * yVel), zPos = (a.pz + (collisionTimeA * a.vz)) - (collisionTimeA * zVel);
                    cout << "Position: " << xPos << ' ' << yPos << ' ' << zPos << endl;
                    cout << (long long)(xPos + yPos + zPos) << endl;
                    return 0;
                }
            }
        }
    }

    cout << answer << endl;
    return 0;
}