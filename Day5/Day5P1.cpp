#include <bits/stdc++.h>

using namespace std;

int main() {
  stack<char> a[9], b[9];
  string line;
  getline(cin, line);
  while (line.length() > 0) {
    cout << "Reading line:" << line << endl;
    for (int i = 0; i < line.length(); i++) {
      if ((i+3) % 4 == 0 && line[i] != ' ') {
        cout << "Pushing value: " << line[i] << " to stack " << i/4 << endl;
        b[i/4].push(line[i]);
        }
    }
    getline(cin, line);
  }
  cout << "Reversing" << endl;
  //reverse stacks
  for (int i = 0; i < 9; i++) {
    cout << "i is currently: " << i << endl;
    while (!b[i].empty()) {
      cout << "Swapping: " << b[i].top() << endl;
      a[i].push(b[i].top());
      b[i].pop();
    }
  }
  for (int i = 0; i < 9; i++) {
    if (!a[i].empty())
      cout << "Stack " << i << " has box " << a[i].top() << " on top." << endl;
  }
  cout << "Reading Changes" << endl;
  //Read changes
  string temp;
  int boxes, source, dest;
  cin >> temp >> boxes >> temp >> source >> temp >> dest;
  while (!cin.eof()) {
    cout << "Read: move " << boxes << " from " << source << " to " << dest << endl;
    for (int i = 0; i < boxes; i++) {
      if (!a[source-1].empty()) {
        a[dest-1].push(a[source-1].top());
        a[source-1].pop();
      }
    }
    cin >> temp >> boxes >> temp >> source >> temp >> dest;
  }
  cout << "Outputting" << endl;
  for (int i = 0; i < 9; i++) {
    if (!a[i].empty())
      cout << "Stack " << i << " has box " << a[i].top() << " on top." << endl;
  }
  return 0;
}
