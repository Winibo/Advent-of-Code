#include <bits/stdc++.h>

using namespace std;

const int TESTROW = 2000000;
// const int TESTROW = 10;

set<pair<int, int>> nobeacon;

void calc(pair<int, int> start, pair<int, int> skip, int distance) {
  queue<pair<int, int>> test;
  test.push(start);
  set<pair<int, int>> seen;
  while (!test.empty()) {
    pair<int, int> current;
    current = test.front(); test.pop();
    if (seen.find(current) != seen.end()) continue;
    seen.insert(current);
    if ((abs(current.first - start.first) + abs(start.second - TESTROW)) <= distance) {
      if (current != skip)
        nobeacon.insert(make_pair(current.first, TESTROW));
      test.push(make_pair(current.first-1, TESTROW));
      test.push(make_pair(current.first+1, TESTROW));
    }
  }
}

int main() {
  string line;
  int temp = 0;
  vector<pair<int, int>> online;
  while (getline(cin, line)) {
    istringstream in(line);
    string skip;
    char sk;
    int currx, curry;
    int beacx, beacy;
    in >> skip >> skip >> sk >> sk >> currx;
    in >> skip >> sk >> sk >> curry;
    in >> skip >> skip >> skip;
    in >> skip >> skip >> sk >> sk >> beacx;
    in >> skip >> sk >> sk >> beacy;
    int taxi = abs(currx - beacx) + abs(curry - beacy);
    temp++;
    calc(make_pair(currx, curry), make_pair(beacx, beacy), taxi);
    if (beacy == TESTROW) online.push_back(make_pair(beacx, beacy));
  }
  int answer = 0;
  for (pair<int, int> p : nobeacon) {
    // cout << p.first << ',' << p.second << endl;
    if (find(online.begin(), online.end(), p) == online.end()) {
      answer++;
    }
  }
  cout << answer << endl;
  return 0;
}
