#include <bits/stdc++.h>

using namespace std;

int main() {
  int score = 0;
  string container;
  cin >> container;
  while (!cin.eof()) {
    string first;
    string second;
    cout << "Reading container: " << container << endl;
    int firsthalf = 0, secondhalf = container.length() - 1;
    while (firsthalf < secondhalf) {
      first = first + container[firsthalf];
      second = second + container[secondhalf];
      firsthalf++;
      secondhalf--;
    }
    cout << "Comparing:" << first << " and " << second << endl;
    size_t pos = -1;
    for (int i = 0; i < first.length(); i++) {
      pos = second.find(first[i]);
      if (pos != -1) break;
    }
    cout << "Found match:" << second[pos] << endl;
      if (second[pos] < '[') {
        score += second[pos] - 'A' + 27;
      } else score += second[pos] - 'a' + 1;
    cout << "Score is now:" << score << endl;
    cin >> container;
  }
  cout << score << endl;
  return 0;
}
