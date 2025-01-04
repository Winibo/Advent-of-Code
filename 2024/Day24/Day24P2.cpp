#include <bits/stdc++.h>

using namespace std;

enum operation {
  AND,
  OR,
  XOR,
  NONE
};

struct node {
  string name;
  long long value;
  bool calculated = false; // This probably doesn't work either?
  operation op = NONE;
  bool visited = false; // This doesn't work :( I don't care though ;)
  node* left = nullptr;
  node* right = nullptr;
};

long long evaluateNode(node x) {
  if (x.calculated) return x.value;
  x.calculated = true;
  switch (x.op) {
    case OR:
      x.value = evaluateNode(*x.left) || evaluateNode(*x.right);
      break;
    case AND:
      x.value = evaluateNode(*x.left) && evaluateNode(*x.right);
      break;
    case XOR:
      x.value = evaluateNode(*x.left) ^ evaluateNode(*x.right);
      break;
    case NONE:
      break;
  };
  return x.value;
}

bool sortNode(node a, node b) {
  return a.name > b.name;
}

long long getResults(vector<node>& nodes) {
  long long result = 0;
  sort(nodes.begin(), nodes.end(), sortNode);
  for (node val : nodes) {
    result = (result << 1) + evaluateNode(val);
  }
  return result;
}

vector<int> getSum(vector<node> x, vector<node> y) {
  vector<int> answer;
  int carry = 0;
  for (int i = 0; i < x.size(); i++) {
    int intermediate = x[i].value ^ y[i].value;
    answer.push_back(intermediate ^ carry);
    carry = (intermediate && carry) || (x[i].value && y[i].value);
  }
  answer.push_back(carry);
  reverse(answer.begin(), answer.end());
  return answer;
}


set<string> getSwaps(vector<node> outputs) {
  set<string> swaps;
  for (node x : outputs) {
    queue<node> toSearch;
    toSearch.push(x);
    while (!toSearch.empty()) {
      node current = toSearch.front(); toSearch.pop();
      if (current.visited) continue;
      current.visited = true;
      if (current.op == NONE) continue;
      toSearch.push(*current.left);
      toSearch.push(*current.right);
      switch (current.op) {
        case AND:
          // Connected to OR but not XOR -> XOR input wrong
          // Connected to X or Y but not both -> Non X/Y input wrong
          if (current.left->op == OR || current.right->op == OR) {
            bool valid = (current.left->op == OR || current.right->op == XOR) && (current.left->op == OR || current.right->op == OR);
            if (!valid) {
              if (current.left->op != OR && current.left->op != XOR) swaps.insert(current.left->name);
              if (current.right->op != OR && current.right->op != XOR) swaps.insert(current.right->name);
            }
          } else {
            if (current.left->op == AND && (current.left->left->op == NONE || current.left->right->op == NONE)) continue;
            if (current.right->op == AND && (current.right->left->op == NONE || current.right->right->op == NONE)) continue;
            if (current.left->op != NONE) swaps.insert(current.left->name);
            if (current.right->op != NONE) swaps.insert(current.right->name);
          }
          if (current.name[0] == 'z') swaps.insert(current.name); // Connected to Zxx
          break;
        case OR:
          // Any non-AND gate connection is wrong
          if (current.left->op != AND) swaps.insert(current.left->name);
          if (current.right->op != AND) swaps.insert(current.right->name);
          if (current.name[0] == 'z' && current.name != outputs[0].name) swaps.insert(current.name); // Connected to Zxx
          break;
        case XOR:
          // Zxx must have 1 OR and 1 XOR connection -> If not either the output or 1 input is swapped
          // NOT Zxx must have Xxx Yxx connections (or the input is swapped)
          if (current.name[0] == 'z') {
            int valid = (current.left->op == XOR || current.right->op == XOR) + (current.left->op == OR || current.right->op == OR);
            if (current.name == "z00") valid = (current.left->op == NONE) + (current.right->op == NONE); // z00 is result of a 1/2 adder
            if (current.name == "z01") valid = (current.left->op == XOR || current.right->op == XOR) + (current.left->op == AND || current.right->op == AND); // Z00 carry is from a 1/2 adder
            if (valid == 1) { // One of the inputs is swapped
              if (current.left->op != XOR && current.left->op != OR) swaps.insert(current.left->name);
              if (current.right->op != XOR && current.right->op != OR) swaps.insert(current.right->name);
            } else if (valid == 0) { // We swapped the XOR gate output
              swaps.insert(current.name);
            }
          } else {
            int valid = (current.left->op == NONE) + (current.right->op == NONE);
            if (valid == 0) {
              cout << current.name << endl;
              cout << valid << endl;
              swaps.insert(current.name); // Swapped the XOR gate output
            } else if (valid == 1) { // Swapped an input
              if (current.left->op != NONE) swaps.insert(current.left->name);
              if (current.right->op != NONE) swaps.insert(current.right->name);
            }
          }
          break;
        case NONE:
            break;
      }
    }
  }
  return swaps;
}

int main() {
  map<string, node> nodes;
  vector<node> xNodes, yNodes;
  vector<node> outputNodes;
  // Get starting states
  while (!cin.eof()) {
    string temp;
    getline(cin, temp);
    if (temp == "") break;
    istringstream tempstream(temp);
    string identifier; int bit;
    getline(tempstream, identifier, ':');
    tempstream >> bit;
    nodes[identifier].name = identifier;
    nodes[identifier].value = bit;
    nodes[identifier].calculated = true;
    if (identifier[0] == 'x') {
      xNodes.push_back(nodes[identifier]);
    }
    if (identifier[0] == 'y') {
      yNodes.push_back(nodes[identifier]);
    }
  }
  
  // Get conditions
  while (!cin.eof()) {
    string temp;
    getline(cin, temp);
    string first, operand, second, identifier;
    istringstream tempstream(temp);
    tempstream >> first >> operand >> second >> temp >> identifier;
    nodes[identifier].name = identifier;
    nodes[identifier].left = &nodes[first];
    nodes[identifier].right = &nodes[second];
    nodes[first].name = first;
    nodes[second].name = second;
    if (operand == "AND") {
      nodes[identifier].op = AND;
    } else if (operand == "XOR") {
      nodes[identifier].op = XOR;
    } else {
      nodes[identifier].op = OR;
    }
    if (identifier[0] == 'z') { // Get the output nodes only
      outputNodes.push_back(nodes[identifier]);
    }
  }
  cout << "Incorrect Result (Part 1):" << endl;
  cout << getResults(outputNodes) << endl;
  cout << "Correct Result:" << getResults(xNodes) + getResults(yNodes) << endl;
  reverse(xNodes.begin(), xNodes.end());
  reverse(yNodes.begin(), yNodes.end());
  // vector<int> correctSum = getSum(xNodes, yNodes);
  set<string> swaps = getSwaps(outputNodes);
  for (string x : swaps) {
    cout << x << ',';
  }
  cout << endl;
  for (string x : swaps) {
    cout << "OP:";
    switch (nodes[x].op) {
      case NONE:
        cout << "None" << endl;
        break;
      case AND:
        cout << "And" << endl;
        break;
      case OR:
        cout << "Or" << endl;
        break;
      case XOR:
        cout << "Xor" << endl;
        break;
    }
    cout << "Name: ";
    cout << nodes[x].name << endl;
    if (nodes[x].op == NONE) continue;
    cout << "Left: ";
    cout << nodes[x].left->name << endl;
    cout << "Right: ";
    cout << nodes[x].right->name << endl;
  }
  return 0;
}
