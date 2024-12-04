#include <bits/stdc++.h>

using namespace std;

vector<string> wordSearch;

int findMatches(vector<string> words) {
    regex xmas("A");
    smatch match;
    long long count = 0;
    for (int i = 1; i < words.size() - 1; i++) {
        string input = words[i];
        // Forward
        int offset = 0;
        while (regex_search(input, match, xmas)) {
            int position = match.position() + offset;
            // Check Not at edge
            if (position != 0 && position != words[0].length() - 1) {
                // Check Down Right matches
                if ((words[i-1][position-1] == 'M' && words[i+1][position+1] == 'S') || (words[i-1][position-1] == 'S' && words[i+1][position+1] == 'M')) {
                    // Check Down Left matches
                    if ((words[i-1][position+1] == 'M' && words[i+1][position-1] == 'S') || (words[i-1][position+1] == 'S' && words[i+1][position-1] == 'M')) {
                        count++;
                    }
                }
            }
            offset += match.position() + 1;
            input = match.suffix().str();
        }
    }
    return count;
}

void printSearch(vector<string> list) {
    for (string x : list) {
        cout << x << endl;
    }
}

int main()
{
    string line;
    long long answer = 0;
    while (!cin.eof()) {
        getline(cin, line);
        wordSearch.push_back(line);
    }
    answer += findMatches(wordSearch);
    cout << answer << endl;
    return 0;
}