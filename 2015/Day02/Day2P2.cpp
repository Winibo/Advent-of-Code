#include "bits/stdc++.h"

using namespace std;

int main()
{
    int totalArea = 0;
    int ribbonArea = 0;
    while (!cin.eof()) {
        char temp;
        int length = 0, width = 0, height = 0;
        cin >> length >> temp >> width >> temp >> height;
        if (length > width) {
            int temp = length;
            length = width;
            width = temp;
        }
        if (width > height) {
            int temp = width;
            width = height;
            height = temp;
        }
        if (length > width) { //Have to check again if height was smallest
            int temp = length;
            length = width;
            width = temp;
        }
        int base = length * width, longWall = height * length, wideWall = width * height;
        int minimum = min(min(base, longWall), wideWall);
        totalArea += (2 * (base + longWall + wideWall)) + minimum;
        ribbonArea += length * width * height; //Bow
        ribbonArea += length * 2; //Smallest face
        ribbonArea += width * 2; //Second Smallest face
    }
    cout << totalArea << endl;
    cout << ribbonArea << endl;
}
