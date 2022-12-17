#include <bits/stdc++.h>

using namespace std;

const int LOCATIONS = 60; //2^6
const int COMBOS = 32768; //2^15
// const int COMBOS = 64;
const int TIME = 26; // 2^5: total: 2^27
// const int IMPORTANT = 15;
// const int IMPORTANT = 6;
struct valve {
  string name;
  int offset = -1;
  int released;
  vector<string> connections; //Index of children
};

map<string, int> mindex;
vector<valve> valves;

int lookup[LOCATIONS][COMBOS][TIME];

int calculate(string start, int used, unsigned int opened) {
  // cout << "Starting Execution of " << start << "," << released << "," << used << "," << opened << endl;
  int valve = mindex[start];
  if (lookup[valve][opened][used] != -1) return lookup[valve][opened][used];
  if (used == TIME) return 0;
  int answer = 0;
  if (valves[valve].released != 0 && opened != (opened | (1 << valves[valve].offset))) { //Spend a minute opening valve
    answer = max(answer, calculate(start, used+1, opened | (1 << valves[valve].offset)) + (valves[valve].released * (TIME-used)));
  }
  for (string c : valves[valve].connections) { //Spend a minute to a different location
    answer = max(answer, calculate(c, used+1, opened));
  }
  lookup[valve][opened][used] = answer;
  // cout << "Best Pressure release starting at " << start << " With time used " << used << endl;
  // cout << answer << endl;
  // cout << "Ending Execution of " << start << "," << released << "," << used << "," << opened << endl;
  return answer;
}

int main() {
  //Setup lookup table
  for (int i = 0; i < LOCATIONS; i++) {
    for (int j = 0; j < COMBOS; j++) {
      for (int k = 0; k < TIME; k++) {
        lookup[i][j][k] = -1;
      }
    }
  }
  int full = 0;
  string line;
  int off = 0;
  while (getline(cin, line)) {
    istringstream in(line);
    string skip;
    char sk;
    string name;
    int flow;
    in >> skip >> name;
    valve next;
    next.name = name;
    in >> skip >> skip >> sk >>sk >> sk >> sk >> sk >> flow;
    next.released = flow;
    if (flow > 0) {
      next.offset = off;
      full |= (1 << off);
      off++;
    }
    vector<string> connected;
    in >> skip >> skip >> skip >> skip >> skip;
    while (!in.eof()) {
      in >> sk;
      string answer;
      answer = answer + sk;
      in >> sk;
      answer = answer + sk;
      connected.push_back(answer);
      in >> sk;
    }
    mindex[name] = valves.size();
    next.connections = connected;
    valves.push_back(next);
  }
  int answer = 0;
  //Try all combos of open valves
  //I needed to see Howard Cheng's solution to get this part
  //And I don't think I would've come up with this on my own
  for (int open = 0; open < (1 << off); open++) {
    if (open % 5000 == 0) cout << "Testing open: " << open << endl;
    if (__builtin_popcount(open) > off/2) continue;
    unsigned int mask1 = 0, mask2 = 0;
    for (int set = 0; set < off; set++) {
      if (open & (1<<set)) {
        mask1 |= (1<<set);
      }
    }
    mask2 = full - mask1;
    int human = calculate("AA", 1, mask1);
    int elephant = calculate("AA", 1, mask2);
    answer = max(answer,human+elephant);
  }
  cout << answer << endl;
  cout << calculate("AA", 1, 0) << endl;
}
