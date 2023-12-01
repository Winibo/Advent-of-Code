#include "bits/stdc++.h"

using namespace std;

int main()
{
    int totalArea = 0;
    while (!cin.eof()) {
        char temp;
        int length = 0, width = 0, height = 0;
        cin >> length >> temp >> width >> temp >> height;
        int base = length * width, longWall = height * length, wideWall = width * height;
        int minimum = min(min(base, longWall), wideWall);
        totalArea += (2 * (base + longWall + wideWall)) + minimum;
    }
    cout << totalArea << endl;
}
