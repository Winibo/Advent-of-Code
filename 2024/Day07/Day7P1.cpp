#include <bits/stdc++.h>

using namespace std;


long long evaluate(long long result, vector<long long>& values, int start = 0, long long partial = 0) {
    int ways = 0;
    if (start == values.size()) {
        return result == partial;
    }
    ways += evaluate(result, values, start + 1, partial + values[start]);
    if (partial == 0) partial = 1;
    ways += evaluate(result, values, start + 1, partial * values[start]);
    return ways;
}

int main()
{
    long long answer = 0;
    while (!cin.eof()) {
        string line;
        getline(cin, line);
        istringstream cline(line);
        long long result; char temp;
        cline >> result >> temp;
        vector<long long> values;
        while (!cline.eof()) {
            int temp;
            cline >> temp;
            values.push_back(temp);
        }
        int ways = evaluate(result, values);
        if (ways > 0) {
            answer += result;
        }
    }
    cout << answer << endl;
    return 0;
}