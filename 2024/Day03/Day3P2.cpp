#include <bits/stdc++.h>

using namespace std;


long long findMatches(string input) {
    long long result = 0;
    regex mult("mul\\((\\d+),(\\d+)\\)|do\\(\\)|don't\\(\\)");
    regex enable("do()");
    regex disable("don't()");
    bool enabled = true;
    smatch match;
    while (regex_search(input, match, mult)) {
        if (match.str(0) == "don't()") {
            enabled = false;
            cout << "Disabled" << endl;
            
        } else if (match.str(0) == "do()") {
            enabled = true;
            cout << "Enabled" << endl;
        } else if (enabled) {
            long long a = stoi(match.str(1)), b = stoi(match.str(2));
            result = result + (a * b);
            cout << result << endl;
            cout << match.str(0) << endl;
        }
        input = match.suffix().str();
    }
    return result;
}

int main()
{
    string input, fullString = "";
    long long result = 0;
    while (!cin.eof()) {
        getline(cin, input);
        fullString = fullString + input;
    }
    result += findMatches(fullString);
    cout << result << endl;

    return 0;
}