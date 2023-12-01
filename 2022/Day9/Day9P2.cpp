#include <bits/stdc++.h>

using namespace std;


set<pair<int, int>> seen;

pair<int, int> move_tail(pair<int, int> head, pair<int, int> tail) {
  int horiz = abs(head.first - tail.first);
  //cout << "Horizontal distance is:" << horiz << endl;
  int verti = abs(head.second - tail.second);
  //cout << "Vertical distance is:" << verti << endl;
  if (verti + horiz > 2) {
    //We're 2+ away diagonally
    if (tail.first > head.first) {
      tail.first -= 1;
    } else {
      tail.first += 1;
    }
    if (tail.second > head.second) {
      tail.second -= 1;
    } else {
      tail.second += 1;
    }
  } else if (verti > 1) {
    //We're 2+ away vertically
    if (tail.second > head.second) {
      tail.second -= 1;
    } else {
      tail.second += 1;
    }
  } else if (horiz > 1) {
    //We're too far away horizontally
    if (tail.first > head.first) {
      tail.first -= 1;
    } else {
      tail.first += 1;
    }
  } //We do nothing if we're fine
  return tail;
}

int main() {
  pair<int, int> head = make_pair(0,0), tail = make_pair(0,0);
  pair<int, int> rope[10];
  for (int i = 0; i < 10; i++) {
    rope[i] = make_pair(0,0);
  }
  seen.insert(make_pair(0, 0));
  string line;
  while (getline(cin, line)) {
    cout << "reading line:" << line << endl;
    istringstream in(line);
    char direction;
    int distance;
    in >> direction >> distance;
    for (int i = 0; i < distance; i++) {
      if (direction == 'R') {
        rope[0].first += 1;
        for (int i = 0; i < 9; i++) {
          rope[i+1] = move_tail(rope[i], rope[i+1]);
        }
      }
      if (direction == 'L') {
        rope[0].first -= 1;
        for (int i = 0; i < 9; i++) {
          rope[i+1] = move_tail(rope[i], rope[i+1]);
        }
      }
      if (direction == 'U') {
        rope[0].second += 1;
        for (int i = 0; i < 9; i++) {
          rope[i+1] = move_tail(rope[i], rope[i+1]);
        }
      }
      if (direction == 'D') {
        rope[0].second -= 1;
        for (int i = 0; i < 9; i++) {
          rope[i+1] = move_tail(rope[i], rope[i+1]);
        }
      }
      seen.insert(rope[9]);
      for (int i = 0; i < 10; i++) {
        cout << "Rope[" << i <<"] is at: (" << rope[i].first << ',' << rope[i].second << ')' << endl;
      }
      cout << endl;
    }
  }
  cout << seen.size() << endl;
  return 0;
}
