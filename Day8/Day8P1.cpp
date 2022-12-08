#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, bool>>> trees;

void calc_visible() {
  int max = 0;
  //from left
  for (int row = 0; row < trees.size(); row++) {
    for (int column = 0; column < trees[row].size(); column++) {
      if (column == 0) {
        trees[row][column].second = true;
        max = trees[row][column].first;
      } else if (trees[row][column].first > max) {
        trees[row][column].second = true;
        max = trees[row][column].first;
      }
    }
  }
  max = 0;
  //from right
  for (int row = 0; row < trees.size(); row++) {
    for (int column = trees[row].size()-1; column >= 0; column--) {
      if (column == trees[row].size()-1) {
        trees[row][column].second = true;
        max = trees[row][column].first;
      } else if (trees[row][column].first > max) {
        trees[row][column].second = true;
        max = trees[row][column].first;
      }
    }
  }
  //from up
  for (int column = 0; column < trees.size(); column++) {
    for (int row = 0; row < trees[column].size(); row++) {
      if (row == 0) {
        trees[row][column].second = true;
        max = trees[row][column].first;
      } else if (trees[row][column].first > max) {
        trees[row][column].second = true;
        max = trees[row][column].first;
      }
    }
  }
  //from down
  for (int column = 0; column < trees.size(); column++) {
    for (int row = trees[column].size()-1; row >= 0; row--) {
      if (row == trees[column].size()-1) {
        trees[row][column].second = true;
        max = trees[row][column].first;
      } else if (trees[row][column].first > max) {
        trees[row][column].second = true;
        max = trees[row][column].first;
      }
    }
  }
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
  calc_visible();
  int answer = 0;
  for (int i = 0; i < trees.size(); i++) {
    for (int j = 0; j < trees[i].size(); j++) {
      cout << trees[i][j].second << ' ';
      if (trees[i][j].second) answer++;
    }
    cout << endl;
  }
  cout << endl;
  for (int i = 0; i < trees.size(); i++) {
    for (int j = 0; j < trees[i].size(); j++) {
      cout << trees[i][j].first << ' ';
    }
    cout << endl;
  }
  cout << trees[1][2].first << ' ' << trees[0][2].first << endl;
  cout << answer << endl;
  return 0;
}
