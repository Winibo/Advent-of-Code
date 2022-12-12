#include <bits/stdc++.h>

using namespace std;

struct Node {
  int posx = 0;
  int posy = 0;
  int steps = 0;
};

vector<string> heightMap;

int bfs(Node end) {
  queue<Node> search;
  vector<Node> seen;
  search.push(end);
  seen.push_back(end);
  while (!search.empty()) {
    Node current = search.front(); search.pop();
    // cout << "Searching node: " << current.posx << ',' << current.posy << endl;
    if (heightMap[current.posx][current.posy] == 'a') return current.steps;
    //Add left
    Node left;
    left.posx = current.posx-1;
    left.posy = current.posy;
    left.steps = current.steps + 1;
    bool searched = false;
    if (!(left.posx < 0)) {
      for (Node n : seen) {
        if (n.posx == left.posx && n.posy == left.posy) {
          searched = true;
          break;
        }
      }
      if (!searched && ((heightMap[left.posx][left.posy] - heightMap[current.posx][current.posy]) >= -1)) {
        // cout << "Adding left at y,x:" << left.posx << ',' << left.posy << endl;
        search.push(left);
        seen.push_back(left);
      }
    }
    //Add right
    Node right;
    right.posx = current.posx+1;
    right.posy = current.posy;
    right.steps = current.steps + 1;
    searched = false;
    if (!(right.posx >= heightMap.size())) {
      // cout << "Searching right at y,x:" << right.posx << ',' << right.posy << endl;
      for (Node n : seen) {
        if (n.posx == right.posx && n.posy == right.posy) {
          searched = true;
          break;
        }
      }
      if (!searched && ((heightMap[right.posx][right.posy] - heightMap[current.posx][current.posy]) >= -1)) {
        // cout << "Adding right at y,x:" << right.posx << ',' << right.posy << endl;
        search.push(right);
        seen.push_back(right);
      }
    }
    //Add up
    Node up;
    up.posx = current.posx;
    up.posy = current.posy-1;
    up.steps = current.steps + 1;
    searched = false;
    if (!(up.posy < 0)) {
      for (Node n : seen) {
        if (n.posx == up.posx && n.posy == up.posy) {
          searched = true;
          break;
        }
      }
      if (!searched && (heightMap[up.posx][up.posy] - heightMap[current.posx][current.posy] >= -1)) {
        // cout << "Adding up at y,x:" << up.posx << ',' << up.posy << endl;
        search.push(up);
        seen.push_back(up);
      }
    }
    //Add down
    Node down;
    down.posx = current.posx;
    down.posy = current.posy+1;
    down.steps = current.steps + 1;
    searched = false;
    if (!(down.posy >= heightMap[0].length())) {
      for (Node n : seen) {
        if (n.posx == down.posx && n.posy == down.posy) {
          searched = true;
          break;
        }
      }
      if (!searched && (heightMap[down.posx][down.posy] - heightMap[current.posx][current.posy] >= -1)) {
        // cout << "Adding down at y,x:" << down.posx << ',' << down.posy << endl;
        search.push(down);
        seen.push_back(down);
      }
    }
  }
  return -1;
}

int main() {
  string line;
  //Read input
  while (getline(cin, line)) {
    heightMap.push_back(line);
  }
  Node end;
  for (int x = 0; x < heightMap.size(); x++) {
    for (int y = 0; y < heightMap[x].length(); y++) {
      cout << heightMap[x][y];
      if (heightMap[x][y] == 'S') {
        heightMap[x][y] = 'a';
      }
      if (heightMap[x][y] == 'E') {
        end.posx = x;
        end.posy = y;
        heightMap[x][y] = 'z';
      }
    }
    cout << endl;
  }
  int min = INT_MAX;
  int searched = 0;
  cout << bfs(end) << endl;
  return 0;
}
