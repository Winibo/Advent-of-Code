// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>

using namespace std;

int main() {
    long long sum = 0;
    string line;
    bool done = false;
    while (getline(cin, line)) {
        cout << "Reading line:" << line << endl;
        if (line.length() == 0 && !done) {
            done = true;
            continue;
        } else if (line.length() == 0 && done) break;
        else done = false;
        long long linesum = 0;
        long long mult = 1;
        for (int i = line.length() - 1; i > -1; i--) {
            long long val;
            if (line[i] == '-') val = -1;
            else if (line[i] == '=') val = -2;
            else val = line[i] - '0';
            val *= mult;
            mult *= 5;
            linesum += val;
        }
        cout << "Linesum:" << linesum << endl;
        sum += linesum;
        cout << "Sum:" << sum << endl;
    }
    cout << sum << endl;
    string result = "";
    //Convert to regular base 5
    while (sum > 0) { //Guaranteed answer is > 0
        result = result + to_string((sum % 5));
        sum = sum / 5;
    }
    result = result + '0';
    cout << result << endl;
    reverse(result.begin(), result.end());
    cout << result << endl;
    reverse(result.begin(), result.end());
    //Convert from base 5 to balanced base 5
    for (int i = 0; i < result.length(); i++) {
        if (result[i] == '3') { //Increment next, change to =
            result[i+1] = result[i+1] + 1;
            result[i] = '=';
        } else if (result[i] == '4') { //Increment next, change to -
            result[i+1] = result[i+1] + 1;
            result[i] = '-';
        }
        if (result[i] == '5') {
            result[i] = '0';
            result[i+1] = result[i+1] + 1;
        }
    }
    //We've been reading backwards
    reverse(result.begin(), result.end());
    cout << result << endl;
    return 0;
}
