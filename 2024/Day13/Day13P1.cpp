#include <bits/stdc++.h>

using namespace std;

map<pair<long long, long long>, long long> memo; // Location -> cost

long long coin_counting(pair<long long, long long>& a, pair<long long, long long>& b, pair<long long, long long>& target) {
    if (memo.count(target) != 0) {
        return memo[target];
    }
    if (target == b) {
        memo[target] = 1;
        return 1;
    }
    if (target == a) {
        memo[target] = 3;
        return 3;
    }
    if ((target.first < a.first || target.second < a.second) && (target.first < b.first || target.second < b.second)) {
        return LLONG_MAX - 20; // Incapable of right answer
    }
    auto newTarget = make_pair(target.first - a.first, target.second - a.second);
    long long result = 0;
    long long costA = 3 + coin_counting(a, b, newTarget);
    newTarget = make_pair(target.first - b.first, target.second - b.second);
    long long costB = 1 + coin_counting(a, b, newTarget);
    if (costA < 0) costA = LLONG_MAX - 20;
    if (costB < 0) costB = LLONG_MAX - 20;
    memo[target] = min(costA, costB);
    return min(costA, costB);
}

int main()
{
    long long answer = 0;
    while (!cin.eof()) {
        memo.clear();
        string temp; char tempc;
        pair<long long, long long> a, b, target;
        cin >> temp >> temp >> tempc >> tempc >> a.first >> tempc >> tempc >> tempc >> a.second;
        cin >> temp >> temp >> tempc >> tempc >> b.first >> tempc >> tempc >> tempc >> b.second;
        cin >> temp >> tempc >> tempc >> target.first >> tempc >> tempc >> tempc >> target.second;
        long long result = coin_counting(a, b, target);
        cout << "Result: " << result << endl;
        if (result < LLONG_MAX - 20) {
            answer += result;  
        }
    }
    cout << answer << endl;
    return 0;
}