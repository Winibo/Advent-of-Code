#include <bits/stdc++.h>

using namespace std;

// Keypad: ".0A123456789"
// Direct: "<v>.^A"

vector<string> getPossibilities(char a, char b, string keypad) {
    struct node {
      pair<int, int> position;
      string path = "";
    };
    node start;
    start.position = make_pair(keypad.find(a) / 3, keypad.find(a) % 3);
    queue<node> search;
    search.push(start);
    vector<string> results;
    pair<int, int> end = make_pair(keypad.find(b) / 3, keypad.find(b) % 3);
    while (!search.empty()) {
        node current = search.front(); search.pop();
        // Check valid position
        // Yeah yeah this could be done better, I don't really care
        if (keypad[current.position.first * 3 + current.position.second] == '.') continue;
        if (current.position == end) {
            results.push_back(current.path + 'A');
            continue;
        }
        if (current.position.first > end.first) {
            node next = current; next.position.first -= 1;
            next.path += 'v';
            search.push(next);
        }
        if (current.position.first < end.first) {
            node next = current; next.position.first += 1;
            next.path += '^';
            search.push(next);
        }
        if (current.position.second > end.second) {
            node next = current; next.position.second -= 1;
            next.path += '<';
            search.push(next);
        }
        if (current.position.second < end.second) {
            node next = current; next.position.second += 1;
            next.path += '>';
            search.push(next);
        }
    }
    return results;
}

map<tuple<char, char, int>, int> lookup; // start, end, level

int getPath(string path, int level, string keypad = "<v>.^A") {
    if (level == 0) return path.length();
    char current = 'A';
    int result = 0;
    for (char x : path) {
        if (lookup.count(make_tuple(current,x,level)) != 0) {
            result += lookup[make_tuple(current,x,level)];
            current = x;
            continue;
        }
        vector<string> possibilities = getPossibilities(current, x, keypad);
        int length = INT_MAX;
        for (string option : possibilities) {
            length = min(length, getPath(option, level - 1));
        }
        lookup[make_tuple(current,x,level)] = length;
        result += length;
        current = x;
    }
    return result;
}

int main()
{
    long long result = 0;
    while (!cin.eof()) {
        string code;
        cin >> code;
        int length = getPath(code, 3, ".0A123456789");
        result += stoi(code.substr(0,code.length() - 1)) * length;
    }
    // cout << getPath("029A", 3, ".0A123456789") << endl;
    cout << result << endl;
    return 0;
}
