#include <bits/stdc++.h>

using namespace std;

const int ROWS = 1000;
const int COLUMNS = 2000;

const int STARTX = 500;
const int STARTY = 0;

string gridP1[ROWS];
string gridP2[ROWS];

bool simP1() {
  int xpos = STARTX;
  int ypos = STARTY;
  while (true) {
    // cout << "Current x: " << xpos << endl;
    // cout << "Current y: " << ypos << endl;
    if (xpos < 0 || xpos >= COLUMNS - 1) return false;
    if (ypos >= ROWS - 1) return false;
    if (gridP1[ypos+1][xpos] == '.') {
      ypos++;
    } else if (gridP1[ypos+1][xpos-1] == '.') {
      ypos++;
      xpos--;
    } else if (gridP1[ypos+1][xpos+1] == '.') {
      ypos++;
      xpos++;
    } else {
      gridP1[ypos][xpos] = 'o';
      return true;
    }
  }
  return false;
}

void simP2() {
  int xpos = STARTX;
  int ypos = STARTY;
  while (true) {
    if (gridP2[ypos+1][xpos] == '.') {
      ypos++;
    } else if (gridP2[ypos+1][xpos-1] == '.') {
      ypos++;
      xpos--;
    } else if (gridP2[ypos+1][xpos+1] == '.') {
      ypos++;
      xpos++;
    } else {
      gridP2[ypos][xpos] = 'o';
      return;
    }
  }
}

int main() {
  //Setup gridP1
  for (int i = 0; i < ROWS; i++) {
    string line(COLUMNS, '.');
    gridP1[i] = line;
  }
  string line;
  while (getline(cin, line)) {
    // cout << "Reading line: " << line << endl;
    line = line + ';';
    istringstream in(line);
    char skip;
    int currx, curry, endx, endy;
    in >> currx >> skip >> curry >> skip >> skip >> endx >> skip >> endy;
    while (!in.eof()) {
      // cout << " end x:" << endx << endl;
      // cout << " end y:" << endy << endl;
      while (currx != endx || curry != endy) {
        gridP1[curry][currx] = '#';
        // cout << "curr x:" << currx << endl;
        // cout << "curr y:" << curry << endl;
        if (currx < endx) currx++;
        if (currx > endx) currx--;
        if (curry < endy) curry++;
        if (curry > endy) curry--;
      }
      gridP1[curry][currx] = '#';
      in >> skip >> skip >> endx >> skip >> endy;
    }
  }
  for (int i = 0; i < ROWS; i++) {
    gridP2[i] = gridP1[i];
  }
  for (int i = ROWS-1; i >= 0; i--) {
    if (gridP1[i].find('#') != string::npos) {
      string floor(COLUMNS, '#');
      gridP2[i+2] = floor;
      // cout << "Floor at" << i+2 << endl;
      break;
    }
  }
  // for (int i = 0; i < 200; i++) {
  //   string line = gridP1[i].substr(450, 100);
  //   cout << line << endl;
  // }
  int answer = 0;
  while (simP1()) {
    answer++;
  }
  cout << answer << endl;
  // for (int i = 0; i < 200; i++) {
  //   string line = gridP1[i].substr(450, 100);
  //   cout << line << endl;
  // }
  answer = 0;
  // for (int i = 0; i < 200; i++) {
  //   string line = gridP2[i].substr(450, 100);
  //   cout << line << endl;
  // }
  while (gridP2[STARTY][STARTX] != 'o') {
    simP2();
    answer++;
    // if (answer % 10 == 0) cout << "Simulated " << answer << " Sand grains" << endl;
  }
  // for (int i = 0; i < 200; i++) {
  //   string line = gridP2[i].substr(300, 400);
  //   cout << line << endl;
  // }
  cout << answer << endl;
  return 0;
}
