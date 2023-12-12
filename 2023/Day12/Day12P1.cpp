#include "bits/stdc++.h"

using namespace std;

bool validate(string line, vector<int> required) {
    replace(line.begin(), line.end(), '?', '.');
    line = line + '.';
    int currentLength = 0, currentIndex = 0;
    for (char x : line) {
        if (x == '#') {
            currentLength++;
        } else {
            if (currentLength > 0) {
                if ((currentIndex >= required.size() || currentLength != required[currentIndex])) {
                    return false;
                }
                currentLength = 0;
                currentIndex++;
            }
        }
    }
    if (currentIndex == required.size()) {
        return true;
    }
    return false;
}

int solve(string line, vector<int> remaining, int sStart, int vStart) {
    if (remaining.size() == vStart) {
        return validate(line, remaining) ? 1 : 0;
    }
    int answers = 0;
    for (int i = sStart; i < line.length() - remaining[vStart] + 1; i++) {
        bool valid = true;
        for (int j = i; j < remaining[vStart] + i; j++) {
            if (line[j] == '.') {
                valid = false;
                break;
            }
        }
        if (valid) {
            string newLine = line.substr(0, i) + string(remaining[vStart], '#') + line.substr(i + remaining[vStart], string::npos);
            answers += solve(newLine, remaining, i + remaining[vStart], vStart + 1);
        }
    }
    return answers;
}


int main() {
    int result = 0;
    while (!cin.eof()) {
        string input, line = "";
        vector<int> required;
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
        int temp = solve(input, required, 0, 0);
        result += temp;
    }
    cout << "Result: " << result << endl;
    return 0;
}