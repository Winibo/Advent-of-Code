#include <bits/stdc++.h>

using namespace std;

int main() {
  int score = 0;
  int a,b,c,d;
  char temp;
  cin >> a >> temp >> b >> temp >> c >> temp >> d;
  while (!cin.eof()) {
    if ((a <= c && b >= d) ||(c <= a && d >= b)) score++;
    cin >> a >> temp >> b >> temp >> c >> temp >> d;
  }
  cout << score << endl;
  return 0;
}
