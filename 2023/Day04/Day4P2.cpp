#include "bits/stdc++.h"

using namespace std;

vector<int> cardScores;
vector<int> totalCards;

int main()
{
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
                        cardScore++;
                }
            }
        }
        cardScores.push_back(cardScore);
        totalCards.push_back(1);
    }
    
    for (int x = 0; x < cardScores.size(); x++) {
        int cardCount = totalCards[x];
        int matches = cardScores[x];
        for (int y = 0; y < matches; y++) {
            totalCards[x+y+1] += cardCount;
        }
    }
    long long answer;
    for (long long x : totalCards) {
        answer += x;
    }
    
    cout << answer << endl;
    return 0;
}
