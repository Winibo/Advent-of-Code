#include <bits/stdc++.h>

using namespace std;

struct reindeer {
    pair<int, int> position = {0, 0};
    int direction = 1; // N E S W = 0 1 2 3
    long long score = 0;
    
    bool operator <(const reindeer& rhs ) const {
        return score > rhs.score;
    }
};

vector<string> maze;

reindeer getNextPos(reindeer start) {
    switch (start.direction) {
        case 0:
            start.position.first -= 1;
            break;
        case 1:
            start.position.second += 1;
            break;
        case 2:
            start.position.first += 1;
            break;
        case 3:
            start.position.second -= 1;
            break;
    }
    start.score += 1;
    return start;
}

char dirConv(int x) {
    return x == 0 ? 'N' : x == 1 ? 'E' : x == 2 ? 'S' : 'W';
}

void debugPrint(reindeer r) {
    cout << "Position:" << r.position.first << ' ' << r.position.second << endl;
    cout << "Direction: " << dirConv(r.direction) << endl;
    cout << "Score: " << r.score << endl;
    cout << "Maze:" << endl;
    maze[r.position.first][r.position.second] = 'R';
    for (string x : maze) {
        cout << x << endl;
    }
    cout << endl;
    maze[r.position.first][r.position.second] = '.';
}

int search(reindeer start) {
    long long bestScore = 0;
    priority_queue<reindeer> searchQueue;
    searchQueue.push(start);
    map<pair<pair<int, int>, int>, bool> visited; 
    while (!searchQueue.empty()) {
        reindeer current = searchQueue.top(); searchQueue.pop();
        if (maze[current.position.first][current.position.second] == 'E') {
            return current.score;
        } else if (maze[current.position.first][current.position.second] == '#') {
            continue; //We can't actually get here, so skip everything
        }
        // debugPrint(current);
        // Search
        // Walk forward
        reindeer forward = getNextPos(current);
        if (!visited[make_pair(forward.position, forward.direction)]) {
            searchQueue.push(forward);
        }
        for (int i = 1; i < 4; i++) {
            // Rotate
            reindeer next = current;
            next.score += i != 2 ? 1000 : 2000;
            next.direction = (next.direction + i) % 4;
            if (!visited[make_pair(next.position, next.direction)]) {
                searchQueue.push(next);
            }
        }
        visited[make_pair(current.position, current.direction)] = true;
    }
    return -1;
}


int main()
{
    while (!cin.eof()) {
        string temp;
        getline(cin, temp);
        maze.push_back(temp);
    }
    // Find start
    reindeer start;
    for (int i = 0; i < maze.size(); i++) {
        bool found = false;
        for (int j = 0; j < maze[i].length(); j++) {
            if (maze[i][j] == 'S') {
                start.position = make_pair(i,j);
                found = true;
                break;
            }
        }
        if (found) break;
    }
    // Find the result
    cout << search(start) << endl;
    return 0;
}