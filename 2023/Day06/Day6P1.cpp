#include "bits/stdc++.h"

using namespace std;

int main() {

    string times, distances;
    getline(cin, times);
    getline(cin, distances);
    stringstream timesStream(times);
    stringstream distanceStream(distances);
    timesStream >> times;
    distanceStream >> distances;
    long long answer = 1;
    while (!timesStream.eof()) {
        int time, distance;
        timesStream >> time;
        distanceStream >> distance;
        long long ways = 0;
        for (int i = 0; i < time; i++) {
            int speed = i;
            if (speed * (time - i) > distance)
                ways++;
        }
        answer *= ways;
    }
    cout << answer << endl;
    return 0;
}