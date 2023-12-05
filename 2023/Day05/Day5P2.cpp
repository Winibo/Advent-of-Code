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
    vector<pair<pair<long long, long long>, bool>> data;
    string temp, newline;
    getline(cin, newline);
    stringstream seedstream(newline);
    seedstream >> temp;
    // cout << "Reading Seeds" << endl;
    while (!seedstream.eof()) {
        long long seed = -1, length = -1;
	seedstream >> seed >> length;
	if (seed == -1 || length == -1)
	    break;
	data.push_back(make_pair(make_pair(seed, length), false));
    }
    getline(cin, temp); //Blank line
    getline(cin, temp); //Map label 1
    // cout << "Reading Maps" << endl;
    while (!cin.eof()) {
	// cout << "Seed Ranges" << endl;
	for (auto x : data) {
	    cout << x.first.first << ' ' << x.first.second << endl;
	}
        string testString;
        getline(cin, testString);
        // cout << "Next line: " << testString << endl;
        if (isdigit(testString[0])) {
            stringstream value(testString);
            long long destination, source, length;
            value >> destination >> source >> length;
            // cout << "Data Length: " << data.size() << endl;
            for (int i = 0; i < data.size(); i++) {
                if (data[i].second || (data[i].first.first < source && data[i].first.first + data[i].first.second <= source) || (data[i].first.first >= source + length)) {
		            // cout << "Skipping Range: " << data[i].first.first << ' ' << data[i].first.second << ' ' << data[i].second << endl;
                    continue;
		        }
                //Entire length fits
                if (data[i].first.first >= source && data[i].first.first + data[i].first.second < source + length) {
                    //Update data
                    data[i].second = true;
                    data[i].first.first = destination + (data[i].first.first - source);
                //First 1/2 fits
                } else if (data[i].first.first >= source && data[i].first.first < source + length) {
                    data[i].second = true;
                    data.push_back(make_pair(make_pair(source + length, data[i].first.second - (source + length - data[i].first.first)), false));
                    data[i].first.second = ((source + length) - data[i].first.first);
                    data[i].first.first = destination + (data[i].first.first - source);
                //Second 1/2 fits
                } else if (data[i].first.first < source && data[i].first.first + data[i].first.second > source) {
                    data[i].second = true;
                    data.push_back(make_pair(make_pair(data[i].first.first, source - data[i].first.first), false));
                    data[i].first.second = data[i].first.second - (source - data[i].first.first);
                    data[i].first.first = source;
                    data[i].first.first = destination + (data[i].first.first - source);
                //Inner Range fits
                } else {
                    data[i].second = true;
                    data.push_back(make_pair(make_pair(data[i].first.first, source - data[i].first.second), false));
                    data.push_back(make_pair(make_pair(source + length, data[i].first.second - length - (source - data[i].first.first)), false));
                    data[i].first.first = source;
                    data[i].first.second = length;
                    data[i].first.first = destination + (data[i].first.first - source);
                }
            }
        } else {
            // cout << "Resetting data " << endl;
            //Reset all data
            for (int i = 0; i < data.size(); i++) {
                data[i].second = false;
            }
        }
    }
    long long smallest = INT_MAX;
    for (auto x : data) {
        smallest = min(x.first.first, smallest);
    }
    // cout << data.size() << endl;
    cout << smallest << endl;
    return 0;
}
