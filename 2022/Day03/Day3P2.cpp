#include <bits/stdc++.h>

using namespace std;

int main() {
  string container1, container2, container3;
  cin >> container1 >> container2 >> container3;
  int score = 0;
  while (!cin.eof()) {
    cout << "Reading next set" << endl;
    cout << "Container 1 is:" << container1 << endl;
    cout << "Container 2 is:" << container2 << endl;
    cout << "Container 3 is:" << container3 << endl;
    int pos = 0;
    // for (int i = 0; i < container1.length(); i++) {
    //   //cout << "Checking for:" << container1[i] << endl;
    //   pos = container2.find(container1[i]);
    //   int pos2 = container3.find(container3[i]);
    //   if (pos != -1 && pos2 != -1) break;
    // }
    string intersection;
    string answer;
    sort(container1.begin(), container1.end());
    sort(container2.begin(), container2.end());
    sort(container3.begin(), container3.end());
    set_intersection(container1.begin(), container1.end(), container2.begin(), container2.end(), back_inserter(intersection));
    cout << "Intersection of 1 and 2" << intersection << endl;
    set_intersection(container3.begin(), container3.end(), intersection.begin(), intersection.end(), back_inserter(answer));
    cout << "Found match:" << answer << endl;
      if (answer[0] < '[') {
        score += answer[0] - 'A' + 27;
      } else score += answer[0] - 'a' + 1;
    cout << "Score is now:" << score << endl;
    cin >> container1 >> container2 >> container3;
  }
  cout << score << endl;
  return 0;
}
