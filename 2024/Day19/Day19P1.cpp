#include <bits/stdc++.h>

using namespace std;

vector<string> towels;

map<string, bool> lookup;

bool getPossible(string design) {
    if (lookup.count(design) != 0) {
        return lookup[design];
    }
    
    for (string towel : towels) {
        if (towel == design) {
            lookup[design] = true;
            return true;
        }
    }
    
    for (int i = 1; i < design.length(); i++) {
        string left = design.substr(0,i), right = design.substr(i);
        if (getPossible(left) && getPossible(right)) {
            lookup[design] = true;
            return true;
        }
    }
    lookup[design] = false;
    return false;
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
    int answer = 0;
    while (!cin.eof()) {
        string design;
        cin >> design;
        if (getPossible(design)) answer++;
        getPossible(design);
    }
    cout << answer << endl;
    return 0;
}