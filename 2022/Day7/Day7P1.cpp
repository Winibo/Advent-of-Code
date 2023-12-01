#include <bits/stdc++.h>

using namespace std;

int sums = 0;

int read_directory() {
  int size = 0;
  string line;
  getline(cin, line);
  while (!cin.eof()) {
    cout << "Reading line: " << line << endl;
    if (line[0] == '$') {
      //Deal with command
      if (line[5] == '.' && line[2] == 'c') {
        //Return to previous
        if (size <= 100000) {
          cout << "Adding size: " << size << " to sums." << endl;
          sums += size;
        }
        cout << "Total Directory size is: " << size << endl;
        return size;
      } else if (line[2] == 'c'){
        //Continue a layer
        cout << "Size before is: " << size << endl;
        size += read_directory();
        cout << "Size is now: " << size << endl;
      }
    } else {
      //Reading data
      if (line[0] != 'd') {
        int file_size = 0;
        for (int i = 0; i < line.length(); i++) {
          if (isdigit(line[i])) {
            file_size = file_size*10 + line[i] - '0';
          } else break;
        }
        cout << "Adding file of size: " << file_size << endl;
        size += file_size;
        cout << "Size is now: " << size << endl;
      }
    }
    getline(cin, line);
  }
  return size;
}


int main() {
  read_directory();
  cout << sums << endl;
  return 0;
}
