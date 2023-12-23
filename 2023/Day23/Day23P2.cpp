#include "bits/stdc++.h"

using namespace std;

struct node {
    pair<int, int> location;
    char value;
    int bestScore = 0;
    vector<pair<int, int>> children;
    bool visited = false;
};

vector<vector<node>> graph; //Row, Column

void setChildren() {
    queue<pair<pair<int, int>, pair<int, int>>> searchList; //Previous, ToSearch
    searchList.push(make_pair(make_pair(-1,1),make_pair(0,1)));
    while (!searchList.empty()) {
        pair<int, int> parent = searchList.front().first;
        pair<int, int> current = searchList.front().second; searchList.pop();
        if (graph[current.first][current.second].children.size() != 0 || current.first + 1 >= graph.size()) {
            continue; //Already done this part
        }
        if (graph[current.first + 1][current.second].value != '#') {
            searchList.push(make_pair(current, make_pair(current.first + 1,current.second)));
            graph[current.first][current.second].children.push_back(make_pair(current.first + 1,current.second));
        }
        if (current.first - 1 >= 0 && graph[current.first - 1][current.second].value != '#') {
            searchList.push(make_pair(current, make_pair(current.first - 1,current.second)));
            graph[current.first][current.second].children.push_back(make_pair(current.first - 1,current.second));
        }
        if (graph[current.first][current.second + 1].value != '#') {
            searchList.push(make_pair(current, make_pair(current.first,current.second + 1)));
            graph[current.first][current.second].children.push_back(make_pair(current.first,current.second + 1));
        }
        if (graph[current.first][current.second - 1].value != '#') {
            searchList.push(make_pair(current, make_pair(current.first,current.second - 1)));
            graph[current.first][current.second].children.push_back(make_pair(current.first,current.second - 1));
        }
    }
}

pair<int, int> endLoc;

int bestScore = 0;

int dijkstra(pair<int, int> start, int score) {
    if (start.first == endLoc.first && start.second == endLoc.second) {
        if (score > bestScore) {
            bestScore = score;
            cout << bestScore << endl;
        }
        return score;
    }
    graph[start.first][start.second].visited = true;
    for (pair<int, int> child : graph[start.first][start.second].children) {
        if (!graph[child.first][child.second].visited) {
            graph[start.first][start.second].bestScore = max(dijkstra(child, score + 1), graph[start.first][start.second].bestScore);
        }
    }
    graph[start.first][start.second].visited = false;
    return bestScore;
}

int main() {
    while (!cin.eof()) {
        string next = "";
        getline(cin, next);
        if (next == "") 
            break;
        vector<node> temp;
        for (int i = 0; i < next.length(); i++) {
            node nextNode;
            nextNode.location = make_pair(graph.size(), i);
            nextNode.value = next[i];
            temp.push_back(nextNode);
        }
        graph.push_back(temp);
    }
    cout << "Setting Children" << endl;
    setChildren();
    cout << "Running Dijkstra" << endl;
    endLoc = make_pair(graph.size() - 1, graph[0].size() - 2);
    cout << dijkstra(make_pair(0,1), 0) << endl;
    return 0;
}