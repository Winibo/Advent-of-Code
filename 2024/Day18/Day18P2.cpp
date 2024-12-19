#include <bits/stdc++.h>

using namespace std;

map<pair<int, int>, int> blocks; // Position -> time

int dim = 70;

struct position {
    pair<int, int> location;
    int step = 0;
    
    bool operator <(const position& rhs ) const {
        return step > rhs.step; // Yeah, yeah, this is wrong
    }
};

vector<position> getNextPositions(position start) {
    vector<position> next;
    start.step += 1;
    for (int i = 0; i < 4; i++) {
        position nextPos = start;
        switch (i) {
            case 0:
                nextPos.location.first += 1;
                break;
            case 1:
                nextPos.location.first -= 1;
                break;
            case 2:
                nextPos.location.second += 1;
                break;
            case 3:
                nextPos.location.second -= 1;
                break;
            default:
                break;
        }
        next.push_back(nextPos);
    }
    return next;
}

map<pair<int, int>, int> getPath(position start, int startTime) {
    priority_queue<position> toSearch;
    toSearch.push(start);
    map<pair<int, int>, int> scores;
    while (!toSearch.empty()) {
        position current = toSearch.top(); toSearch.pop();
        if (blocks.count(current.location) != 0 && blocks[current.location] < startTime) { // Invalid location
            continue;
        }
        if (current.location.first < 0 || current.location.first > dim
        || current.location.second < 0 || current.location.second > dim) { // Out of bounds
            continue;
        }
        if (scores.count(current.location) != 0 && scores[current.location] <= current.step) { // Wasted effort
            continue;
        }
        vector<position> nextPositions = getNextPositions(current);
        for (position x : nextPositions) {
            toSearch.push(x);
        }
        scores[current.location] = current.step;
    }
    return scores;
}

int main()
{
    int steps = 0;
    while (!cin.eof()) {
        int a, b; char c;
        cin >> a >> c >> b;
        blocks[make_pair(a, b)] = steps;
        steps++;
    }
    position start; start.location = make_pair(0, 0); start.step = 0;
    int minStart = 1024, maxStart = blocks.size();
    
    while (maxStart - minStart > 1) {
        cout << "Min: " << minStart << " Max: " << maxStart << endl;
        map<pair<int, int>, int> maze = getPath(start, (minStart + maxStart) / 2);
        if (maze.count(make_pair(dim, dim)) == 0) {
            // Max too big
            maxStart = (minStart + maxStart) / 2;
        } else {
            // Min too small
            minStart = (minStart + maxStart) / 2;
        }
    }
    map<pair<int, int>, int> maze = getPath(start, minStart);
    assert(maze[make_pair(dim, dim)] != 0);
    for (auto x : blocks) { // Should have stored these in a vector, but I'm stupid...
        if (x.second == minStart) {
            cout << x.first.first << ',' << x.first.second << endl;
            break;
        }
    }
    return 0;
}