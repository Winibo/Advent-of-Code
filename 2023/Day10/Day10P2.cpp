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
        if (start.x + x < 0 || start.y + y < 0 || start.x + x > maze[0].size() || start.y + y > maze.size())
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


void cleanupMaze() {
    for (int row = 0; row < maze.size(); row++) {
        for (int column = 0; column < maze.size(); column++) {
            if (!maze[row][column].valid) {
                maze[row][column].pipe ='.';
                maze[row][column].validxDir.clear();
                maze[row][column].validyDir.clear();
            } else {
                maze[row][column].visited = false;
            }
        }
    }
}

void solveS(node start) {
    if (maze[start.y + 1][start.x].pipe == '|' || maze[start.y + 1][start.x].pipe == 'L' || maze[start.y + 1][start.x].pipe == 'J') {
        //S is one of F,7,|
        if (maze[start.y - 1][start.x].pipe == '|' || maze[start.y - 1][start.x].pipe == 'F' || maze[start.y - 1][start.x] .pipe== '7') {
            maze[start.y][start.x].pipe = '|';
        } else if (maze[start.y][start.x + 1].pipe == '7' || maze[start.y][start.x + 1].pipe == 'J' || maze[start.y][start.x + 1].pipe == '-') {
            maze[start.y][start.x].pipe = 'F';
        } else {
            maze[start.y][start.x].pipe = '7';
        }
    } else if (maze[start.y - 1][start.x].pipe == '|' || maze[start.y - 1][start.x].pipe == 'F' || maze[start.y - 1][start.x].pipe == '7'){
        //S is one of L,J
        if (maze[start.y][start.x + 1].pipe == '7' || maze[start.y][start.x + 1].pipe == 'J' || maze[start.y][start.x + 1].pipe == '-') {
            maze[start.y][start.x].pipe = 'L';
        } else {
            maze[start.y][start.x].pipe = 'J';
        }
    } else {
        maze[start.y][start.x].pipe = '-';
    }
    maze[start.y][start.x].validxDir.clear();
    maze[start.y][start.x].validyDir.clear();
    maze[start.y][start.x] = setupDirection(maze[start.y][start.x]);
}

void floodFill(int row, int column, char colour) {   
    if (row < 0 || column < 0)
        return;
    if (row >= maze.size() || column >= maze[row].size())
        return;
    if (maze[row][column].pipe != '.')
        return;
    maze[row][column].pipe = colour;
    //Only flood fills .
    int xdir[] = {0,0,-1,1};
    int ydir[] = {-1,1,0,0};
    for (int i = 0; i < 4; i++) {
        if (row + ydir[i] < 0 || column + xdir[i] < 0 || row + ydir[i] >= maze.size() || column + xdir[i] >= maze[row].size())
            continue;
        floodFill(row + ydir[i], column + xdir[i], colour);
    }
}

