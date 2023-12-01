#include <bits/stdc++.h>

using namespace std;

const int LOCATIONS = 60; //2^6
const int COMBOS = 28737; //2^15
const int TIME = 30; // 2^5: total: 2^27
struct valve {
  string name;
  bool open = false;
  int offset = -1;
  int released;
  vector<string> connections; //Index of children
};

map<string, int> mindex;
int lOpened = 20000;
vector<valve> valves;

pair<int, int> lookup[LOCATIONS][COMBOS][TIME];

int calculate(string start, int released, int used, unsigned int opened) {
  if (opened >= lOpened) {
    cout << opened << endl;
    lOpened = opened;
  }
  // cout << "Starting Execution of " << start << "," << released << "," << used << "," << opened << endl;
  int valve = mindex[start];
  if (lookup[valve][opened][used].first != -1 && lookup[valve][opened][used].first >= released) return lookup[valve][opened][used].second;
  if (used >= TIME) return released;
  int answer = released;
  if (!valves[valve].open && valves[valve].released != 0) { //Spend a minute opening valve
    valves[valve].open = true;
    answer = max(answer, calculate(start,released + (valves[valve].released * (TIME-used)), used+1, opened + (1 << valves[valve].offset)));
    valves[valve].open = false;
  }
  for (string c : valves[valve].connections) { //Spend a minute to a different location
    answer = max(answer, calculate(c,released, used+1, opened));
  }
  lookup[valve][opened][used].first = released;
  lookup[valve][opened][used].second = answer;
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
        lookup[i][j][k] = make_pair(-1, -1);
      }
    }
  }
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
  for (valve v : valves) {
    cout << "Valve " << v.name << " Has flow " << v.released << endl;
    if (v.released != 0) {
      cout << "It's offset is: " << v.offset << endl;
    }
    cout << "Valve connected to: " << endl;
    for (string c : v.connections) {
      cout << c << endl;
    }
  }
  //560
  // cout << "Time for DD at 3" << endl << valves[mindex["DD"]].released * (30-(2)) << endl;
  // cout << calculate("DD", 0, 2, 0) << endl;
  cout << calculate("AA", 0, 1, 0) << endl;
}
