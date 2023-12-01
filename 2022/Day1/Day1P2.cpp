#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  int best = 0, second = 0, third = 0, current = 0;
  while (!cin.eof()) {
    getline(cin, input);
    cout << "Current input: " << input << endl;
    if (input == "") {
      if (current > best) {
        int temp = best;
        best = current;
        current = temp;
      }
      if (current > second) {
        int temp = second;
        second = current;
        current = temp;
      }
      if (current > third) {
        third = current;
      }
      current = 0;
      cout << "Best is: " << best << endl;
      cout << "Second is: " << second << endl;
      cout << "Third is: " << third << endl;
    } else {
        current += stoi(input);
    }
  }
  cout << best << endl;
  cout << best+second+third << endl;
  return 0;
}
