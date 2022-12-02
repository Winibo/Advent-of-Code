#include <bits/stdc++.h>

using namespace std;

int main() {
  char op, me;
  cin >> op >> me;
  int score = 0;
  while (!cin.eof()) {
    if (op == 'A') {
      if (me == 'X') score += 4;
      if (me == 'Y') score += 8;
      if (me == 'Z') score += 3;
    }
    if (op == 'B') {
      if (me == 'X') score += 1;
      if (me == 'Y') score += 5;
      if (me == 'Z') score += 9;
    }
    if (op == 'C') {
      if (me == 'X') score += 7;
      if (me == 'Y') score += 2;
      if (me == 'Z') score += 6;
    }
    cin >> op >> me;
  }
  cout << score << endl;
  return 0;
}
