#include "bits/stdc++.h"

using namespace std;

long long lookup[110][50][50];
vector<int> remaining;

long long solve(string line, int sStart, int vStart, int hashCount) {
    if (lookup[sStart][vStart][hashCount] != -1) {
        return lookup[sStart][vStart][hashCount];
    }
    int currentHashes = hashCount;
    int currentIndex = vStart;
    for (int i = sStart; i < line.length(); i++) {
        if (line[i] == '.') {
            //Validate
            if (currentHashes != 0 && (currentIndex >= remaining.size() || currentHashes != remaining[currentIndex])) { //Impossible
                lookup[sStart][vStart][hashCount] = 0;
                return 0;
            } else if (currentHashes != 0) { //Valid option
                currentIndex++;
                currentHashes = 0;
            }
        } else if (line[i] == '#') {
            //Work
            currentHashes++;
        } else {
            //Answer is sum of both options
            line[i] = '#';
            long long answer = solve(line, i + 1, currentIndex, currentHashes + 1);
            line[i] = '.';
            answer += solve(line, i, currentIndex, currentHashes);
            lookup[sStart][vStart][hashCount] = answer;
            return answer;
        }
    }

    if (currentIndex >= remaining.size()) {
        lookup[sStart][vStart][hashCount] = 1;
        return 1;
    }
    lookup[sStart][vStart][hashCount] = 0;
    return 0;
}

//Takes ~1 second (Maybe less)
int main() {
    long long result = 0;
    while (!cin.eof()) {
        string input, line = "", oInput;
        vector<int> required, oRequired;
        getline(cin, line);
        if (line == "")
            break;
        stringstream sline(line);
        sline >> input;
        while (!sline.eof()) {
            int next = -1;
            char temp;
            sline >> next >> temp;
            if (next == -1)
                break;
            required.push_back(next);
        }
        oInput = input;
        remaining.clear();
        for (int i = 0; i < 4; i++) {
            input = input + '?' + oInput;
        }
        for (int i = 0; i < 5; i++) {
            for (auto x : required) {
                remaining.push_back(x);
            }
        }
        for (int i = 0; i < input.length() + 1; i++) {
            for (int j = 0; j < remaining.size() + 1; j++) {
                for (int k = 0; k < 50; k++) {
                    lookup[i][j][k] = -1;
                }
            }
        }
        result += solve(input + '.', 0, 0, 0);
    }
    cout << "Result: " << result << endl;
    return 0;
}