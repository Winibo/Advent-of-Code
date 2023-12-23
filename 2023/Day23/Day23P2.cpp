#include "bits/stdc++.h"

using namespace std;

struct node {
    pair<int, int> location;
    char value;
    int bestScore = 0;
    vector<pair<pair<int, int>, int>> children; //Location, weight
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
            graph[current.first][current.second].children.push_back(make_pair(make_pair(current.first + 1,current.second), 1));
        }
        if (current.first - 1 >= 0 && graph[current.first - 1][current.second].value != '#') {
            searchList.push(make_pair(current, make_pair(current.first - 1,current.second)));
            graph[current.first][current.second].children.push_back(make_pair(make_pair(current.first - 1,current.second), 1));
        }
        if (graph[current.first][current.second + 1].value != '#') {
            searchList.push(make_pair(current, make_pair(current.first,current.second + 1)));
            graph[current.first][current.second].children.push_back(make_pair(make_pair(current.first,current.second + 1), 1));
        }
        if (graph[current.first][current.second - 1].value != '#') {
            searchList.push(make_pair(current, make_pair(current.first,current.second - 1)));
            graph[current.first][current.second].children.push_back(make_pair(make_pair(current.first,current.second - 1), 1));
        }
    }
}

void shrinkChildren() {
    queue<pair<int, int>> searchList;
    searchList.push(make_pair(0,1));
    while (!searchList.empty()) {
        int i = searchList.front().first, j = searchList.front().second; searchList.pop();
        // if (graph[i][j].value != '#') {
        //     cout << "Node: " << i << ' ' << j << endl;
        // }
        bool addChildren = false;
        for (int k = 0; k < graph[i][j].children.size(); k++) {
            pair<int, int> previous = make_pair(i, j);
            while (graph[graph[i][j].children[k].first.first][graph[i][j].children[k].first.second].children.size() == 2) {
                addChildren = true;
                // cout << "Child Was: " << graph[i][j].children[k].first.first << ' ' << graph[i][j].children[k].first.second << endl;
                if (graph[graph[i][j].children[k].first.first][graph[i][j].children[k].first.second].children[0].first != previous) {
                    previous = graph[i][j].children[k].first;
                    graph[i][j].children[k].second += graph[graph[i][j].children[k].first.first][graph[i][j].children[k].first.second].children[0].second;
                    graph[i][j].children[k].first = graph[graph[i][j].children[k].first.first][graph[i][j].children[k].first.second].children[0].first;
                } else {
                    previous = graph[i][j].children[k].first;
                    graph[i][j].children[k].second += graph[graph[i][j].children[k].first.first][graph[i][j].children[k].first.second].children[1].second;
                    graph[i][j].children[k].first = graph[graph[i][j].children[k].first.first][graph[i][j].children[k].first.second].children[1].first;
                }
                // cout << "Child now: " << graph[i][j].children[k].first.first << ' ' << graph[i][j].children[k].first.second << endl;
            }
        }
        if (addChildren) {
            for (auto x : graph[i][j].children) {
                searchList.push(x.first);
            }
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
    
    // cout << "Score: " << score << endl;
    graph[start.first][start.second].visited = true;
    for (auto childset : graph[start.first][start.second].children) {
        pair<int, int> child = childset.first;
        // cout << "Node: " << start.first << ' ' << start.second << endl;
        // cout << "Visiting Child: " << child.first << ' ' << child.second << endl;
        if (!graph[child.first][child.second].visited) {
            graph[start.first][start.second].bestScore = max(dijkstra(child, score + childset.second), graph[start.first][start.second].bestScore);
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
    cout << "Shrinking Children" << endl;
    shrinkChildren();
    cout << "Running Dijkstra" << endl;
    endLoc = make_pair(graph.size() - 1, graph[0].size() - 2);
    cout << dijkstra(make_pair(0,1), 0) << endl;
    return 0;
}