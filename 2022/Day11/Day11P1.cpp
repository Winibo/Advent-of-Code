#include <bits/stdc++.h>

using namespace std;

class Monkey {
public:
  Monkey(vector<int> startItems, string operation, int test, int trueThrow, int falseThrow):
  test(test), trueTest(trueThrow), falseTest(falseThrow) {
    for (int i : startItems) {
      items.push(i);
    }
    istringstream i(operation);
    cout << "Operation is: " << operation << endl;
    i >> operand;
    cout << "Operand is: " << operand << endl;
    i >> op2;
    cout << "Op2 is: " << op2 << endl;
    cout << "test is divisible by: " << test << endl;
    cout << "Will throw to " << trueTest << " when test is true" << endl;
    cout << "Will throw to " << falseTest << " when test is false" << endl;
    inspectCount = 0;
  }
  vector<pair<int, long long>> inspect() {
    vector<pair<int, long long>> answer;
    while (!items.empty()) {
      long long item = items.front(); items.pop();
      // cout << "Inspecting Item " << item << endl;
      inspectCount++;
      // cout << "Inspect count is now: " << inspectCount << endl;
      switch (operand) {
        case '+':
          if (op2 == "old") {
            item = item + item;
          } else {
            item = item + stoi(op2);
          }
          break;
        case '*':
          if (op2 == "old") {
            item = item * item;
          } else {
            item = item * stoi(op2);
          }
          break;
        default:
        cout << "Something Broke :(" << endl;
      }
      cout << "worry is now: " << item << endl;
      item = item / 3; //didn't get broken!
      cout << "Worry div 3 is: " << item << endl;
      //Run test
      if (item % test == 0) {
        answer.push_back(make_pair(trueTest, item));
        cout << "Passed test div " << test << endl;
      } else {
        answer.push_back(make_pair(falseTest, item));
        cout << "Failed test div " << test << endl;
      }
    }
    return answer;
  }
  int getInspectCount() {return inspectCount;}
  void addNew(long long item) {
    items.push(item);
  }
private:
  queue<long long> items;
  int inspectCount;
  char operand;
  string op2;
  int test;
  int trueTest;
  int falseTest;
};

const int MONKEYS = 8;

int main() {
  string line;
  Monkey* monkeys[8];
  for (int i = 0; i < MONKEYS; i++) {
    getline(cin, line);
    getline(cin, line);
    istringstream in(line);
    string temp;
    vector<int> items;
    int item;
    //Get starting items
    // cout << "Line is: " << line << endl;
    in >> temp >> temp >> item;
    while (!in.eof()) {
      items.push_back(item);
      in >> temp;
      // cout << "Temp is now: " << temp << endl;
      in >> item;
    }
    items.push_back(item);
    // cout << "Monkey " << i << " Starting items: " << endl;
    for (int i : items) {
      cout << i << endl;
    }
    //Get Operation
    getline(cin, line);
    // cout << "Line is: " << line << endl;
    string operation = line.substr(23,99999);
    //Get test
    getline(cin, line);
    // cout << "Line is: " << line << endl;
    istringstream test(line);
    int testval;
    test >> temp >> temp >> temp >> testval;
    //Get True monkey
    getline(cin, line);
    // cout << "Line is: " << line << endl;
    istringstream ttest(line);
    int t;
    ttest >> temp >> temp >> temp >> temp >> temp >> t;
    //Get false monkey
    getline(cin, line);
    // cout << "Line is: " << line << endl;
    istringstream ftest(line);
    int f;
    ftest >> temp >> temp >> temp >> temp >> temp >> f;
    //Add a monkey;
    monkeys[i] = new Monkey(items, operation, testval, t, f);
  }
  //Sim monkey business!
  for (int i = 0; i < 20; i++) {
    cout << "Round " << i+1 << endl;
    for (int j = 0; j < MONKEYS; j++) {
      cout << endl <<  "Monkey " << j << " inspecting" << endl << endl;
      vector<pair<int,long long>> next;
      next = monkeys[j]->inspect();
      for (pair<int,long long> receiver : next) {
        monkeys[receiver.first]->addNew(receiver.second);
      }
    }
  }
  //Get answer
  int best = 0;
  int second = 0;
  for (int i = 0; i < MONKEYS; i++) {
    int current = monkeys[i]->getInspectCount();
    cout << "Monkey " << i << " Inspect count is: " << current << endl;
    if (current > best) {
      best = current + best;
      current = best - current;
      best = best - current;
    }
    if (current > second) {
      second = current;
    }
    delete monkeys[i];
  }
  cout << "Best:" << best << endl;
  cout << "Second:" << second << endl;
  cout << "Monkey Business:" << best*second << endl;
  return 0;
}
