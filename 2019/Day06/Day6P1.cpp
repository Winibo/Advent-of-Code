#include "bits/stdc++.h"

using namespace std;

struct satellite {
    int orbitCount;
    vector<string> children;
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

int main() {
    while (!cin.eof()) {
        string line, inner, outer;
        getline(cin, line);
        stringstream lstream(line);
        getline(lstream, inner, ')');
        getline(lstream, outer);
        orbits[inner].children.push_back(outer);
    }
    cout << count_orbits("COM") << endl;
}