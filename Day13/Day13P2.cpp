#include <bits/stdc++.h>

using namespace std;

int parse(string first, string second, int startFirst, int startSecond) {
  int firstPos = startFirst;
  int secondPos = startSecond;
  while (first[firstPos] != ']' && second[secondPos] != ']') {
    if (first[firstPos] == ',') firstPos++;
    if (second[secondPos] == ',') secondPos++;
    // cout << "Reading characters: " << endl;
    // cout << first[firstPos] << endl;
    // cout << second[secondPos] << endl;
    //Check both digits
    if (isdigit(first[firstPos]) && isdigit(second[secondPos])) {
       // cout << "Both characters are digits, continuing" << endl;
      int firstDigit = 0;
      while (isdigit(first[firstPos])) {
        firstDigit = firstDigit*10 + first[firstPos] - '0';
        firstPos++;
      }
      // cout << "First number is: " << firstDigit << endl;
      int secondDigit = 0;
      while (isdigit(second[secondPos])) {
        secondDigit = secondDigit*10 + second[secondPos] - '0';
        secondPos++;
      }
      // cout << "Second number is: " << secondDigit << endl;
      if (firstDigit > secondDigit) return -1;
      if (firstDigit < secondDigit) return 1;
    }
    //Check both lists
    if (first[firstPos] == '[' && second[secondPos] == '[') {
      int result = parse(first, second, firstPos+1, secondPos+1);
      if (result != 0) return result;
      //Move pointers forward
      while (first[firstPos-1] != ']') firstPos++;
      while (second[secondPos-1] != ']') secondPos++;
    } else if (first[firstPos] == '[') { //Check left is list, right is int
      int digit = 0;
      while (isdigit(second[secondPos])) {
        digit = digit*10 + second[secondPos] - '0';
        secondPos++;
      }
      string created = "[" + to_string(digit) + "]";
      int result = parse(first, created, firstPos+1, 1);
      if (result != 0) return result;
      while (first[firstPos-1] != ']') firstPos++;
      //Move pointer forward
    } else if (second[secondPos] == '[') { //Check right is list, left is int
      int digit = 0;
      while (isdigit(first[firstPos])) {
        digit = digit*10 + first[firstPos] - '0';
        firstPos++;
      }
      string created = "[" + to_string(digit) + "]";
      int result = parse(created, second, 1, secondPos+1);
      if (result != 0) return result;
      //Move pointer forward
      while (second[secondPos-1] != ']') secondPos++;
    }
  }
  if (second[secondPos] == ']' && first[firstPos] == ']') return 0;
  if (second[secondPos] == ']') return -1;
  return 1;
}

bool parseWrapper(string first, string second) {
  int result = parse(first, second, 1, 1);
  if (result == 1) return true;
  return false;
}

int main() {
  string line;
  int sum = 1;
  int index = 1;
  vector<string> lists;
  while (getline(cin, line)) {
    if (line.length() > 0) {
      lists.push_back(line);
    }
  }
  lists.push_back("[[2]]");
  lists.push_back("[[6]]");
  sort(lists.begin(), lists.end(), parseWrapper);
  for (int i = 0; i < lists.size(); i++) {
    cout << lists[i] << endl;
    if (lists[i] == "[[2]]")  sum *= index;
    if (lists[i] == "[[6]]") sum *= index;
    index++;
  }
  cout << sum << endl;
  return 0;
}
