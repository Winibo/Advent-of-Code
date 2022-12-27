#include <bits/stdc++.h>

using namespace std;

struct Monkey {
  bool finished = false;
  long long answer;
  string op1;
  string op2;
  char operand;
};

map<string, Monkey> monkeys;


long long solve(string monkey) {
  Monkey m = monkeys[monkey];
  if (m.finished) return m.answer;
  long long op1 = solve(m.op1);
  long long op2 = solve(m.op2);
  long long answer = 0;
  switch (m.operand) {
    case '+':
      answer = op1 + op2;
      break;
    case '-':
      answer = op1 - op2;
      break;
    case '*':
      answer = op1 * op2;
      break;
    case '/':
      answer = op1 / op2;
      break;
  }
  m.finished = true;
  m.answer = answer;
  return answer;
}

int main() {
  string line;
  //Read file
  while (getline(cin, line)) {
    string name;
    string op1, op2;
    char operand;
    istringstream in(line);
    in >> name >> op1;
    name = name.substr(0, name.length()-1);
    Monkey m;
    if ('0' <= op1[0] && op1[0] <= '9') { //If we have a number monkey
      m.answer = stoi(op1);
      m.finished = true;
    } else { //We have an opertion monkey
      m.op1 = op1;
      in >> operand >> op2;
      m.op2 = op2;
      m.operand = operand;
    }
    monkeys.insert(make_pair(name, m));
  }
  //Get answer
  cout << "Root says:" << solve("root") << endl;
}
