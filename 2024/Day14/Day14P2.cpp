#include <bits/stdc++.h>

using namespace std;

struct robot {
    pair<long long, long long> position;
    pair<long long, long long> velocity;
};

long long width = 101;
long long height = 103;


vector<robot> robots;

void simulateRobot(int index) {
    robot r = robots[index];
    for (int i = 0; i < 1; i++) {
        r.position.first += r.velocity.first;
        r.position.second += r.velocity.second;
        if (r.position.first < 0) r.position.first += width;
        if (r.position.second < 0) r.position.second += height;
        if (r.position.first > width - 1) r.position.first %= width;
        if (r.position.second > height - 1) r.position.second %= height;
    }
    robots[index] = r;
}

long long getQuadrant(int quadrant) {
    long long minX, maxX, minY, maxY;
    switch (quadrant) {
        case 0:
            minX = 0; maxX = width / 2; minY = 0; maxY = height / 2;
            break;
        case 1:
            minX = (width / 2) + 1; maxX = width + 1; minY = 0; maxY = height / 2;
            break;
        case 2:
            minX = 0; maxX = width / 2; minY = (height / 2) + 1; maxY = height;
            break;
        case 3:
            minX = (width / 2) + 1; maxX = width + 1; minY = (height / 2) + 1; maxY = height;
            break;
    }
    long long result = 0;
    for (robot x : robots) {
        if (x.position.first >= minX && x.position.first < maxX && x.position.second >= minY && x.position.second < maxY) result++;
    }
    return result;
}

bool printGrid(int step) {
  vector<string> data;
  for (int i = 0; i < height; i++) {
      data.push_back("");
      for (int j = 0;j < height; j++) {
          data[i] += ".";
      }
  }
  for (robot x : robots) {
      data[x.position.second][x.position.first] = 'R';
  }
  int best = 0;
  for (string x : data) {
    int counter = 0;
      for (char y : x) {
        if (y == 'R') {
          counter++;
        } else {
          if (counter > best) {
            best = counter;
          }
          counter = 0;
        }
      }
  }
  if (best >= width / 4) {
    cout << step << endl;
    for (string x : data) {
      cout << x << endl;
    }
    return true;
    }
  return false;
}

int main()
{
    while (!cin.eof()) {
        robot temp; char ctemp;
        cin >> ctemp >> ctemp >> temp.position.first >> ctemp >> temp.position.second;
        cin >> ctemp >> ctemp >> temp.velocity.first >> ctemp >> temp.velocity.second;
        robots.push_back(temp);
    }
    long long step = 0;
    bool found = false;
    while (!found) {
        for (int i = 0; i < robots.size(); i++) {
            simulateRobot(i);
        }
        step++;
        if (step % 10000 == 0) cout << "Step:" << step << endl;
        found = printGrid(step);
    }
    return 0;
}
