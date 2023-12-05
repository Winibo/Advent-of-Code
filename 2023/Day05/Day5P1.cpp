#include "bits/stdc++.h"

using namespace std;

//Seed -> soil
//Soil -> Fert
//Fert -> water
//Water -> Light
//Light -> temp
//Temp -> Humidity
//Humidity -> Location

int main()
{
    vector<pair<long long, bool>> data;
    string temp, newline;
    getline(cin, newline);
    stringstream seedstream(newline);
    seedstream >> temp;
    cout << "Reading Seeds" << endl;
    while (!seedstream.eof()) {
        long long seed;
        seedstream >> seed;
        data.push_back(make_pair(seed, false));
    }
    getline(cin, temp); //Blank line
    getline(cin, temp); //Map label 1
    cout << "Reading Maps" << endl;
    while (!cin.eof()) {
        string testString;
        getline(cin, testString);
        // cout << "Next line: " << testString << endl;
        if (isdigit(testString[0])) {
            stringstream value(testString);
            long long destination, source, length;
            value >> destination >> source >> length;
            for (int i = 0; i < data.size(); i++) {
                auto current = data[i];
                if (!current.second && current.first >= source && current.first <= source + length) {
                    //Update data
                    data[i].second = true;
                    // cout << "Value " << i << " Was: " << data[i].first;
                    data[i].first = destination + (current.first - source);
                    // cout << " is now: " << data[i].first << endl;
                }
            }
        } else {
            // cout << "Finished Reading map" << endl;
            //Reset all data
            for (int i = 0; i < data.size(); i++) {
                data[i].second = false;
            }
        }
    }
    // for (auto x : data) {
    //     cout << x.first << endl;
    // }
    long long smallest = INT_MAX;
    for (auto x : data) {
        smallest = min(x.first, smallest);
    }
    cout << smallest << endl;
    return 0;
}