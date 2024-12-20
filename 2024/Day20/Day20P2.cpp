#include <bits/stdc++.h>

using namespace std;

vector<string> maze;

struct position {
    pair<int, int> location;
    int score;
    bool operator <(const position& rhs ) const {
        return score > rhs.score; // Yeah, yeah, this is 'wrong'
    }
};

vector<position> getNextPositions(position start) {
    vector<position> next;
    start.score += 1;
    for (int i = 0; i < 4; i++) {
        position nextPos = start;
        switch (i) {
            case 0:
                nextPos.location.first += 1;
                break;
            case 1:
                nextPos.location.first -= 1;
                break;
            case 2:
                nextPos.location.second += 1;
                break;
            case 3:
                nextPos.location.second -= 1;
                break;
            default:
                break;
        }
        next.push_back(nextPos);
    }
    return next;
}

vector<vector<int>> getScores(position start) {
    vector<vector<int>> scores(maze.size(), vector<int>(maze[0].length(), -1));
    priority_queue<position> positions;
    positions.push(start);
    while (!positions.empty()) {
        position current = positions.top(); positions.pop();
        if (scores[current.location.first][current.location.second] != -1)
            continue;
        if (maze[current.location.first][current.location.second] == '#')
            continue;
        vector<position> nextPositions = getNextPositions(current);
        for (position x : nextPositions) {
            positions.push(x);
        }
        scores[current.location.first][current.location.second] = current.score;
    }
    return scores;
}

vector<pair<pair<int, int>, int>> getCheats(pair<int, int> start) {
    vector<pair<pair<int, int>, int>> cheats;
    for (int distance = 1; distance <= 20; distance++) {
        for (int i = 0; i <= distance; i++) {
            pair<int, int> a = make_pair(start.first + i, start.second + (distance - i));
            pair<int, int> b = make_pair(start.first - i, start.second + (distance - i));
            pair<int, int> c = make_pair(start.first + i, start.second - (distance - i));
            pair<int, int> d = make_pair(start.first - i, start.second - (distance - i));
            cheats.push_back(make_pair(a, distance));
            if (i != 0 && (i != distance && distance != 1)) {
                cheats.push_back(make_pair(b, distance));
                cheats.push_back(make_pair(c, distance));
            }
            cheats.push_back(make_pair(d, distance));
        }
    }
    return cheats; // List of all possible locations 20 or less tiles away
}

long long getCheatCount(vector<vector<int>> grid) {
    long long result = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == -1) continue;
            // Get nextPos
            vector<pair<pair<int, int>, int>> cheats = getCheats(make_pair(i, j));
            for (pair<pair<int, int>, int> x : cheats) {
                pair<int, int> nextPos = x.first;
                if (nextPos.first < 0 || nextPos.first >= grid.size())
                    continue;
                if (nextPos.second < 0 || nextPos.second >= grid[i].size())
                    continue;
                if (grid[nextPos.first][nextPos.second] == -1)
                    continue; // Can't cheat into a wall
                if (grid[nextPos.first][nextPos.second] - (grid[i][j] + x.second) >= 100) {
                    result += 1;
                }
            }
        }
    }
    return result;
}

int main()
{
    while (!cin.eof()) {
        string temp;
        getline(cin, temp);
        maze.push_back(temp);
    }
    
    // Find Start and End
    position start, end;
    start.score = 0;
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].length(); j++) {
            if (maze[i][j] == 'S')
                start.location = make_pair(i, j);
            if (maze[i][j] == 'E')
                end.location = make_pair(i, j);
        }
    }
    
    vector<vector<int>> scores = getScores(start);
    end.score = scores[end.location.first][end.location.second];
    cout << "End Score: " << end.score << endl;
    cout << getCheatCount(scores) << endl;
    return 0;
}