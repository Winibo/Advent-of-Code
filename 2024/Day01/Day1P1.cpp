#include <bits/stdc++.h>

using namespace std;

int main()
{
    vector<int> left, right;
    int a, b;
    cin >> a >> b;
    while (!cin.eof()) {
        left.push_back(a);
        right.push_back(b);
        a = 0;
        b = 0;
        cin >> a >> b;
    }
    left.push_back(a);
    right.push_back(b);
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    long long difference = 0;
    for (int i = 0; i < left.size(); i++) {
        difference += abs(left[i] - right[i]);
    }
    cout << difference << endl;
    return 0;
}