#include "bits/stdc++.h"

using namespace std;

struct state {
    int direction;
    int straightCount;
    pair<int, int> location;
};

struct node {
    pair<int, int> location;
    int direction;
    int straightCount;
    bool visited = false;
    int cost;
    int shortestCost = INT_MIN;
    int idx;
    bool ignoreMin = false;
};

vector<string> heatMap;

map<pair<int, int>, int> locMap;

const int maxDistance = 11;
const int minDistance = 4;

int search() {
    vector<node> graph;
    priority_queue<pair<int, int>> shortestList; //Score, idx;
    int index = 0;
    for (int i = 0; i < heatMap.size(); i++) { //Row
        for (int j = 0; j < heatMap[0].length(); j++) { //Columns
            locMap[make_pair(i,j)] = index;
            for (int k = 0; k < 4; k++) { //Directions
                for (int l = 0; l < maxDistance;l++) { //Straight Count
                    node next;
                    next.location = make_pair(i, j);
                    next.cost = '0' - heatMap[i][j]; //Costs negative to make my life easier
                    next.direction = k;
                    next.straightCount = l;
                    next.idx = index++;
                    graph.push_back(next);
                    if (i == 0 && j == 0 && k == 2 && l == 0) {
                        graph[graph.size() - 1].shortestCost = 0;
                        graph[graph.size() - 1].ignoreMin = true;
                        shortestList.push(make_pair(0, index - 1));
                    }
                }
            }
        }
    }
    int best = INT_MAX;
    while (!shortestList.empty()) {
        if (shortestList.top().first < graph[shortestList.top().second].shortestCost) {
            shortestList.pop();
            continue;
        }
        node current = graph[shortestList.top().second]; shortestList.pop();
        if (current.location.first == heatMap.size() - 1 && current.location.second == heatMap[0].length() - 1 && current.straightCount >= 4) {
            if (best > -current.shortestCost) {
                best = -current.shortestCost;
            }
        }

        graph[current.idx].visited = true;
        //Update neighbors
        if (current.direction != 2 && ((current.direction == 0 && current.straightCount < maxDistance - 1) || (current.direction != 0 && current.straightCount >= minDistance) || current.ignoreMin) && current.location.first > 0) { //N
            int idx = locMap[make_pair(current.location.first - 1, current.location.second)] + (11*0) + (current.direction == 0 ? (current.straightCount + 1) : 1);
            if (graph[idx].shortestCost < graph[idx].cost + current.shortestCost) {
                graph[idx].shortestCost = graph[idx].cost + current.shortestCost;
                shortestList.push(make_pair(graph[idx].cost + current.shortestCost,idx));
            }
        }
        if (current.direction != 3 && ((current.direction == 1 && current.straightCount < maxDistance - 1) || (current.direction != 1 && current.straightCount >= minDistance) || current.ignoreMin) && current.location.second < heatMap[0].length()) { //E
            int idx = locMap[make_pair(current.location.first, current.location.second + 1)] + (11*1) + (current.direction == 1 ? (current.straightCount + 1) : 1);
            if (graph[idx].shortestCost < graph[idx].cost + current.shortestCost) {
                graph[idx].shortestCost = graph[idx].cost + current.shortestCost;
                shortestList.push(make_pair(graph[idx].cost + current.shortestCost,idx));
            }
        }
        if (current.direction != 0 && ((current.direction == 2 && current.straightCount < maxDistance - 1) || (current.direction != 2 && current.straightCount >= minDistance) || current.ignoreMin) && current.location.first < heatMap.size()) { //S
            int idx = locMap[make_pair(current.location.first + 1, current.location.second)] + (11*2) + (current.direction == 2 ? (current.straightCount + 1) : 1);
            if (graph[idx].shortestCost < graph[idx].cost + current.shortestCost) {
                graph[idx].shortestCost = graph[idx].cost + current.shortestCost;
                shortestList.push(make_pair(graph[idx].cost + current.shortestCost,idx));
            }
        }
        if (current.direction != 1 && ((current.direction == 3 && current.straightCount < maxDistance - 1) || (current.direction != 3 && current.straightCount >= minDistance) || current.ignoreMin) && current.location.second > 0) { //W
            int idx = locMap[make_pair(current.location.first, current.location.second - 1)] + (11*3) + (current.direction == 3 ? (current.straightCount + 1) : 1);
            if (graph[idx].shortestCost < graph[idx].cost + current.shortestCost) {
                graph[idx].shortestCost = graph[idx].cost + current.shortestCost;
                shortestList.push(make_pair(graph[idx].cost + current.shortestCost,idx));
            }
        }
    }
    return best;
}


//This is very slow because I don't use a priority queue... Oops.
int main() {
    while (!cin.eof()) {
        string next = "";
        getline(cin, next);
        if (next == "")
            break;
        heatMap.push_back(next);
    }
    //This sucks...

    cout << search() << endl;
    return 0;
}