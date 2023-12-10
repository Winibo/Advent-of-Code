#include "bits/stdc++.h"

using namespace std;

struct node {
    int x;
    int y;
    vector<int> validxDir, validyDir;
    char pipe;
    bool visited = false;
    bool valid = false;
};

vector<vector<node>> maze;

node setupDirection(node x) {
    switch (x.pipe) {
        case '|':
            x.validxDir.push_back(0);
            x.validyDir.push_back(1);
            x.validxDir.push_back(0);
            x.validyDir.push_back(-1);
            break;
        case '-':
            x.validxDir.push_back(1);
            x.validyDir.push_back(0);
            x.validxDir.push_back(-1);
            x.validyDir.push_back(0);
            break;
        case 'L':
            x.validxDir.push_back(0);
            x.validyDir.push_back(-1);
            x.validxDir.push_back(1);
            x.validyDir.push_back(0);
            break;
        case 'J':
            x.validxDir.push_back(0);
            x.validyDir.push_back(-1);
            x.validxDir.push_back(-1);
            x.validyDir.push_back(0);
            break;
        case '7':
            x.validxDir.push_back(-1);
            x.validyDir.push_back(0);
            x.validxDir.push_back(0);
            x.validyDir.push_back(1);
            break;
        case 'F':
            x.validxDir.push_back(1);
            x.validyDir.push_back(0);
            x.validxDir.push_back(0);
            x.validyDir.push_back(1);
            break;
        case '.':
            break;
        case 'S':
            x.validxDir.push_back(0); //Up/Down
            x.validyDir.push_back(1);
            x.validxDir.push_back(0);
            x.validyDir.push_back(-1);
            x.validxDir.push_back(1); //Left/Right
            x.validyDir.push_back(0);
            x.validxDir.push_back(-1);
            x.validyDir.push_back(0);
            break;
    }
    return x;
}

int dfs(node start, int xdir = 0, int ydir = 0) {
    
    if (start.pipe != 'S' && (find(start.validxDir.begin(), start.validxDir.end(), -xdir) == start.validxDir.end() || find(start.validyDir.begin(), start.validyDir.end(), -ydir) == start.validyDir.end()))
        return -1; //We need to be able to get back to where we started
    if (start.visited == true) {
        return start.pipe == 'S' ? 0 : -1;
    }
    maze[start.y][start.x].visited = true;
    for (int i = 0; i < start.validxDir.size(); i++) {
        int x = start.validxDir[i], y = start.validyDir[i];
        if ((x != 0 && -x == xdir) || (y != 0 && -y == ydir))
            continue; //Don't go forward->back->forward->back->forward...
        if (start.x + x < 0 || start.y + y < 0 || start.x + x > maze.size() || start.y + y > maze.size())
            continue; //No invalid indices
        node next = maze[start.y + y][start.x + x];
        int value = dfs(next, x, y);
        if (value != -1) {
            maze[start.y][start.x].valid = true;
            maze[start.y][start.x].visited = false;
            return value + 1;
        }
    }
    maze[start.y][start.x].visited = true;
    cout << "Returning having not found the answer" << endl;
    return -1;
}

int main() {
    int yStart = 0;
    node startNode;
    while (!cin.eof()) {
        int xStart = 0;
        vector<node> temp;
        string next = "";
        getline(cin, next);
        if (next == "") 
            break;
        for (char x : next) {
            node nextNode;
            nextNode.x = xStart++;
            nextNode.y = yStart;
            nextNode.pipe = x;
            nextNode = setupDirection(nextNode);
            if (x == 'S') {
                nextNode.valid = true;
                startNode = nextNode;
            }
            temp.push_back(nextNode);
        }
        maze.push_back(temp);
        yStart++;
    }

    int pipeLength = dfs(startNode);
    cout << pipeLength / 2 << endl;
    return 0;
}