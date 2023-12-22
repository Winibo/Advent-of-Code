#include "bits/stdc++.h"

using namespace std;

const int totalSteps = 64;

struct node {
    bool rock = false;
    int minSteps = INT_MIN; //Negative since pq is max
    pair<int, int> location;
};

vector<vector<node>> baseGraph; //Base we copy from

vector<vector<node>> expandedGraph; //5x5 version of base

void dijkstra(pair<int, int> start, vector<vector<node>>& graph) {
    const vector<int> xOff = {0,0,-1,1};
    const vector<int> yOff = {-1,1,0,0};
    priority_queue<pair<pair<int, int>, int>> searchList; //Stores location, minimum
    graph[start.first][start.second].minSteps = 0;
    searchList.push(make_pair(start, 0));
    while (!searchList.empty()) {
        pair<int, int> location = searchList.top().first;
        int score = searchList.top().second; searchList.pop();
        if (score < graph[location.first][location.second].minSteps) {
            continue;
        }
        for (int i = 0; i < xOff.size(); i++) {
            if (location.first + xOff[i] < 0 || location.first + xOff[i] >= graph.size()) {
                continue;
            }
            if (location.second + yOff[i] < 0 || location.second + yOff[i] >= graph[0].size()) {
                continue;
            }
            pair<int, int> neighbor = make_pair(location.first + xOff[i], location.second + yOff[i]);
            if (!graph[neighbor.first][neighbor.second].rock && score - 1 > graph[neighbor.first][neighbor.second].minSteps) {
                searchList.push(make_pair(neighbor, score - 1));
                graph[neighbor.first][neighbor.second].minSteps = score - 1;
            }
        }
    }
}

int main() {
    pair<int, int> start;
    while (!cin.eof()) {
        string next = "";
        getline(cin, next);
        if (next == "")
            break;
        vector<node> temp;
        for (int i = 0; i < next.length(); i++) {
            node nextNode;
            nextNode.location = make_pair(baseGraph.size(), i); //Row, Column
            if (next[i] == '#') {
                nextNode.rock = true;
            } else if (next[i] == 'S') {
                start = make_pair(baseGraph.size(), i);
            }
            temp.push_back(nextNode);
        }
        baseGraph.push_back(temp);
    }
    for (int i = 0; i < baseGraph.size(); i++) {
        vector<node> temp;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < baseGraph[i].size(); k++) {
                temp.push_back(baseGraph[i][k]);
            }
        }
        expandedGraph.push_back(temp);
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < baseGraph.size(); j++) {
            expandedGraph.push_back(expandedGraph[j]);
        }
    }
    start.first = start.first + (2 * baseGraph.size());
    start.second = start.second + (2 * baseGraph[0].size());
    dijkstra(start, expandedGraph);
    //We can get somewhere in x steps iff total steps % 2 == minimum steps % 2 and minimum steps < total steps?
    //Minimum steps is cost to get there from closest corner + cost to get to that corner
    double first = 0, second = 0, third = 0;
    for (vector<node> x : expandedGraph) {
        for (node y : x) {
            if (y.rock) {
                continue;
            }
            if (65 >= -y.minSteps && (65) % 2 == ((-y.minSteps) % 2)) {
                first++;
            }
            if (65 + baseGraph.size() >= -y.minSteps && (65 + baseGraph.size()) % 2 == ((-y.minSteps) % 2)) {
                second++;
            }
            if (65 + baseGraph.size()*2 >= -y.minSteps && (65 + baseGraph.size()*2) % 2 == ((-y.minSteps) % 2)) {
                third++;
            }
        }
    }
    //Langrange Interpolation
    // cout << first << ' ' << second << ' ' << third << endl;
    long long c =  first, a = first/2 - second + third/2, b = -3*first/2 + 2*second - third/2;
    long long answer = c;
    long long xVal = (26501365 - 65) / 131;
    answer += a * xVal * xVal;
    answer += b * xVal;
    // cout << a << ' ' << b << ' ' << c << endl;
    // cout << xVal << endl;
    cout << answer << endl;
    return 0;
}