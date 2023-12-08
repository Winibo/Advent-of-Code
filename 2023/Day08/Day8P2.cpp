#include "bits/stdc++.h"

using namespace std;

struct node {
    string name;
    string leftChild;
    string rightChild;
    long long loopLength = 0; //We always go back to start from Z
};

map<string, node> tree;

int main() {
    vector<node> startNodes;
    string treePath, temp;
    getline(cin, treePath);
    getline(cin, temp); //Blank line
    while (!cin.eof()) {
        string parent, leftChild, rightChild;
        char temp;
        cin >> parent >> temp >> temp >> leftChild >> rightChild;
        leftChild = leftChild.substr(0, leftChild.length()- 1);
        rightChild = rightChild.substr(0, rightChild.length() - 1);
        node p;
        p.leftChild = leftChild;
        p.rightChild = rightChild;
        p.name = parent;
        tree[parent] = p;
        if (parent[parent.length() - 1] == 'A') {
            startNodes.push_back(p);
        }
    }
    for (int i = 0; i < startNodes.size(); i++) {
        node x = startNodes[i];
        string firstZ = "";
        int steps = 0, index = 0;
        while (true) {
            steps++;
            node child;
            if (treePath[index] == 'L') {
                child = tree[x.leftChild];
            } else {
                child = tree[x.rightChild];
            }
            startNodes[i] = child;
            if (child.name[child.name.length() - 1] == 'Z') {
                tree[startNodes[i].name].loopLength = steps;
                break;
            }
            x = child;
            index = (index + 1) % treePath.length();
        }
    }
    long long lcmAnswer = 1;
    for (int i = 0; i < startNodes.size(); i++) {
        lcmAnswer = lcm(tree[startNodes[i].name].loopLength, lcmAnswer);
    }
    cout << lcmAnswer << endl;
    return 0;
}