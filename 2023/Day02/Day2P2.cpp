#include "bits/stdc++.h"

using namespace std;

int main()
{
    long long answer = 0;
    while (!cin.eof()) {
        string nextLine;
        getline(cin, nextLine);
        stringstream s(nextLine);
        string temp;
        int id = 0;
        s >> temp >> id >> temp;
        bool possible = true;
        long long red = 1, blue = 1, green = 1;
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
                        if (amount > red || red == -1) {
                            red = amount;
                        }
                    }
                    if (tcolour == "blue") {
                        if (amount > blue || blue == -1) {
                            blue = amount;
                        }
                    }
                    if (tcolour == "green") {
                        if (amount > green || green == -1) {
                            green = amount;
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
        // cout << "Game: " << id << endl;
        // cout << "Min red: " << red << " Min Blue: " << blue << " Min Green: " << green << endl;
        long long additional = red*blue*green;
        // cout << "Additional " << additional << endl;
        answer += additional;
        // cout << "New Answer " << answer << endl;
    }
    cout << answer << endl;
    return 0;
}