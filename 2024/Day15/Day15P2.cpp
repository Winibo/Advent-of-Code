#include <bits/stdc++.h>

using namespace std;

vector<string> maze;

string directions;

long long score_grid() {
    long long score = 0;
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[0].length(); j++) {
            if (maze[i][j] == '[') {
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

bool check_move(pair<int, int>& robot, int move) {
    pair<int, int> target = robot;
    if (maze[robot.first][robot.second] == '.') return true;
    if (maze[robot.first][robot.second] == '#') return false;
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
    if (maze[target.first][target.second] == '.' || (maze[target.first][target.second] != '#' && check_move(target, move))) {
        if (maze[robot.first][robot.second] != '@' && (directions[move] == '^' || directions[move] == 'v')) {
            pair<int, int> newRobot = target;
            maze[robot.first][robot.second] == ']' ? newRobot.second -= 1 : newRobot.second += 1;
            return true && check_move(newRobot, move);
        }
        return true;
    } else { // We would move into a wall :(
        return false;
    }
    return true; // We made a successful move, so all dependants can move :)
}

bool make_move(pair<int, int>& robot, int move) {
    if (maze[robot.first][robot.second] == '.') return true; // Don't move if we already have
    bool robotTile = false;
    if (maze[robot.first][robot.second] == '@') robotTile = true;
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
    if (robotTile || directions[move] == '<' || directions[move] == '>') { // Robot moves and horizontal moves are the same as before
        pair<int, int> sacTarget = target;
        if (maze[target.first][target.second] == '.' || (maze[target.first][target.second] != '#' && make_move(sacTarget, move))) {
            // Move
            maze[target.first][target.second] = maze[robot.first][robot.second]; // Update to new tile
            maze[robot.first][robot.second] = '.'; // Update previous tile to be clear
        } else { // We would move into a wall :(
            return false;
        }
        robot = target; // Update the reference for main
        return true; // We made a successful move, so all dependants can move :)
    } else { // We are dealing with a box moving vertically
        pair<int, int> firstTarget = target, secondTarget = target;
        maze[robot.first][robot.second] == ']' ? secondTarget.second -= 1 : secondTarget.second += 1;
        if (check_move(firstTarget, move) && check_move(secondTarget, move)) {
            // Move
            make_move(firstTarget, move);
            make_move(secondTarget, move);
            pair<int, int> secondRobot = robot;
            maze[robot.first][robot.second] == ']' ? secondRobot.second -= 1 : secondRobot.second += 1;
            maze[firstTarget.first][firstTarget.second] = maze[robot.first][robot.second];
            maze[secondTarget.first][secondTarget.second] = maze[secondRobot.first][secondRobot.second];
            maze[robot.first][robot.second] = '.';
            maze[secondRobot.first][secondRobot.second] = '.';
            return true;
        }
        return false;
    }
    return true;
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
    
    // Expand maze
    for (int i = 0; i < maze.size(); i++) {
        string newString = "";
        for (char y : maze[i]) {
            if (y == '#') newString += "##";
            if (y == '.') newString += "..";
            if (y == 'O') newString += "[]";
            if (y == '@') newString += "@.";
        }
        maze[i] = newString;
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
    cout << "Start:" << endl;
    print_grid();
    cout << endl;
    for (int i = 0; i < directions.length(); i++) {
        make_move(robot, i);
    }
    cout << score_grid() << endl;
    return 0;
}