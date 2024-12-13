#include <bits/stdc++.h>

using namespace std;

long long calculate(pair<long long, long long> a, pair<long long, long long> b, pair<long long, long long> target) {
    // I don't know linear algebra, so I stole this from Reddit user SuperSmurfen
    // I went back and did the math for this by hand after the fact! See Working Out.txt
    long long bp = (target.second * a.first - target.first * a.second) / (b.second * a.first - b.first * a.second);
    long long ap = (target.first - bp * b.first) / a.first;
    if (a.first * ap + b.first * bp != target.first || a.second * ap + b.second * bp != target.second) {
        return 0;
    }
    return ap * 3 + bp;
}

int main()
{
    long long answer = 0;
    while (!cin.eof()) {
        string temp; char tempc;
        pair<long long, long long> a, b, target;
        cin >> temp >> temp >> tempc >> tempc >> a.first >> tempc >> tempc >> tempc >> a.second;
        cin >> temp >> temp >> tempc >> tempc >> b.first >> tempc >> tempc >> tempc >> b.second;
        cin >> temp >> tempc >> tempc >> target.first >> tempc >> tempc >> tempc >> target.second;
        target.first += 10000000000000;
        target.second += 10000000000000;
        long long result = calculate(a, b, target);
        answer += result;
    }
    cout << answer << endl;
    return 0;
}
