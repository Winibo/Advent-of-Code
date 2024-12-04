#include <bits/stdc++.h>

using namespace std;

vector<string> wordSearch;

vector<string> convertDiagonals() {
    vector<string> answer;
    // Down
    for (int i = 0; i < wordSearch.size(); i++) {
        string result = "";
        int j = 0, k = i;
        while (k < wordSearch.size()) {
            result = result + wordSearch[k][j];
            j++; k++;
        }
        answer.push_back(result);
    }
    // Across
    for (int i = 1; i < wordSearch[0].length(); i++) {
        string result = "";
        int j = 0, k = i;
        while (k < wordSearch[0].length()) {
            result = result + wordSearch[j][k];
            j++; k++;
        }
        answer.push_back(result);
    }
    return answer;
}

vector<string> convertVerticals() {
    vector<string> answer;
    for (int i = 0; i < wordSearch[0].length(); i++) {
        string result = "";
        for (int j = 0; j < wordSearch.size(); j++) {
            result = result + wordSearch[j][i];
        }
        answer.push_back(result);
    }
    return answer;
}

vector<string> flipSearch(vector<string> words) {
    vector<string> answer;
    for (string x : words) {
        string temp = x;
        reverse(temp.begin(), temp.end());
        answer.push_back(temp);
    }
    return answer;
}

int findMatches(vector<string> words) {
    regex xmas("XMAS");
    smatch match;
    long long count = 0;
    for (string x : words) {
        string input = x;
        // Forward
        while (regex_search(input, match, xmas)) {
            count++;
            input = match.suffix().str();
        }
        // Backward
        string copy = x;
        reverse(copy.begin(), copy.end());
        while (regex_search(copy, match, xmas)) {
            count++;
            copy = match.suffix().str();
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
    answer += findMatches(convertVerticals());
    answer += findMatches(convertDiagonals());
    wordSearch = flipSearch(wordSearch);
    answer += findMatches(convertDiagonals());
    cout << answer << endl;
    return 0;
}