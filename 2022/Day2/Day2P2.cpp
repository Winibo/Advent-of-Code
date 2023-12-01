#include <bits/stdc++.h>

using namespace std;

int main() {
  char op, me;
  cin >> op >> me;
  int score = 0;
  while (!cin.eof()) {
    if (op == 'A') {
      if (me == 'X') score += 3;
      if (me == 'Y') score += 4;
      if (me == 'Z') score += 8;
    }
    if (op == 'B') {
      if (me == 'X') score += 1;
      if (me == 'Y') score += 5;
      if (me == 'Z') score += 9;
    }
    if (op == 'C') {
      if (me == 'X') score += 2;
      if (me == 'Y') score += 6;
      if (me == 'Z') score += 7;
    }
    cin >> op >> me;
  }
  cout << score << endl;
  return 0;
}
