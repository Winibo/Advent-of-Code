#include <bits/stdc++.h>

using namespace std;

int main()
{
    int safeLines = 0;
    string inputLine;
    do {
        getline(cin, inputLine);
        istringstream line(inputLine);
        int previous = 0, a = 0;
        line >> a >> previous;
        bool increasing = a < previous;
        bool safe = true;
        if (abs(a - previous) > 3 || abs(a - previous) < 1) {
            safe = false;
        }
        while (!line.eof()) {
            if (safe == false) {
                break;
            }
            int current;
            line >> current;
            if ((increasing && previous > current) || (!increasing && previous < current)) {
                safe = false;
                break;
            }
            if (abs(current - previous) > 3 || abs(current - previous) < 1) {
                safe = false;
                break;
            }
            previous = current;
        }
        if (safe) {
            safeLines++;
        }
    } while (!cin.eof());
    cout << safeLines << endl;
    
    return 0;
}