void followPath(node start) {
    //Find which side is outside
    char dir = '.'; //Direction we CAME from: U,D,L,R
    int xOut, yOut;
    if (start.y - 1 < 0 || maze[start.y-1][start.x].pipe == 'O') {
        xOut = 0;
        yOut = -1; //Outside is above us
        if (start.pipe != 'F') {
            dir = 'L';
        }
    } else if (start.y + 1 >= maze.size() || maze[start.y+1][start.x].pipe == 'O') {
        xOut = 0;
        yOut = 1; //Outside is below us
        if (start.pipe != 'J') {
            dir = 'R';
        }
    } else if (start.x + 1 >= maze.size() || maze[start.y][start.x+1].pipe == 'O') {
        xOut = 1;
        yOut = 0; //Outside is to the right
        if (start.pipe != '7') {
            dir = 'D';
        }
    } else {
        xOut = -1;
        yOut = 0; //Outside is to the left
        if (start.pipe != 'F') {
            dir = 'U';
        }
    }
    node current = start;
    //Follow path
    while (!current.visited) {
        //Flood Fill
        floodFill(current.y + yOut, current.x + xOut, 'O');
        floodFill(current.y - yOut, current.x - xOut, 'I');
        maze[current.y][current.x].visited = true;
        if ((current.validxDir[0] == 1 && dir != 'R') || (current.validxDir[0] == -1 && dir != 'L') || (current.validyDir[0] == 1 && dir != 'D') || (current.validyDir[0] == -1 && dir != 'U')) {
            //Use first Direction
            if (current.validxDir[0] == 1) {
                //Going Right
                if (yOut == 0) {
                    int temp;
                    temp = yOut;
                    yOut = xOut;
                    xOut = temp;
                    if (dir == 'U')
                        yOut *= -1;
                }
                dir = 'L';
            } else if (current.validxDir[0] == -1) {
                //Going Left
                if (yOut == 0) {
                    int temp;
                    temp = yOut;
                    yOut = xOut;
                    xOut = temp;
                    if (dir == 'D')
                        yOut *= -1;
                }
                dir = 'R';
            } else if (current.validyDir[0] == 1) {
                //Going Down
                if (xOut == 0) {
                    int temp;
                    temp = yOut;
                    yOut = xOut;
                    xOut = temp;
                    if (dir == 'L')
                        xOut *= -1;
                }
                dir = 'U';
            } else {
                //Going Up
                if (xOut == 0) {
                    int temp;
                    temp = yOut;
                    yOut = xOut;
                    xOut = temp;
                    if (dir == 'R')
                        xOut *= -1;
                }
                dir = 'D';
            }
            //Flood Fill
            floodFill(current.y + yOut, current.x + xOut, 'O');
            floodFill(current.y - yOut, current.x - xOut, 'I');
            current = maze[current.y + current.validyDir[0]][current.x + current.validxDir[0]];
        } else {
            //Use second Direction
            if (current.validxDir[1] == 1) {
                //Going Right
                if (yOut == 0) {
                    int temp;
                    temp = yOut;
                    yOut = xOut;
                    xOut = temp;
                    if (dir == 'U')
                        yOut *= -1;
                }
                dir = 'L';
            } else if (current.validxDir[1] == -1) {
                //Going Left
                if (yOut == 0) {
                    int temp;
                    temp = yOut;
                    yOut = xOut;
                    xOut = temp;
                    if (dir == 'D')
                        yOut *= -1;
                }
                dir = 'R';
            } else if (current.validyDir[1] == 1) {
                //Going Down
                if (xOut == 0) {
                    int temp;
                    temp = yOut;
                    yOut = xOut;
                    xOut = temp;
                    if (dir == 'L')
                        xOut *= -1;
                }
                dir = 'U';
            } else {
                //Going Up
                if (xOut == 0) {
                    int temp;
                    temp = yOut;
                    yOut = xOut;
                    xOut = temp;
                    if (dir == 'R')
                        xOut *= -1;
                }
                dir = 'D';
            }
            //Flood Fill
            floodFill(current.y + yOut, current.x + xOut, 'O');
            floodFill(current.y - yOut, current.x - xOut, 'I');
            current = maze[current.y + current.validyDir[1]][current.x + current.validxDir[1]];
        }
    }
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

    cleanupMaze();
    solveS(startNode);
    floodFill(0,0,'O');
    //Find first Non O Space, Will be adjacent to an O
    node search;
    bool found = false;
    for (int row = 0; row < maze.size(); row++) {
        for (int column = 0; column < maze.size(); column++) {
            if (maze[row][column].pipe != 'O') {
                search = maze[row][column];
                found = true;
                break;
            }
        }
        if (found)
            break;
    }
    followPath(search);
    int answer = 0;
    for (auto x : maze) {
        for (auto y : x) {
            if (y.pipe == 'I')
                answer++;
        }
    }
    cout << answer << endl;
    return 0;
}