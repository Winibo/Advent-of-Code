#include "bits/stdc++.h"

using namespace std;

string cardRanks = "23456789TJQKA";

int getScore(string hand) {
    int longestMatch = 0, uniqueValues = 0, currentMatch = 0;
    for (int i = 0; i < hand.length(); i++) {
        if (i == 0 || hand[i] != hand[i-1]) {
            uniqueValues++;
            longestMatch = max(longestMatch, currentMatch);
            currentMatch = 1;
        }
        if (i == 0 || hand[i] == hand[i-1]) {
            if (i != 0)
                currentMatch++;
            longestMatch = max(longestMatch, currentMatch);
        }
    }
    if (longestMatch > 2) {
        if (uniqueValues <= 2) {
            return longestMatch + 1; //6,5,4 
        } else {
            return 3; //3
        }
    } else if (uniqueValues == 3) {
        return 2;
    } else if (uniqueValues == 4) {
        return 1;
    }
    return 0;
}

bool sortHands(pair<string, int> a, pair<string, int> b) {
    string sortedA = a.first, sortedB = b.first;
    sort(sortedA.begin(), sortedA.end());
    sort(sortedB.begin(), sortedB.end());
    int aScore = getScore(sortedA);
    int bScore = getScore(sortedB);
    if (aScore > bScore) {
        return true;
    } else if (aScore < bScore) {
        return false;
    } else {
        //Break with first card
        for (int i = 0; i < sortedA.length(); i++) {
            int aPow = cardRanks.find(a.first[i]);
            int bPow = cardRanks.find(b.first[i]);
            if (aPow > bPow) {
                return true;
            } else if (aPow < bPow){
                return false;
            }
        }
    }
    return true; //Unreachable
}

int main() {
    vector<pair<string, int>> hands;
    long long score = 0;
    while (!cin.eof()) {
        string hand;
        int wager = -1;
        cin >> hand >> wager;
        if (wager == -1)
            break;
        hands.push_back(make_pair(hand, wager));
    }
    sort(hands.rbegin(), hands.rend(), sortHands);
    for (int i = 0; i < hands.size(); i++) {
        score += hands[i].second * (i+1);
    }
    cout << score << endl;
    return 0;
}