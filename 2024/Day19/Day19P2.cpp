#include <bits/stdc++.h>

using namespace std;

vector<string> towels;

map<string, long long> lookup;

long long getPossible(string design) {
    if (lookup.count(design) != 0) {
        return lookup[design];
    }
    
    if (design == "") {
        return 1;
    }
    long long result = 0;
    for (string towel : towels) {
        if (design.substr(0, towel.length()) == towel) {
            result += getPossible(design.substr(towel.length()));
        }
    }

    lookup[design] = result;
    return result;
}

string trim(string x) {
    string value;
    for (char y : x) {
        if (y != ' ') value += y;
    }
    return value;
}

int main()
{
    string ts;
    getline(cin, ts);
    istringstream t(ts);
    while (!t.eof()) {
        string towel;
        getline(t, towel, ',');
        towel = trim(towel);
        towels.push_back(towel);
    }
    long long answer = 0;
    while (!cin.eof()) {
        string design;
        cin >> design;
        answer += getPossible(design);
    }
    cout << answer << endl;
    return 0;
}