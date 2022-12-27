#include <bits/stdc++.h>

using namespace std;

struct Monkey {
  bool finished = false;
  bool start = false;
  long long answer = 0;
  string op1;
  string op2;
  char operand;
};

map<string, Monkey> monkeys;

long long solve(string monkey) {
  Monkey m = monkeys[monkey];
  if (m.finished) return m.answer;
  if (monkey == "humn") return m.answer;
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
    case '=':
      answer = (op1 == op2);
      break;
  }
  if (monkeys[m.op1].finished && monkeys[m.op2].finished)
    monkeys[monkey].finished = true;
  monkeys[monkey].answer = answer;
  // cout << "Answer for: " << monkey << " is " << answer << endl;
  return answer;
}

void rsolve(string monkey, long long goal) {
  // cout << "Solving monkey: " << monkey << endl;
  // cout << "Target is: " << goal << endl;
  Monkey m = monkeys[monkey];
  monkeys[monkey].answer = goal;
  m.finished = true;
  if (monkey == "humn") return;
  if (monkeys[m.op1].finished) { //If the first operand is correct
    switch(m.operand) {
      case '+':
        rsolve(m.op2, goal-monkeys[m.op1].answer);
        break;
      case '-':
        rsolve(m.op2, monkeys[m.op1].answer - goal);
        break;
      case '*':
        assert(goal % monkeys[m.op1].answer == 0);
        rsolve(m.op2, goal / monkeys[m.op1].answer);
        break;
      case '/':
        assert(monkeys[m.op1].answer % goal == 0);
        rsolve(m.op2,monkeys[m.op1].answer / goal);
        break;
    }
  } else if (monkeys[m.op2].finished) { //If the second operand is correct
    switch(m.operand) {
      case '+':
        rsolve(m.op1, goal-monkeys[m.op2].answer);
        break;
      case '-':
        rsolve(m.op1, goal+monkeys[m.op2].answer);
        break;
      case '*':
        assert(goal % monkeys[m.op2].answer == 0);
        rsolve(m.op1, goal / monkeys[m.op2].answer);
        break;
      case '/':
        rsolve(m.op1, goal * monkeys[m.op2].answer);
        break;
    }
  } else {
    cout << "Circular loop" << endl;
    assert(false);
  }
}

string getEquation(string monkey) {
  Monkey m = monkeys[monkey];
  if (monkey == "humn") return "x";
  if (m.start) return to_string(m.answer);
  string op1 = getEquation(m.op1);
  string op2 = getEquation(m.op2);
  string answer = "";
  if (isdigit(op1[0]) && isdigit(op2[0])) {
    switch (m.operand) {
      case '+':
        answer = to_string(stoi(op1) + stoi(op2));
        break;
      case '-':
        answer = to_string(stoi(op1) - stoi(op2));
        break;
      case '*':
        answer = to_string(stoi(op1) * stoi(op2));
        break;
      case '/':
        answer = to_string(stoi(op1) / stoi(op2));
        break;
    }
  } else answer = "(" + op1 + m.operand + op2 + ")";
  return answer;
}

int main() {
  string line;
  //Read file
  cout << "Reading input" << endl;
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
      if (name != "humn")
        m.finished = true;
      m.start = true;
    } else { //We have an opertion monkey
      m.op1 = op1;
      in >> operand >> op2;
      m.op2 = op2;
      m.operand = operand;
    }
    monkeys.insert(make_pair(name, m));
  }
  cout << "Done reading input" << endl;
  //Get answer
  cout << "Root says:";
  solve("root");
  cout << monkeys["root"].answer << endl;
  if (monkeys[monkeys["root"].op1].finished) {
    cout << "Op1 is valid" << endl;
    rsolve(monkeys["root"].op2, monkeys[monkeys["root"].op1].answer);
  } else if (monkeys[monkeys["root"].op2].finished) {
    cout << "Op2 is valid" << endl;
    rsolve(monkeys["root"].op1, monkeys[monkeys["root"].op2].answer);
  } else {
    cout << "Circular loop" << endl;
    cout << "First half is: " << getEquation(monkeys["root"].op1) << endl;
    cout << "Second half is: " << getEquation(monkeys["root"].op2) << endl;
    return 0;
  }
  cout << "Human says:" << monkeys["humn"].answer << endl;
}
