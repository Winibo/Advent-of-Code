#include <bits/stdc++.h>

using namespace std;

const int TESTROW = 2000000;
// const int TESTROW = 10;

const int ROWMAX = 4000000;
// const int ROWMAX = 20;

vector<pair<int, int>> beacons;
vector<pair<int, int>> sensors;

int main() {
  string line;
  while (getline(cin, line)) {
    istringstream in(line);
    cout << "Reading line: " << line << endl;
    string skip;
    char sk;
    int currx, curry;
    int beacx, beacy;
    in >> skip >> skip >> sk >> sk >> currx;
    in >> skip >> sk >> sk >> curry;
    in >> skip >> skip >> skip;
    in >> skip >> skip >> sk >> sk >> beacx;
    in >> skip >> sk >> sk >> beacy;


    sensors.push_back(make_pair(currx, curry));
    beacons.push_back(make_pair(beacx, beacy));
  }
  //Part 1
  int answer = 0;
  vector<pair<int, int>> ranges;
  for (int i = 0; i < sensors.size(); i++) {
    pair<int, int> sensor = sensors[i];
    pair<int, int> beacon = beacons[i];
    // cout << "Sensor at: " << sensor.first << ',' << sensor.second << endl;
    // cout << "Beacon at: " << beacon.first << ',' << beacon.second << endl;
    int taxi = abs(sensor.first - beacon.first) + abs(sensor.second - beacon.second);
    // cout << "Taxi dist: " << taxi << endl;
    int diff = abs(sensor.second - TESTROW);
    if (taxi - diff > 0) {
      pair<int, int> nextRange(sensor.first-(taxi - diff), sensor.first+ (taxi - diff));
      //Add to list of ranges
      for (auto itr = ranges.begin(); itr != ranges.end(); itr++) {
        if (((nextRange.second >= itr->first && itr->first >= nextRange.first) ||
         (itr->second >= nextRange.first && nextRange.first >= itr->first))) {
           nextRange.first = min(nextRange.first, itr->first);
           nextRange.second = max(nextRange.second, itr->second);
           itr = ranges.erase(itr);
           itr--;
        }
      }
      ranges.push_back(nextRange);
      // cout << "Adding range: " << nextRange.first << ',' << nextRange.second << endl;
    }
  }
  //Add ranges
  for (pair<int, int> range : ranges) {
    cout << "Range: " << range.first << ',' << range.second << endl;
    answer += range.second - range.first;
  }
  //Sub out miscounted beacons
  for (pair<int, int> beacon : beacons) {
    if (beacon.second != TESTROW) continue;
    for (pair<int, int> range : ranges) {
      if (beacon.first > range.first && beacon.first < range.first) answer--;
    }
  }
  cout << answer << endl;
  //Part 2
  for (int i = 0; i < ROWMAX+1; i++) {
    ranges.clear();
    // cout << "Checking row: " << i << endl;
    for (int j = 0; j < sensors.size(); j++) {
      pair<int, int> sensor = sensors[j];
      pair<int, int> beacon = beacons[j];
      // cout << "Sensor at: " << sensor.first << ',' << sensor.second << endl;
      // cout << "Beacon at: " << beacon.first << ',' << beacon.second << endl;
      int taxi = abs(sensor.first - beacon.first) + abs(sensor.second - beacon.second);
      // cout << "Taxi dist: " << taxi << endl;
      int diff = abs(sensor.second - i);
      // cout << "Diff is: " << taxi - diff << endl;
      if (taxi - diff > 0) {
        pair<int, int> nextRange(sensor.first-(taxi - diff), sensor.first+ (taxi - diff));
        for (auto itr = ranges.begin(); itr != ranges.end(); itr++) {
          if (((nextRange.second >= itr->first && itr->first >= nextRange.first) ||
           (itr->second >= nextRange.first && nextRange.first >= itr->first))) {
             nextRange.first = min(nextRange.first, itr->first);
             nextRange.second = max(nextRange.second, itr->second);
             itr = ranges.erase(itr);
             itr--;
          }
        }
        ranges.push_back(nextRange);
      }
    }
    //Check ranges for 0-max
    for (pair<int, int> range : ranges) {
      // cout << "Range: " << range.first << '-' << range.second << endl;
      //If we find left half of discontinuity first
      if (range.first <= 0 && range.second >= 0 && range.second < ROWMAX) {
        cout << range.second+1 << ',' << i << endl;
        return 0;
      }
      //If we find right half of discontinuity first
      if (range.first > 0 && range.first < ROWMAX && range.second >= ROWMAX) {
        cout << range.first-1 << ',' << i << endl;
        return 0;
      }
      //We found the clone we're looking for in the row
      if (range.first <= 0 && range.second >= ROWMAX) break;
    }
  }
  cout << "Something broke?" << endl;
  return 0;
}
