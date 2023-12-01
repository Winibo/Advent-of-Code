#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  int best = 0, current = 0;
  while (!cin.eof()) {
    getline(cin, input);
    cout << "Current input: " << input << endl;
    if (input == "") {
      if (current > best) {
        best = current;
      }
      current = 0;
      cout << "Best is: " << best << endl;
    } else {
        current += stoi(input);
    }
  }
  cout << best << endl;
  return 0;
}
