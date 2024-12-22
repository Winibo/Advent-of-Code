#include <bits/stdc++.h>

using namespace std;

long long getNextNumber(long long number, int step) {
    number = ((number * 64) ^ number) % 16777216;
    number = ((number / 32) ^ number) % 16777216;
    number = ((number * 2048)^ number) % 16777216;
    return number;
}

int main()
{
    int step = 1;
    long long value = 0;
    long long result = 0;
    while (!cin.eof()) {
        cin >> value;
        for (int i = 0; i < 2000; i++) {
            value  = getNextNumber(value, step);
        }
        result += value;
    }
    cout << result << endl;
    return 0;
}