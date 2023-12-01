//This code is just, the worst. I should've stopped and approached this better, but NO I said, I will continue to fail for all eternity.
//And then I spent like, 40 minutes debugging this...

#include "bits/stdc++.h"

using namespace std;

string testNumbers[] = {"./.", "one","two","three", "four","five","six","seven","eight","nine"};

int main()
{
    int answer = 0;
    while (!cin.eof()) {
        string nextLine;
        getline(cin, nextLine);
        bool foundFirst = false;
        int last = -1;
        int lastIndex = 0;
        int tempAnswer = 0;
        string temp;
        for (int i = 0; i < nextLine.length(); i++) {
            char x = nextLine[i];
            if (isdigit(x)) {
                if (!foundFirst) {
                    foundFirst = true;
                    int previousString = -1;
                    int prevStringLoc = -1;
                    for (int j = 0; j < 10; j++) {
                        string textNumber = testNumbers[j];
                        int location = nextLine.substr(0,i).find(textNumber);
                        if (location != -1) {
                            if (prevStringLoc == -1 || location < prevStringLoc) {
                                prevStringLoc = location;
                                previousString = j;
                            }
                        }
                    }
                    if (previousString != -1) {
                        tempAnswer = previousString * 10;
                    } else {
                        tempAnswer = (x - '0') * 10;
                    }
                }
                last = x - '0';
                lastIndex = i;
            }
        }
        if (!foundFirst) {
            int previousString = -1;
            int prevStringLoc = -1;
            for (int j = 0; j < 10; j++) {
                string textNumber = testNumbers[j];
                int location = nextLine.find(textNumber);
                if (location != -1) {
                    if (prevStringLoc == -1 || location < prevStringLoc) {
                        prevStringLoc = location;
                        previousString = j;
                    }
                }
            }
            if (previousString != -1) {
                tempAnswer = previousString * 10;
            }
        }
        int previousString = -1;
        int prevStringLoc = -1;
        for (int j = 0; j < 10; j++) {
            string testLine = nextLine;
            int prevRemoved = 0;
            string textNumber = testNumbers[j];
            int location = testLine.substr(lastIndex != -1 ? lastIndex : 0).find(textNumber);
            testLine = testLine.substr(lastIndex != -1 ? lastIndex : 0);
            while (location != -1) {
                if (prevStringLoc == -1 || location + (nextLine.length() - testLine.length()) > prevStringLoc) {
                    prevStringLoc = location + (nextLine.length() - testLine.length());
                    previousString = j;
                }
                int tempLocation = location;
                location = testLine.substr(location + testNumbers[j].length()).find(textNumber);
                testLine = testLine.substr(tempLocation + testNumbers[j].length());
            }
        }
        if (previousString == -1 && last == -1) {
            answer += tempAnswer + tempAnswer / 10;
            // cout << tempAnswer + tempAnswer / 10 << endl;
        } else if (previousString != -1 && prevStringLoc > lastIndex) {
            answer += tempAnswer + previousString;
            // cout << tempAnswer + previousString << endl;
        } else {
            answer += tempAnswer + last;
            // cout << tempAnswer + last << endl;
        }
    }
    cout << answer;
    return 0;
}
