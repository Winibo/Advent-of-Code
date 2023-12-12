#include "bits/stdc++.h"

using namespace std;

long long lookup[200][200][200];
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
            long long answer = solve(line.substr(0, i) + '#' + line.substr(i+1, string::npos), i + 1, currentIndex, currentHashes + 1);
            answer += solve(line.substr(0, i) + '.' + line.substr(i+1, string::npos), i, currentIndex, currentHashes);
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

//Takes ~10 seconds?
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
        oRequired = required;
        for (int i = 0; i < 4; i++) {
            input = input + '?' + oInput;
            required.insert(required.end(), oRequired.begin(), oRequired.end());
        }
        for (int i = 0; i < 200; i++) {
            for (int j = 0; j < 200; j++) {
                for (int k = 0;k < 200; k++) {
                    lookup[i][j][k] = -1;
                }
            }
        }
        remaining = required;
        long long temp = solve(input + '.', 0, 0, 0);
        result += temp;
    }
    cout << "Result: " << result << endl;
    return 0;
}