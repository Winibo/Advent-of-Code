#include "bits/stdc++.h"

using namespace std;

const int totalSteps = 64;

struct node {
    bool rock = false;
    int minSteps = INT_MIN; //Negative since pq is max
    pair<int, int> location;
};

vector<vector<node>> graph;

void dijkstra(pair<int, int> start) {
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
        // cout << "Searching " << location.first << ' ' << location.second << endl;
        // cout << "Score: " << score << endl;
        // cout << "Best: " << graph[location.first][location.second].minSteps << endl;
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
            nextNode.location = make_pair(graph.size(), i); //Row, Column
            if (next[i] == '#') {
                nextNode.rock = true;
            } else if (next[i] == 'S') {
                start = make_pair(graph.size(), i);
            }
            temp.push_back(nextNode);
        }
        graph.push_back(temp);
    }
    dijkstra(start);
    //We can get somewhere in x steps iff total steps % 2 == minimum steps % 2 and minimum steps < total steps?
    int answer = 0;
    for (vector<node> x : graph) {
        for (node y : x) {
            if (y.rock) {
                continue;
            }
            if (totalSteps >= -y.minSteps && totalSteps % 2 == ((-y.minSteps) % 2)) {
                answer++;
            }
        }
    }
    cout << answer << endl;
    return 0;
}