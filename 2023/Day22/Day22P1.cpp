#include "bits/stdc++.h"

using namespace std;

struct brick {
    vector<int> startLocation; //x, y, z format
    vector<int> endLocation; //x, y, z format
    vector<int> supportedBy; //Indices of blocks that this block rests on
    vector<int> supports; //Indices of blocks that this block supports
};

vector<brick> sandPillars;

void dropBricks() {
    for (int i = 0; i < sandPillars.size(); i++) {
        
        int highestY = -1;
        vector<int> supportingBrickIndices;
        for (int j = 0; j < i; j++) {
            if (((sandPillars[j].startLocation[0] <= sandPillars[i].startLocation[0] && sandPillars[j].endLocation[0] >= sandPillars[i].startLocation[0]) || (sandPillars[j].startLocation[0] >= sandPillars[i].startLocation[0] && sandPillars[j].startLocation[0] <= sandPillars[i].endLocation[0])) && ((sandPillars[j].startLocation[1] <= sandPillars[i].startLocation[1] && sandPillars[j].endLocation[1] >= sandPillars[i].startLocation[1]) || (sandPillars[j].startLocation[1] >= sandPillars[i].startLocation[1] && sandPillars[j].startLocation[1] <= sandPillars[i].endLocation[1]))) { //If this brick could support our current brick
                if (sandPillars[j].endLocation[2] > highestY) {
                    supportingBrickIndices.clear();
                    supportingBrickIndices.push_back(j);
                    highestY = sandPillars[j].endLocation[2];
                } else if (sandPillars[j].endLocation[2] == highestY) {
                    supportingBrickIndices.push_back(j);
                }
            }
        }
        // cout << "Block: " << sandPillars[i].startLocation[0] << ' ' << sandPillars[i].startLocation[1] << ' ' << sandPillars[i].startLocation[2] << "~" << sandPillars[i].endLocation[0] << ' ' << sandPillars[i].endLocation[1] << ' ' << sandPillars[i].endLocation[2] << endl;
        for (int x : supportingBrickIndices) {
            // cout << "Supported By: " << sandPillars[x].startLocation[0] << ' ' << sandPillars[x].startLocation[1] << ' ' << sandPillars[x].startLocation[2] << "~" << sandPillars[x].endLocation[0] << ' ' << sandPillars[x].endLocation[1] << ' ' << sandPillars[x].endLocation[2] << endl;
            sandPillars[i].supportedBy.push_back(x);
            sandPillars[x].supports.push_back(i);
        }
        sandPillars[i].endLocation[2] -= sandPillars[i].startLocation[2] - (highestY + 1);
        sandPillars[i].startLocation[2] = (highestY + 1);
    }
}

int main() {
    while (!cin.eof()) {
        string next;
        getline(cin, next);
        if (next == "")
            break;
        stringstream ns(next);
        brick nextBrick;
        char temp;
        int x;
        ns >> x >> temp;
        nextBrick.startLocation.push_back(x);
        ns >> x >> temp;
        nextBrick.startLocation.push_back(x);
        ns >> x >> temp;
        nextBrick.startLocation.push_back(x);
        ns >> x >> temp;
        nextBrick.endLocation.push_back(x);
        ns >> x >> temp;
        nextBrick.endLocation.push_back(x);
        ns >> x;
        nextBrick.endLocation.push_back(x);
        sandPillars.push_back(nextBrick);
    }
    sort(sandPillars.begin(), sandPillars.end(), [](brick a, brick b) -> bool { return a.startLocation[2] < b.startLocation[2];});
    dropBricks();
    int answer = 0;
    for (brick x : sandPillars) {
        // cout << "Checking: " << x.startLocation[0] << ' ' << x.startLocation[1] << ' ' << x.startLocation[2] << "~" << x.endLocation[0] << ' ' << x.endLocation[1] << ' ' << x.endLocation[2] << endl;
        bool validDisintigrate = true;
        for (int y : x.supports) {
            // cout << "Supports: " << sandPillars[y].startLocation[0] << ' ' << sandPillars[y].startLocation[1] << ' ' << sandPillars[y].startLocation[2] << "~" << sandPillars[y].endLocation[0] << ' ' << sandPillars[y].endLocation[1] << ' ' << sandPillars[y].endLocation[2] << endl;
            if (sandPillars[y].supportedBy.size() == 1) {
                validDisintigrate = false;
                // cout << "Cannot Remove" << endl;
                break;
            }
        }
        if (validDisintigrate) {
            // cout << "Can Remove" << endl;
            answer++;
        }
    }
    cout << answer << endl;
    return 0;
}