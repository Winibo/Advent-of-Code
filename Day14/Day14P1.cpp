#include <bits/stdc++.h>

using namespace std;

struct tile {
  int x;
  int y;
};

vector<tile> spaces;

int sim(int minx, int maxx, int maxy) {
  int simNum = 0;
  int simx = 500;
  int simy = 0;
  while (simx >= minx && simx <= maxx && simy <= maxy) {
    bool blockeddown = false;
    bool blockedleft = false;
    bool blockedright = false;
    for (tile t : spaces) {
      if (t.y == simy+1 && t.x == simx)
        blockeddown = true;
      if (t.y == simy+1 && t.x == simx - 1)
        blockedleft = true;
      if (t.y == simy+1 && t.x == simx + 1)
        blockedright = true;
    }
    if (!blockeddown) {
      simy++;
      continue;
    }
    if (!blockedleft) {
      simy++;
      simx--;
      continue;
    }
    if (!blockedright) {
      simy++;
      simx++;
      continue;
    }
    //We are blocked
    tile sand;
    sand.x = simx;
    sand.y = simy;
    spaces.push_back(sand);
    simx = 500;
    simy = 0;
    simNum++;
  }
  return simNum;
}

int main() {
  int minimumx = INT_MAX;
  int maximumx = 0;
  int maximumy = 0;
  string line;
  while (getline(cin, line)) {
    //Read input
    line = line + ';';
    istringstream in(line);
    char skip;
    int currx, curry, endx, endy;
    in >> currx >> skip >> curry >> skip >> skip >> endx >> skip >> endy;
    if (currx < minimumx) minimumx = currx;
    if (endx < minimumx) minimumx = endx;
    if (currx > maximumx) maximumx = currx;
    if (endx > maximumx) maximumx = endx;
    if (curry > maximumy) maximumy = curry;
    if (endy > maximumy) maximumy = endy;
    tile fix;
    fix.x = currx;
    fix.y = curry;
    spaces.push_back(fix);
    while (!in.eof()) {
      cout << "Current x is: " << currx << endl;
      cout << "Current y is: " << curry << endl;
      cout << "End x is: " << endx << endl;
      cout << "End y is: " << endy << endl;
      while (currx != endx || curry != endy) {
        if (currx < endx) currx++;
        if (currx > endx) currx--;
        if (curry < endy) curry++;
        if (curry > endy) curry--;
        tile filled;
        filled.x = currx;
        filled.y = curry;
        spaces.push_back(filled);
      }
      in >> skip >> skip >> endx >> skip >> endy;
      if (endx < minimumx) minimumx = endx;
      if (endx > maximumx) maximumx = endx;
      if (endy > maximumy) maximumy = endy;
    }
  }
  cout << "Min x: " << minimumx << endl;
  cout << "Max x: " << maximumx << endl;
  cout << "Max y: " << maximumy << endl;
  cout << sim(minimumx, maximumx, maximumy) << endl;
  return 0;
}
