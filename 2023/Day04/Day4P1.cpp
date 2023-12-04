#include "bits/stdc++.h"

using namespace std;

int main()
{
    long long answer = 0;
    while (!cin.eof()) {
        string nextCard;
        getline(cin, nextCard);
        long long cardScore = 0;
        stringstream card(nextCard);
        while (!card.eof()) {
            string temp;
            card >> temp >> temp;
            // cout << "Reading card: " << temp << endl;
            string winning, ours;
            getline(card, winning, '|');
            getline(card, ours);
            vector<int> winningNumbers;
            // cout << "Winning Numbers: " << winning << endl;
            // cout << "Our Numbers: " << ours << endl;
            stringstream winningstream(winning);
            stringstream oursStream(ours);
            while (!winningstream.eof()) {
                int next;
                winningstream >> next;
                winningNumbers.push_back(next);
            }
            while (!oursStream.eof()) {
                int next;
                oursStream >> next;
                int match = count(winningNumbers.begin(), winningNumbers.end(), next);
                if (match > 0) {
                    if (cardScore == 0)
                        cardScore = 1;
                    else
                        cardScore *= 2;
                }
            }
        }
        answer += cardScore;
    }
    cout << answer << endl;
    return 0;
}
