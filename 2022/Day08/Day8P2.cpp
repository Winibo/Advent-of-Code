#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, bool>>> trees;

int calc_score(int rowx, int columnx) {
  int leftScore = 0;
  //Left
  for (int column = columnx-1; column >= 0; column--) {
    leftScore++;
    if (trees[rowx][column].first >= trees[rowx][columnx].first) break;
  }
  //right
  int rightScore = 0;
  for (int column = columnx+1; column < trees[rowx].size(); column++) {
    rightScore++;
    if (trees[rowx][column].first >= trees[rowx][columnx].first) break;
  }
  //up
  int upScore = 0;
  for (int row = rowx-1; row >= 0; row--) {
    upScore++;
    if (trees[row][columnx].first >= trees[rowx][columnx].first) break;
  }
  int downScore = 0;
  for (int row = rowx+1; row < trees.size(); row++) {
    downScore++;
    if (trees[row][columnx].first >= trees[rowx][columnx].first) break;
  }
  return upScore * downScore * leftScore * rightScore;
}

int main() {
  string line;
  //Read input
  while (getline(cin, line)) {
    vector<pair<int, bool>> temp;
    for (int i = 0; i < line.length(); i++) {
      temp.push_back(make_pair(line[i] - '0', false));
    }
    trees.push_back(temp);
  }
  int best = 0;
  for (int i = 0; i < trees.size(); i++) {
    for (int j = 0; j < trees[i].size(); j++) {
      int curr = calc_score(i,j);
      if (curr > best) best = curr;
    }
  }
  cout << best << endl;
  return 0;
}
