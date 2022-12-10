#include <bits/stdc++.h>

using namespace std;


int check_cycle(int cycle, int x) {
  if (cycle <= 220 && (cycle+20) % 40 == 0) {
    cout << "Cycle " << cycle << " adds " << cycle*x << endl;
    return x*cycle;
  }
  return 0;
}

void print(int cycle, int x) {
  if ((x == (cycle % 40)) || ((x-1) == (cycle % 40)) || ((x+1) == (cycle % 40))) {
    cout << '#';
  } else cout << '.';
  if (cycle % 40 == 0) cout << endl;
}

int main() {
  int cycleNum = 0;
  int x = 2;
  string line;
  int answer = 0;
  while (getline(cin, line)) {
    istringstream in(line);
    string command;
    int value;
    in >> command;
    // cout << "Reading Command " << line << endl;
    if (command == "addx") {
      in >> value;
      cycleNum++;
      print(cycleNum, x);
      cycleNum++;
      print(cycleNum, x);
      x += value;
    } else {
      cycleNum++;
      print(cycleNum, x);
    }
    // cout << "X is now: " << x << endl;
    // cout << "Clock is now at: " << cycleNum << endl;
  }
  // cout << "answer: " << answer << endl;
  return 0;
}
