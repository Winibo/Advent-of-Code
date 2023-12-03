#include "bits/stdc++.h"

using namespace std;

map<int, pair<int, int>> bits;

int main()
{
    while (!cin.eof()) {
        string nextbitString;
        cin >> nextbitString;
        if (nextbitString == "")
            break;
        for (int x = 0; x < nextbitString.length(); x++) {
            if (!bits.contains(x)) {
                bits[x] = make_pair(0,0);
            }
            pair<int, int> count = (nextbitString[x] == '1') ? make_pair(bits[x].first + 1,bits[x].second) : make_pair(bits[x].first, bits[x].second + 1);
            bits[x] = count;
        }
    }
    int gamma = 0, epsilon = 0;
    for (auto x : bits) {
        gamma = (gamma << 1) + (x.second.first > x.second.second);
        epsilon = (epsilon << 1) + !(x.second.first > x.second.second);
    }
    cout << "Gamma: " << gamma << endl;
    cout << "Espilon: " << epsilon << endl;
    cout << gamma*epsilon << endl;
    return 0;
}
