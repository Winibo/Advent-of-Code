#include "bits/stdc++.h"

using namespace std;

int main()
{
    int depth = 0;
    int distance = 0;
    int aim = 0;
    while (!cin.eof()) {
        string direction = "";
        int speed = 0;
        cin >> direction >> speed;
        if (direction == "" || speed == 0)
            break;
        if (direction == "forward") {
            distance += speed;
            depth += speed * aim;
        } else if (direction == "down") {
            aim += speed;
        }  else { //Up
            aim -= speed;
        }
    }
    cout << depth*distance << endl;
    return 0;
}
