#include <bits/stdc++.h>

using namespace std;


int check_cycle(int cycle, int x) {
  if (cycle <= 220 && (cycle+20) % 40 == 0) {
    cout << "Cycle " << cycle << " adds " << cycle*x << endl;
    return x*cycle;
  }
  return 0;
}

int main() {
  int cycleNum = 0;
  int x = 1;
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
      answer += check_cycle(cycleNum, x);
      cycleNum++;
      answer += check_cycle(cycleNum, x);
      x += value;
    } else {
      cycleNum++;
      answer += check_cycle(cycleNum, x);
    }
    // cout << "X is now: " << x << endl;
    // cout << "Clock is now at: " << cycleNum << endl;
  }
  cout << "answer: " << answer << endl;
  return 0;
}
