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
    int shortestCost = INT_MAX;
    int idx;
};

vector<string> heatMap;

map<pair<int, int>, int> locMap;

int search() {
    vector<node> graph;
    int index = 0;
    for (int i = 0; i < heatMap.size(); i++) { //Row
        for (int j = 0; j < heatMap[0].length(); j++) { //Columns
            locMap[make_pair(i,j)] = index;
            for (int k = 0; k < 4; k++) { //Directions
                for (int l = 0; l < 4;l++) { //Straight Count
                    node next;
                    next.location = make_pair(i, j);
                    next.cost = heatMap[i][j] - '0';
                    next.direction = k;
                    next.straightCount = l;
                    next.idx = index++;
                    graph.push_back(next);
                    if (i == 0 && j == 0 && k == 2 && l == 0) {
                        graph[graph.size() - 1].shortestCost = 0;
                    }
                }
            }
        }
    }

    while (true) {
        node temp;
        node& current = temp;
        //Search graph
        for (node& x : graph) {
            if (x.shortestCost < current.shortestCost && !x.visited) {
                current = x;
            }
        }
        if (current.location.first == heatMap.size() - 1 && current.location.second == heatMap[0].length() - 1) {
            return current.shortestCost;
        }

        if (current.shortestCost == INT_MAX || current.visited) {
            break;
        }

        graph[current.idx].visited = true;
        //Update neighbors
        if (current.direction != 2 && (current.direction != 0 || current.straightCount < 3) && current.location.first > 0) { //N
            int idx = locMap[make_pair(current.location.first - 1, current.location.second)] + (4*0) + (current.direction == 0 ? (current.straightCount + 1) : 1);
            graph[idx].shortestCost = min(graph[idx].shortestCost, graph[idx].cost + current.shortestCost);
        }
        if (current.direction != 3 && (current.direction != 1 || current.straightCount < 3) && current.location.second < heatMap[0].length()) { //E
            int idx = locMap[make_pair(current.location.first, current.location.second + 1)] + (4*1) + (current.direction == 1 ? (current.straightCount + 1) : 1);
            graph[idx].shortestCost = min(graph[idx].shortestCost, graph[idx].cost + current.shortestCost);
        }
        if (current.direction != 0 && (current.direction != 2 || current.straightCount < 3) && current.location.first < heatMap.size()) { //S
            int idx = locMap[make_pair(current.location.first + 1, current.location.second)] + (4*2) + (current.direction == 2 ? (current.straightCount + 1) : 1);
            graph[idx].shortestCost = min(graph[idx].shortestCost, graph[idx].cost + current.shortestCost);
        }
        if (current.direction != 1 && (current.direction != 3 || current.straightCount < 3) && current.location.second > 0) { //W
            int idx = locMap[make_pair(current.location.first, current.location.second - 1)] + (4*3) + (current.direction == 3 ? (current.straightCount + 1) : 1);
            graph[idx].shortestCost = min(graph[idx].shortestCost, graph[idx].cost + current.shortestCost);
        }
    }
    int finalidx = locMap[make_pair(heatMap.size() - 1, heatMap[0].length() - 1)];
    int answer = INT_MAX;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            answer = min(graph[finalidx + i + j].shortestCost, answer);
        }
    }
    return answer;
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