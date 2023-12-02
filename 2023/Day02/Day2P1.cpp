#include "bits/stdc++.h"

using namespace std;

int main()
{
    int answer = 0;
    while (!cin.eof()) {
        string nextLine;
        getline(cin, nextLine);
        stringstream s(nextLine);
        string temp;
        int id = 0;
        s >> temp >> id >> temp;
        bool possible = true;
        while (!s.eof()) {
            string input;
            getline(s, input, ';');
            // cout << "Current Game: " << id << endl;
            stringstream bag(input);
            while (!bag.eof()) {
                string t;
                getline(bag, t, ',');
                stringstream colour(t);
                while (!colour.eof()) {
                    int amount;
                    string tcolour;
                    colour >> amount >> tcolour;
                    if (tcolour == "red") {
                        if (amount > 12) {
                            possible = false;
                            break;
                        }
                    }
                    if (tcolour == "blue") {
                        if (amount > 14) {
                            possible = false;
                            break;
                        }
                    }
                    if (tcolour == "green") {
                        if (amount > 13) {
                            possible = false;
                            break;
                        }
                    }
                }
                if (!possible)
                    break;
            }
            if (!possible)
                break;
        }
        if (!possible)
            continue;
        // cout << "Game: " << id << " Possible" << endl;
        answer += id;
    }
    cout << answer << endl;
    return 0;
}