#include <bits/stdc++.h>

using namespace std;

enum direction {
    up = 0,
    right = 1,
    down = 2,
    left = 3,
};

struct position {
    direction heading;
    int x;
    int y;
};

pair<bool, position> take_step(vector<string>& map, position& p) {
    int nextX = p.x, nextY = p.y;
    switch (p.heading) {
        case direction::up:
            nextY = p.y - 1;
            break;
        case direction::right:
            nextX = p.x + 1;
            break;
        case direction::down:
            nextY = p.y + 1;
            break;
        case direction::left:
            nextX = p.x - 1;
            break;
    }
    if (nextX < 0 || nextX >= map[0].length() || nextY < 0 || nextY >= map.size()) {
        return make_pair(false, p);
    }
    if (map[nextY][nextX] == '#') {
        p.heading = static_cast<direction>((p.heading + 1) % 4); 
    } else {
        p.x = nextX;
        p.y = nextY;
    }
    
    return make_pair(true, p);
}

bool check_loop(vector<string> map, position p, std::map<tuple<int, int, direction>, bool> visited) {
    pair<bool, position> guard = make_pair(true, p);
    while (guard.first) {
        guard = take_step(map, guard.second);
        if (visited[make_tuple(guard.second.x,guard.second.y,guard.second.heading)] && guard.first) {
            return true;
        }
        visited[make_tuple(guard.second.x,guard.second.y,guard.second.heading)] = true;
    }
    return false;
}

int main()
{
    vector<string> map;
    while (!cin.eof()) {
        string input = "";
        getline(cin, input);
        if (input == "\n") {
            break;
        }
        map.push_back(input);
    }
    int y = 0, x = 0;
    while (y < map.size()) {
        x = map[y].find('^');
        if (x != string::npos) break;
        y++;
    }
    pair<bool, position> guard;
    guard.first = true;
    guard.second.heading = direction::up;
    guard.second.x = x;
    guard.second.y = y;
    std::map<tuple<int, int, direction>, bool> visited;
    std::map<pair<int, int>, bool> seen;
    visited[make_tuple(x,y,direction::up)] = true;
    long long validObstacles = 0;
    while (guard.first) {
        position previous = guard.second;
        guard = take_step(map, guard.second);
        vector<string> mapCopy(map);
        mapCopy[guard.second.y][guard.second.x] = '#';
        if (!seen[make_pair(guard.second.x,guard.second.y)] && check_loop(mapCopy,previous,visited)) validObstacles++;
        visited[make_tuple(guard.second.x,guard.second.y,guard.second.heading)] = true;
        seen[make_pair(guard.second.x, guard.second.y)] = true;
    }
    cout << "Done Walk" << endl;
    cout << validObstacles << endl;
    return 0;
}