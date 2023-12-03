#include "bits/stdc++.h"

using namespace std;

map<int, pair<int, int>> bits;
vector<string> bitStrings;
int main()
{
    while (!cin.eof()) {
        string nextbitString;
        cin >> nextbitString;
        if (nextbitString == "")
            break;
        bitStrings.push_back(nextbitString);
        for (int x = 0; x < nextbitString.length(); x++) {
            if (!bits.contains(x)) {
                bits[x] = make_pair(0,0);
            }
            pair<int, int> count = (nextbitString[x] == '1') ? make_pair(bits[x].first + 1,bits[x].second) : make_pair(bits[x].first, bits[x].second + 1);
            bits[x] = count;
        }
    }
    int gamma = 0, epsilon = 0;
    string gammaString = "", epsilonString = "";
    for (auto x : bits) {
        gamma = (gamma << 1) + (x.second.first >= x.second.second);
        cout << x.second.first << ' ' << x.second.second << endl;
        epsilon = (epsilon << 1) + !(x.second.first >= x.second.second);
    }
    cout << "Gamma: " << gamma << endl;
    cout << "Epsilon: " << epsilon << endl;
    cout << gamma*epsilon << endl;
    cout << "Part 2:" << endl;
    cout << "Gamma: " << gammaString << endl;
    cout << "Epsilon: " << epsilonString << endl;
    vector<string> gammaMatches = bitStrings;
    vector<string> epsilonMatches = bitStrings;
    int currentBit = 0;
    while (gammaMatches.size() > 1) {
        //Find most popular
        vector<string> tempMatches;
        pair<int, int> counts; //1,0
        for (string x : gammaMatches) {
            if (x[currentBit] == '1') {
                counts.first++;
            } else {
                counts.second++;
            }
        }
        int bit = (counts.first >= counts.second);
        for (string x: gammaMatches) {
            if (x[currentBit] - '0' == bit) {
                tempMatches.push_back(x);
            }
        }
        gammaMatches = tempMatches;
        currentBit++;
    }
    currentBit = 0;
        while (epsilonMatches.size() > 1) {
        //Find most popular
        vector<string> tempMatches;
        pair<int, int> counts; //1,0
        for (string x : epsilonMatches) {
            if (x[currentBit] == '1') {
                counts.first++;
            } else {
                counts.second++;
            }
        }
        int bit = !(counts.first >= counts.second);
        for (string x: epsilonMatches) {
            if (x[currentBit] - '0' == bit) {
                tempMatches.push_back(x);
            }
        }
        epsilonMatches = tempMatches;
        currentBit++;
    }
    
    //Convert to decimal
    gamma = 0;
    epsilon = 0;
    for (char x : gammaMatches[0]) {
        gamma = (gamma << 1) + (x - '0');
    }
    for (char x : epsilonMatches[0]) {
        epsilon = (epsilon << 1) + (x - '0');
    }
    cout << gammaMatches[0] << endl;
    cout << epsilonMatches[0] << endl;
    cout << gamma*epsilon << endl;
    return 0;
}
