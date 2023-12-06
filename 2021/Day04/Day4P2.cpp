#include "bits/stdc++.h"

using namespace std;

struct board {
    vector<vector<pair<int, bool>>> data;
    bool complete = false;
    bool mark(int value) {
        for (int row = 0; row < data.size(); row++) {
            for (int column = 0; column < data[row].size(); column++) {
                if (data[row][column].first == value) {
                    data[row][column].second = true;
                    break;
                }
            }
        }
        return line();
    }

    bool line() {
        if (complete)
            return false;
        //Check every row
        for (int row = 0; row < data.size(); row++) {
            bool rowComplete = true;
            for (int column = 0; column < data[row].size(); column++) {
                if (data[row][column].second == false) {
                    rowComplete = false;
                    break;
                }
            }
            if (rowComplete) {
                complete = true;
                return true;
            }
        }
        //Check every column
        for (int column = 0; column < data[0].size(); column++) {
            bool columnComplete = true;
            for (int row = 0; row < data.size(); row++) {
                if (data[row][column].second == false) {
                    columnComplete = false;
                    break;
                }
            }
            if (columnComplete) {
                complete = true;
                return true;
            }
        }
        return false;
    }
};



vector<board> boards;

int main()
{
    string callouts;
    getline(cin, callouts);
    while (!cin.eof()) {
        //Read boards
        board newBoard;
        bool done = false;
        for (int i = 0; i < 5; i++) {
            vector<pair<int, bool>> line;
            for (int j = 0; j < 5; j++) {
                int x = -1;
                cin >> x;
                if (x == -1) {
                    done = true;
                    break;
                }
                line.push_back(make_pair(x, false));
            }
            if (done)
                break;
            newBoard.data.push_back(line);
        }
        if (done)
            break;
        boards.push_back(newBoard);
    }
    //Parse Data
    // cout << "Parsing Calls" << endl;
    board winningBoard;
    stringstream calls(callouts);
    int finalCall = 0;
    // cout << "Callouts: " << callouts << endl;
    int remainingBoards = boards.size();
    while (!calls.eof()) {
        int call = 0;
        char temp;
        calls >> call >> temp;
        // cout << "Called: " << call << endl;
        bool done = false;
        for (board& cboard : boards) {
            done = cboard.mark(call);
            if (done) {
                remainingBoards--;
                if (remainingBoards == 0) {
                    winningBoard = cboard;
                    break;
                }
                done = false;
            }
        }
        if (done) {
            finalCall = call;
            break;
        }
    }
    // cout << "Reading all boards" << endl;
    // for (auto cboard : boards) {
    //     for (auto x : cboard.data) {
    //         for (auto y : x) { 
    //             cout << y.first << ',' << y.second << ' ';
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

    // cout << "Reading Winning Board" << endl;
    //Read Winning Board
    int answer = 0;
    for (auto x : winningBoard.data) {
        for (auto y : x) {
            if (!y.second) {
                answer += y.first;
            }
            // cout << y.first << ' ';
        }
        // cout << endl;
    }
    cout << answer * finalCall << endl;
    return 0;
}
