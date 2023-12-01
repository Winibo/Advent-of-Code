#include <bits/stdc++.h>

using namespace std;

struct Node {
  ~Node()
  {
  for (auto p : children) {
    delete p;
    }
  }
  int size;
  string name;
  vector<Node*> children;
};

Node* read_tree(string name) {
  Node* self = new Node;
  self->name = name;
  string line;
  getline(cin, line);
  while (getline(cin, line) && line != "$ cd ..") {
    if (line[2] == 'c') { //cd into a file
      self->children.push_back(read_tree(line.substr(5,99999)));
    } else if (line[0] == 'd') { //Directory exists
    } else { // A file!
      int file_size = 0;
      for (int i = 0; i < line.length(); i++) {
        if (isdigit(line[i])) {
          file_size = file_size*10 + line[i] - '0';
        } else break;
      }
      self->size += file_size;
    }
  }
  return self;
}

int calc_size(Node* node) {
  for (Node* n : node->children) {
    node->size += calc_size(n);
  }
  return node->size;
}

int best = INT_MAX;
string bestName = "";

void get_best(Node* node, int needed) {
  if (node->size > needed && node->size < best) {
    best = node->size;
    bestName = node->name;
  }
  for (Node* c : node->children) {
    get_best(c, needed);
  }
}

const int maximum = 100000;

int getSmallSum(Node* node) {
  int sum = 0;
  if (node->size <= maximum) {
    sum += node->size;
  }
  for (Node* c : node->children) {
    sum += getSmallSum(c);
  }
  return sum;
}

const int total = 70000000;
const int totalNeeded = 30000000;

int main() {
  Node* root;
  root = read_tree("/");
  int fsize = calc_size(root);
  cout << "Filesystem Size: "<< fsize << endl;
  int day1 = getSmallSum(root);
  cout << "Sum of files < 100000 bytes: " << day1 << endl;
  int needed = totalNeeded - (total - fsize);
  cout << "Needed space: " << needed << endl;
  get_best(root, needed);
  cout << "Best: " << best << endl;
  cout << "Best name: " << bestName << endl;
  delete root;
  return 0;
}
