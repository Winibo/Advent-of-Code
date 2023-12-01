#include <bits/stdc++.h>

using namespace std;


set<pair<int, int>> seen;

pair<int, int> move_tail(pair<int, int> head, pair<int, int> tail) {
  int horiz = abs(head.first - tail.first);
  cout << "Horizontal distance is:" << horiz << endl;
  int verti = abs(head.second - tail.second);
  cout << "Vertical distance is:" << verti << endl;
  if (verti + horiz > 2) {
    //We're 2+ away diagonally
    if (horiz == 2) {
      // H.. --> HT.
      // ..T --> ...
      tail.second = head.second;
      if (tail.first > head.first) {
        tail.first -= 1;
      } else {
        tail.first += 1;
      }
    } else {
      // .H -> .H
      // .. -> .T
      // T. -> ..
      tail.first = head.first;
      if (tail.second > head.second) {
        tail.second -= 1;
      } else {
        tail.second += 1;
      }
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
  seen.insert(tail);
  return tail;
}

int main() {
  pair<int, int> head = make_pair(0,0), tail = make_pair(0,0);
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
        head.first += 1;
        tail = move_tail(head, tail);
      }
      if (direction == 'L') {
        head.first -= 1;
        tail = move_tail(head, tail);
      }
      if (direction == 'U') {
        head.second += 1;
        tail = move_tail(head, tail);
      }
      if (direction == 'D') {
        head.second -= 1;
        tail = move_tail(head, tail);
      }
      cout << "Head is at: (" << head.first << ',' << head.second << ')' << endl;
      cout << "Tail is at: (" << tail.first << ',' << tail.second << ')' << endl;
    }
  }
  cout << seen.size() << endl;
  return 0;
}
