#include "bits/stdc++.h"

using namespace std;

struct satellite {
    int orbitCount;
    vector<string> children;
    string parent = "";
};

map<string, satellite> orbits;

int count_orbits(string orbit) {
    int totalOrbits = orbits[orbit].orbitCount;
    vector<string> children = orbits[orbit].children;
    for (string child : children) {
        orbits[child].orbitCount = orbits[orbit].orbitCount + 1;
        totalOrbits += count_orbits(child);
    }
    return totalOrbits;
}

int transfer_count(string start,  string previous) {
    satellite data = orbits[start];
    if (find(data.children.begin(), data.children.end(), "SAN") != data.children.end()) {
        return 0;
    }

    for (string x : data.children) {
        if (x == previous) {
            continue;
        }
        int result = transfer_count(x, start);
        if (result != -1) { //We found the route
            return result + 1;
        }
    }
    if (previous != data.parent) {
        int result = transfer_count(data.parent, start);
        if (result != -1)
            return result + 1;
    }
    return -1;
}

int main() {
    while (!cin.eof()) {
        string line, inner, outer;
        getline(cin, line);
        stringstream lstream(line);
        getline(lstream, inner, ')');
        getline(lstream, outer);
        orbits[inner].children.push_back(outer);
        orbits[outer].parent = inner;
    }
    cout << transfer_count(orbits["YOU"].parent, "YOU") << endl;
}