#include <bits/stdc++.h>

using namespace std;



long long getNextNumber(long long number, int step) {
    number = ((number * 64) ^ number) % 16777216;
    number = ((number / 32) ^ number) % 16777216;
    number = ((number * 2048)^ number) % 16777216;
    return number;
}

map<vector<int>, int> lookup;

void calculateSequences(vector<int>& prices) {
    map<tuple<int, int, int, int>, int> seenProfits;
    tuple<int, int, int, int> differences;
    map<vector<int>, bool> seen;
    for (int i = 0; i + 4 < prices.size(); i++) {
        vector<int> data(5);
        data.push_back(prices[i] - prices[i+1]);
        data.push_back(prices[i+1] - prices[i+2]);
        data.push_back(prices[i+2] - prices[i+3]);
        data.push_back(prices[i+3] - prices[i+4]);
        if (!seen[data]) {
            lookup[data] += prices[i + 4];
            seen[data] = true;
        }
    }
}

int main()
{
    int step = 1;
    long long value = 0;
    long long result = 0;
    int count = 1;
    while (!cin.eof()) {
        count++;
        value = -1;
        cin >> value;
        if (value == -1) break;
        vector<int> prices;
        prices.push_back(value % 10);
        for (int i = 0; i < 2000; i++) {
            value = getNextNumber(value, step);
            prices.push_back(value % 10);
        }
        result += value;
        calculateSequences(prices);
    }
    long long best = 0; 
    for (auto x : lookup) {
        if (x.second > best) best = x.second;
    }
    cout << "Part 1" << endl;
    cout << result << endl;
    cout << "Part 2" << endl;
    cout << best << endl;
    return 0;
}
