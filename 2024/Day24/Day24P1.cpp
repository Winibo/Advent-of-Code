#include <bits/stdc++.h>

using namespace std;

enum operation {
  AND,
  OR,
  XOR
};

struct node {
  string name;
  long long value;
  bool calculated = false;
  operation op;
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
  };
  return x.value;
}

bool sortNode(node a, node b) {
  return a.name > b.name;
}

long long getResults(vector<node> nodes) {
  long long result = 0;
  sort(nodes.begin(), nodes.end(), sortNode);
  for (node val : nodes) {
    result = (result << 1) + evaluateNode(val);
  }
  return result;
}

int main() {
  map<string, node> nodes;
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
    nodes[identifier].value = bit;
    nodes[identifier].calculated = true;
    if (identifier[0] == 'z') {
      outputNodes.push_back(nodes[identifier]);
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

  cout << getResults(outputNodes) << endl;
  return 0;
}
