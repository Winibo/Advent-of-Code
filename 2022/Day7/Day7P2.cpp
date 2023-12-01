#include <bits/stdc++.h>

using namespace std;

int best = INT_MAX;
string bestName = "";


// Run to get Total disk space, then use to calculate needed free space manually
// int get_size() {
//   int size = 0;
//   string line;
//   getline(cin, line);
//   while (!cin.eof()) {
//     cout << "Reading line: " << line << endl;
//     if (line[0] == '$') {
//       //Deal with command
//       if (line[5] == '.' && line[2] == 'c') {
//         //Return to previous
//         return size;
//       } else if (line[2] == 'c') {
//         //Continue a layer
//         size += get_size();
//       }
//     } else {
//       //Reading data
//       if (line[0] != 'd') {
//         int file_size = 0;
//         for (int i = 0; i < line.length(); i++) {
//           if (isdigit(line[i])) {
//             file_size = file_size*10 + line[i] - '0';
//           } else break;
//         }
//         size += file_size;
//       }
//     }
//     getline(cin, line);
//   }
//   used = size;
//   return size;
// }

int read_directory(string name) {
  int size = 0;
  string line;
  getline(cin, line);
  while (!cin.eof()) {
    cout << "Reading line: " << line << endl;
    if (line[0] == '$') {
      //Deal with command
      if (line[5] == '.' && line[2] == 'c') {
        //Return to previous

        //Put Needed disk space here: (replace 1272621)

        if (size >= 1272621 && size < best) {
          cout << "New best is: " << size << " from directory: " << bestName << endl;
          best = size;
          bestName = name;
        }
        return size;
      } else if (line[2] == 'c'){
        //Continue a layer
        cout << "Size before is: " << size << endl;
        size += read_directory(line.substr(5,99999));
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
  string temp;
  getline(cin, temp);
  // get_size();
  // cout << "Used space is: " << used << endl;
  read_directory("/");
  cout << "Best:" << best << endl;
  cout << "Name:" << bestName << endl;
  return 0;
}
