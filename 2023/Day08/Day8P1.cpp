#include "bits/stdc++.h"

using namespace std;

struct node {
    string name;
    string leftChild;
    string rightChild;
};

map<string, node> tree;

int main() {
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
    }
    int steps = 0;
    node currentNode = tree["AAA"];
    while (true) {
        for (char x : treePath) {
            // cout << "Current Node: " << currentNode.name << endl;
            if (currentNode.name == "ZZZ") {
                cout << steps << endl;
                return 0;
            }
            if (x == 'L') {
                currentNode = tree[currentNode.leftChild];
            } else {
                currentNode = tree[currentNode.rightChild];
            }
            steps++;
        }
    }
    //Unreachable
    return 0;
}