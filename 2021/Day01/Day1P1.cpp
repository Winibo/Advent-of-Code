#include "bits/stdc++.h"

using namespace std;
int main()
{
    int count = 0, previous = -1;
    while (!cin.eof()) {
        int value;
        cin >> value;
        if (value > previous && previous != -1) {
            count++;
        }
        previous = value;
    }
    cout << count << endl;
    return 0;
}
