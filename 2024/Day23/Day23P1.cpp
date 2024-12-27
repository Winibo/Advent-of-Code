#include <bits/stdc++.h>

using namespace std;

struct node {
  string name;
  vector<string> connections;
  bool visited = false;
};

map<string, node> graph;

map<tuple<string, string, string>, bool> seen;

bool nodeSort(node a, node b) {
  return a.name < b.name;
}

void searchCliques(vector<node> nodes, vector<node> current) {
  if (current.size() == 3) {
    sort(current.begin(), current.end(), nodeSort);
    seen[make_tuple(current[0].name,current[1].name,current[2].name)] = true;
    return;
  }
  for (node n : nodes) {
    // Always start at a node starting with t
    if (n.name[0] != 't' && current.size() == 0) continue;
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
      searchCliques(nodes, temp);
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
  cout << seen.size() << endl;
  for (auto x : seen) {
    cout << get<0>(x.first) << endl;
    cout << get<1>(x.first) << endl;
    cout << get<2>(x.first) << endl;
    cout << endl;
  }
}
