#include <bits/stdc++.h>

using namespace std;

struct node {
  string name;
  vector<string> connections;
  bool visited = false;
};

map<string, node> graph;

bool nodeSort(node a, node b) {
  return a.name < b.name;
}

vector<node> best;

void searchCliques(vector<node>& nodes, vector<node>& current,  int start = 0) {
  if (current.size() > best.size()) {
    best = current;
  }
  for (int i = start; i < nodes.size(); i++) {
    if (current.size() == 0) {
      cout << "Testing: " << i << " Out of " << nodes.size() << endl;
    }
    node n = nodes[i];
    // Search for neighbors
    bool valid = true;
    for (node neighbor : current) {
      // Ensure test node is not already included
      if (n.name == neighbor.name) {
         valid = false;
         break;
      }
      if (find(n.connections.begin(), n.connections.end(), neighbor.name) == n.connections.end()) {
        valid = false;
        break;
      }
    }
    if (valid) {
      vector<node> temp = current;
      temp.push_back(n);
      searchCliques(nodes, temp, i + 1);
    }
  }
  return;
}

int main() {
  while (!cin.eof()) {
    string a, b;
    getline(cin, a, '-');
    getline(cin, b);
    graph[a].name = a;
    graph[b].name = b;
    graph[a].connections.push_back(b);
    graph[b].connections.push_back(a);
  }
  vector<node> x;
  for (auto y : graph) {
    x.push_back(y.second);
  }
  // Get answer
  vector<node> bleh;
  searchCliques(x, bleh);
  sort(best.begin(), best.end(), nodeSort);
  for (auto x : best) {
    cout << x.name << ',';
  }
}
