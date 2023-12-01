#include <bits/stdc++.h>

using namespace std;

bool allUnique(string x) {
  for (int i = 0; i < x.length(); i++) {
    for (int j = i+1; j < x.length(); j++) {
      if (x[j] == x[i]) return false;
    }
  }
  return true;
}

int main() {
  string line, sot;
  getline(cin, line);
  cout << "The line is: " << line << endl;
  for (int i = 0; i < line.length(); i++) {
    cout << "Reading Character " << i << endl;
    cout << "That character is: " << line[i] << endl;
    cout << "sot is: " << sot << endl;
    sot = sot + line[i];
    if (sot.length() > 14) {
      sot = sot.substr(1, 15);
    }
    if (allUnique(sot) && i >=13) {
      cout << i+1 << endl;
      break;
    }
  }
  return 0;
}
