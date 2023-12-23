#include "bits/stdc++.h"

using namespace std;

struct node {
    pair<int, int> location;
    char value;
    int shortestPath = 0;
    vector<pair<int, int>> children;
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
        if (current.first + 1 != parent.first && graph[current.first + 1][current.second].value != '#' && graph[current.first + 1][current.second].value != '^') {
            searchList.push(make_pair(current, make_pair(current.first + 1,current.second)));
            graph[current.first][current.second].children.push_back(make_pair(current.first + 1,current.second));
        }
        if (current.first - 1 != parent.first && graph[current.first - 1][current.second].value != '#' && graph[current.first - 1][current.second].value != 'v') {
            searchList.push(make_pair(current, make_pair(current.first - 1,current.second)));
            graph[current.first][current.second].children.push_back(make_pair(current.first - 1,current.second));
        }
        if (current.second + 1 != parent.second && graph[current.first][current.second + 1].value != '#' && graph[current.first][current.second + 1].value != '<') {
            searchList.push(make_pair(current, make_pair(current.first,current.second + 1)));
            graph[current.first][current.second].children.push_back(make_pair(current.first,current.second + 1));
        }
        if (current.second - 1 != parent.second && graph[current.first][current.second - 1].value != '#' && graph[current.first][current.second - 1].value != '>') {
            searchList.push(make_pair(current, make_pair(current.first,current.second - 1)));
            graph[current.first][current.second].children.push_back(make_pair(current.first,current.second - 1));
        }
    }
}

int dijkstra(pair<int, int> start, pair<int, int> end) {

    priority_queue<pair<pair<int, int>, int>> searchList; //Node to search, score
    searchList.push(make_pair(make_pair(start.first,start.second), 0));
    while (!searchList.empty()) {
        pair<int, int> current = searchList.top().first;
        int score = searchList.top().second; searchList.pop();
        for (pair<int, int> child : graph[current.first][current.second].children) {
            if (graph[child.first][child.second].shortestPath < score + 1) {
                searchList.push(make_pair(child, score + 1));
                graph[child.first][child.second].shortestPath = score + 1;
            }
        }
    }
    return graph[end.first][end.second].shortestPath;
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
    setChildren();
    cout << dijkstra(make_pair(0,1), make_pair(graph.size() - 1, graph[0].size() - 2)) << endl;
    return 0;
}