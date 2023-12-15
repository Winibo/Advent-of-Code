#include "bits/stdc++.h"

using namespace std;

vector<pair<string, long long>> hashmap[256];

long long fHash(string in) {
    long long result = 0;
    for (char x : in) {
        result += x;
        result *= 17;
        result %= 256;
    }
    return result;
}

void addElement(int box, string label, int focus) {
    for (pair<string, long long> &x : hashmap[box]) {
        if (x.first == label) {
            x.second = focus;
            return;
        }
    }
    hashmap[box].push_back(make_pair(label, focus));
}

void removeElement(int box, string label) {
    for (int i = 0; i < hashmap[box].size(); i++) {
        auto x = hashmap[box][i];
        if (x.first == label) {
            hashmap[box].erase(hashmap[box].begin() + i);
            return;
        }
    }
}

void split(string in) {
    if (in.find('-') != string::npos) { //-
        string label = in.substr(0,in.find('-'));
        int box = fHash(label);
        removeElement(box, label);
    } else { //=
        string label = in.substr(0,in.find('='));
        int box = fHash(label);
        string focus = in.substr(in.find('=') + 1, string::npos);
        addElement(box, label, stoi(focus));
    }
}


int main() {
    while (!cin.eof()) {
        string next = "";
        getline(cin, next, ',');
        split(next);
    }
    long long answer = 0;
    for (long long i = 0; i < 256; i++) {
        for (long long j = 0; j < hashmap[i].size(); j++) {
            answer += ((i+1) * (j+1) * hashmap[i][j].second);
        }
    }
    cout << answer << endl;
    return 0;
}