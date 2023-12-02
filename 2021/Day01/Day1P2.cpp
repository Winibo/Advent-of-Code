#include "bits/stdc++.h"

using namespace std;

int window[3] = {-1,-1,-1};

int main()
{
    int count = 0;
    while (!cin.eof()) {
        int value = 0;
        cin >> value;
        //Work
        if (window[0] != -1) { //Check we have at data
            int previous = window[0] + window[1] + window[2];
            int current = window[1] + window[2] + value;
            if (previous < current) {
                count++;
            }
        }
        for (int i = 1; i < 3; i++) {
            window[i-1] = window[i];
        }
        window[2] = value;
    }
    cout << count << endl;
    return 0;
}
