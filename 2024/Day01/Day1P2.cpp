#include <bits/stdc++.h>

using namespace std;

int main()
{
    map<int, int> rightList;
    vector<int> leftList;
    int a, b;
    cin >> a >> b;
    while (!cin.eof()) {
        rightList[b] += 1;
        leftList.push_back(a);
        cin >> a >> b;
    }
    rightList[b] += 1;
    leftList.push_back(a);
    long long answer = 0;
    for (int x : leftList) {
        answer += rightList[x] * x;
    }
    cout << answer << endl;
    return 0;
}