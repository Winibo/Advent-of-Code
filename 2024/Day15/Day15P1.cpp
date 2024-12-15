#include <bits/stdc++.h>

using namespace std;

vector<string> maze;

string directions;

bool make_move(pair<int, int>& robot, int move) {
    pair<int, int> target = robot;
    // Make move
    switch(directions[move]) {
        case '<':
            target.second -= 1;
            break;
        case '>':
            target.second += 1;
            break;
        case '^':
            target.first -= 1;
            break;
        case 'v':
            target.first += 1;
            break;
    }
    // The maze is surrounded by walls, so this can't be oob
    // Move if we can move into the space, or the moves of some crate pushes all succeeds
    pair<int, int> sacTarget = target;
    if (maze[target.first][target.second] == '.' || (maze[target.first][target.second] == 'O' && make_move(sacTarget, move))) {
        // Move
        maze[target.first][target.second] = maze[robot.first][robot.second]; // Update to new tile
        maze[robot.first][robot.second] = '.'; // Update previous tile to be clear
    } else { // We would move into a wall :(
        return false;
    }
    robot = target; // Update the reference for main() (sactarget is updated otherwise)
    return true; // We made a successful move, so all dependants can move :)
}

long long score_grid() {
    long long score = 0;
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[0].length(); j++) {
            if (maze[i][j] == 'O') {
                score += (i*100) + j;
            }
        }
    }
    return score;
}

void print_grid() {
    for (string x : maze) {
        cout << x << endl;
    }
}

int main()
{
    while (true) {
        string temp;
        getline(cin, temp);
        if (temp == "") break; //Split between this and the directions
        maze.push_back(temp);
    }
    while (!cin.eof()) {
        string temp;
        getline(cin, temp);
        directions = directions + temp;
    }

    // Find robot
    pair<int, int> robot;
    for (int i = 0; i < maze.size(); i++) {
        bool found = false;
        for (int j = 0; j < maze[0].length(); j++) {
            if (maze[i][j] == '@') {
                robot = make_pair(i, j);
                found = true;
                break;
            }
        }
        if (found) break;
    }
    // Simulate moves
    // I know I probably need to do cycle checking later, but for now this is fine
    for (int i = 0; i < directions.length(); i++) {
        make_move(robot, i);
    }
    cout << score_grid() << endl;
    return 0;
}