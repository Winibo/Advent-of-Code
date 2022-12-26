#include <bits/stdc++.h>

using namespace std;

vector<pair<long long, long long>> file;

int main() {
  long long input, count = 0;
  cin >> input;
  while (!cin.eof()) {
    file.push_back(make_pair(input, count));
    count++;
    cin >> input;
  }
  for (long long i = 0; i < file.size(); i++) {
    // for (long long i : file) {
    //   cout << i << ' ';
    // }
    // cout << endl;
    long long pos = 0, element = 0;
    //Find the position of the element to shift
    //Can't use find, need the index for math stuff, not an iterator
    for (long long j = 0; j < file.size(); j++) {
      if (file[j].second == i) {
        pos = j;
        element = file[j].first;
        break;
      }
    }
    if (element > 0) {
      for (long long i = 0; i < element; i++) {
        pair<long long, long long> temp = file[(pos+i) % file.size()];
        file[(pos+i) % file.size()] = file[(pos+i+1) % file.size()];
        file[(pos+i+1) % file.size()] = temp;
      }
    } else if (element < 0) {
      for (long long i = 0; i > element; i--) {
        pair<long long, long long> temp;
        long long ind1, ind2;
        ind1 = pos+i;
        ind2 = pos+i-1;
        while (ind1 < 0) ind1 += file.size();
        while (ind2 < 0) ind2 += file.size();
        temp = file[ind1];
        file[ind1] = file[ind2];
        file[ind2] = temp;
      }
    }
  }
  // for (long long i : file) {
  //   cout << i << ' ';
  // }
  // cout << endl;
  //Find element
  long long pos = 0, sum = 0;
  for (long long j = 0; j < file.size(); j++) {
    if (file[j].first == 0) {
      pos = j;
    }
  }
  //Get answer
  for (long long j = 0; j < 3; j++) {
    for (long long i = 0; i < 1000; i++) {
      pos = (pos+1) % file.size();
    }
    cout << file[pos].first << endl;
    sum += file[pos].first;
  }
  cout << sum << endl;
  return 0;
}
