#include <bits/stdc++.h>

using namespace std;

bool evaluate(bool increasing, vector<int> line, int skip) {
    int previous = skip != 0 ? line[0] : line[1];
    for (int i = skip != 0 ? 1 : 2; i < line.size(); i++) {
        int current = line[i];
        if (skip == i) {
            continue;
        }
        if ((increasing && previous > current) || (!increasing && previous < current)) {
            return false;
        }
        if (abs(current - previous) > 3 || abs(current - previous) < 1) {
            return false;
        }
        previous = current;
    }
    return true;
}

bool checkLine(string inputLine) {
    vector<int> line;
    istringstream cline(inputLine);
    while (!cline.eof()) {
        int a;
        cline >> a;
        line.push_back(a);
    }
    bool valid = false;
    for (int i = 0; i < line.size(); i++) {
        valid = evaluate(true, line, i);
        valid = valid || evaluate(false, line, i);
        if (valid) return valid;
    }
    return false;
}


int main()
{
    int safeLines = 0;
    string inputLine;
    do {
        getline(cin, inputLine);
        if (checkLine(inputLine)) {
            safeLines++;
        }
    } while (!cin.eof());
    cout << safeLines << endl;
    
    return 0;
}