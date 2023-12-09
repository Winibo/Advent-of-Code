#include "bits/stdc++.h"

using namespace std;

long long getValues(vector<long long> start) {

    if (count(start.begin(), start.end(), 0) == start.size()) {
        return 0;
    }
    vector<long long> newData;
    for (int i = 1; i < start.size(); i++) {
        newData.push_back(start[i] - start[i-1]);
    }
    long long finalData = getValues(newData);

    return start[0] - finalData;
}


int main() {
    long long nextValueSum = 0;
    string newData;
    while (!cin.eof()) { //For every line
        getline(cin, newData);
        stringstream dataStream(newData);
        vector<long long> lineData;
        while (!dataStream.eof()) {
            int next = 0;
            dataStream >> next;
            lineData.push_back(next);
        }
        long long result = getValues(lineData);
        nextValueSum += result;
    }
    cout << nextValueSum << endl;
    return 0;
}
