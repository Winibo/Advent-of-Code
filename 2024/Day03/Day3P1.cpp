#include <bits/stdc++.h>

using namespace std;


int main()
{
    regex r("mul\\((\\d+),(\\d+)\\)");
    string input;
    smatch match;
    long long result;
    while (!cin.eof()) {
        getline(cin, input);
        while (regex_search(input, match, r)) {
            long long a = stoi(match.str(1)), b = stoi(match.str(2));
            result = result + (a * b);
            input = match.suffix().str();
        }
    }

    cout << result << endl;

    return 0;
}