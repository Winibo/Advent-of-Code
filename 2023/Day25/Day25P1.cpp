#include "bits/stdc++.h"

using namespace std;

struct node {
    vector<string> neighbors;
    bool visited = true;
};

map<string, node> graph;

pair<int, vector<int>> globalMinCut(vector<vector<int>> mat) {
	pair<int, vector<int>> best = {INT_MAX, {}};
	int n = mat.size();
	vector<vector<int>> co(n);
	for (int i = 0; i < n; i++) co[i] = {i};
	for (int ph = 1; ph < n; ph++) {
		vector<int> w = mat[0];
		size_t s = 0, t = 0;
		for (int it = 0; it < n - ph; it++) { // O(V^2) -> O(E log V) with prio. queue
			w[t] = INT_MIN;
			s = t, t = max_element(w.begin(),w.end()) - w.begin();
			for (int i = 0; i < n; i++) w[i] += mat[t][i];
		}
		best = min(best, {w[t] - mat[t][t], co[t]});
		co[s].insert(co[s].end(), co[t].begin(), co[t].end());
		for (int i = 0; i < n; i++) mat[s][i] += mat[t][i];
		for (int i = 0; i < n; i++) mat[i][s] = mat[s][i];
		mat[0][t] = INT_MIN;
	}
	return best;
}


int main() {
    while (!cin.eof()) {
        string line = "";
        getline(cin, line);
        if (line == "")
            break;
        node next;
        string name;
        stringstream ls(line);
        ls >> name;
        name = name.substr(0, name.length() - 1); //Drop :
        if (graph.find(name) == graph.end()) {
            node temp;
            graph[name] = temp;
        }
        while (!ls.eof()) {
            string con = "";
            ls >> con;
            if (con == "")
                break;
            graph[name].neighbors.push_back(con);
            if (graph.find(con) == graph.end()) {
                node temp;
                graph[con] = temp;
            }
            graph[con].neighbors.push_back(name);
        }
    }
    vector<vector<int>> adjacencyList;
    for (auto x : graph) {
        vector<int> temp;
        for (auto y : graph) {

            if (x.first == y.first || find(x.second.neighbors.begin(), x.second.neighbors.end(), y.first) == x.second.neighbors.end()) {
                temp.push_back(0);
                continue;
            }
            temp.push_back(1);
        }
        adjacencyList.push_back(temp);
    }
    pair<int, vector<int>> answer = globalMinCut(adjacencyList);
    cout << answer.first << endl;
    cout << answer.second.size() << ' ' << graph.size() - answer.second.size() << endl;
    cout << (graph.size() - answer.second.size()) * answer.second.size() << endl;
    return 0;
}