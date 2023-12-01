//Minor improvement Note:
//I should've just always stored x in last, then I wouldn't have needed that last != -1 check at the end there
//Since if the first and the last were the same, we would've already known.

#include "bits/stdc++.h"

using namespace std;

int main()
{
    int answer = 0;
    while (!cin.eof()) {
        string nextLine;
        getline(cin, nextLine);
        bool foundFirst = false;
        int last = -1;
        int tempAnswer = 0;
        for (char x : nextLine) {
            if (isdigit(x)) {
                if (!foundFirst) {
                    foundFirst = true;
                    tempAnswer = (x - '0') * 10;
                } else {
                    last = x - '0';
                }
            }
        }
        if (last != -1) {
            answer += (tempAnswer + last);
        } else {
            answer += (tempAnswer + (tempAnswer / 10));
        }
    }
    cout << answer;
    return 0;
}
