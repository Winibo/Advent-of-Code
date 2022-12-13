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


int main() {
  string line;
  int sum = 0;
  int index = 1;
  while (getline(cin, line)) {
    string firstList = line;
    getline(cin, line);
    string secondList = line;
    // cout << "Reading lists: " << endl;
    // cout << firstList << endl;
    // cout << secondList << endl;
    int result = parse(firstList, secondList, 1, 1);
    cout << "Result was: " << result << endl;
    if (result == 1) sum += index;
    index++;
    getline(cin, line);
  }
  cout << sum << endl;
  return 0;
}
