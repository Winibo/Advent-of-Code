#include <bits/stdc++.h>

using namespace std;

vector<pair<long long, long long>> file;

struct Node {
  long long value;
  int originalPos;
  Node* prev;
  Node* next;
};

const long long DECRYPT = 811589153;

int main() {
  long long input, count = 0;
  cin >> input;
  Node* start = new Node();
  Node* current;
  Node* previous = NULL;
  Node* zero;
  cout << "Reading input" << endl;
  while (!cin.eof()) {
    // cout << "Reading element " << input << endl;
    if (count == 0) current = start;
    else current = new Node();
    // cout << "Setting values" << endl;
    current->value = input*DECRYPT;
    if (current->value == 0) zero = current;
    // cout << "Setting originalPos" << endl;
    current->originalPos = count;
    // cout << "Setting previous" << endl;
    if (count != 0) current->prev = previous;
    else current->prev = NULL;
    // cout << "Setting next" << endl;
    if (previous != NULL)
      previous->next = current;
    previous = current;
    count++;
    // cout << "Reading next input" << endl;
    cin >> input;
  }
  current->next = start;
  start->prev = current;
  cout << "Read input" << endl;
  cout << "Count was: " << count << endl;
  current = zero;
  // cout << current->value << ' ';
  // current = current->next;
  // while (current->value != 0) {
  //   cout << current->value << ' ';
  //   current = current->next;
  // }
  cout << endl;
  for (int k = 0; k < 10; k++) {
    cout << "Doing iteration: " << k << endl;
    for (long long i = 0; i < count; i++) {
      // cout << "Moving element " << i << ',';
      long long pos = 0, element = 0;
      //Find the position of the element to shift
      Node* next = start;
      while (next->originalPos != i) {
        next = next->next;
        pos++;
      }
      element = next->value;
      // cout << element << endl;
      //Update neighbor connections
      if (element != 0) {
        next->prev->next = next->next;
        next->next->prev = next->prev;
      }
      Node* moving = next;
      if (element > 0) {
        while (element >= count) {
          long long off = element / count;
          element = element % count;
          element += off;
        }
        if (pos + element > count) {
          element = 1 + element - count;
        }
      } else if (element < 0) {
        while (abs(element) >= count) {
          long long off = abs(element) / count;
          element = -(abs(element) % count);
          element -= off;
        }
        if (pos + element < 0) {
          element = count + element - 1;
        }
      }
      // cout << "Moving element " << element << " Spaces " << endl;
      if (element > 0) {
        for (long long i = 0; i < element; i++) {
          next = next->next;
        }
      } else if (element < 0){
        for (long long i = 0; i >= element; i--) {
          next = next->prev;
        }
      }
      //Insert element
      if (element != 0) {
        moving->prev = next;
        moving->next = next->next;
        next->next = moving;
        moving->next->prev = moving;
      }
    }
    current = zero;
    cout << current->value << ' ';
    current = current->next;
    while (current->value != 0) {
      cout << current->value << ' ';
      current = current->next;
    }
    cout << endl;
  }
  current = start;
  //Find element
  long long pos = 0, sum = 0;
  current = zero;
  //Get answer
  for (long long j = 0; j < 3; j++) {
    for (long long i = 0; i < 1000; i++) {
      current = current->next;
    }
    cout << current->value << endl;
    sum += current->value;
  }
  cout << sum << endl;

  //Clean up memory
  Node* next = start;
  start->prev->next = NULL; //Set up endpoint
  while (next->next != NULL) {
    Node* temp = next->next;
    delete next;
    next = temp;
  }
  return 0;
}
