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
    long long time = 0, distance = 0;
    while (!timesStream.eof()) {
        int temp, temp2;
        timesStream >> temp;
        temp2 = temp;
        while (temp2 > 0) {
            time *= 10;
            temp2 = temp2 / 10;
        }
        time += temp;
        distanceStream >> temp;
        temp2 = temp;
        while (temp2 > 0) {
            distance *= 10;
            temp2 = temp2 / 10;
        }
        distance += temp;
    }
    long long ways = 0;
        for (int i = 0; i < time; i++) {
            int speed = i;
            if (speed * (time - i) > distance)
                ways++;
        }
        answer *= ways;
    cout << "Distance: " << distance << endl;
    cout << "Time: " << time << endl;
    cout << answer << endl;
    return 0;
}