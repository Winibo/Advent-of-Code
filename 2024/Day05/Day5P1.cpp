#include <bits/stdc++.h>

using namespace std;

struct page {
    vector<int> previousPages;
    vector<int> laterPages;
};

map<int, page> pages;

void addPage(int page, int laterPage) {
    pages[page].laterPages.push_back(laterPage);
    pages[laterPage].previousPages.push_back(page);
}

bool check_valid(vector<int> pageList) {
    vector<int> seen;
    for (int x : pageList) {
        page current = pages[x];
        for (int x : current.laterPages) {
            if (find(seen.begin(), seen.end(), x) != seen.end()) {
                return false;
            }
        }
        seen.push_back(x);
    }
    return true;
}

int main()
{
    while (true) {
        string input;
        getline(cin, input);
        if (input.find("|") != string::npos) {
            int a, b;
            int position = input.find("|");
            a = stoi(input.substr(0,position));
            b = stoi(input.substr(position + 1, 2));
            addPage(a, b);
        } else {
            break;
        }
    }
    long long result = 0;
    while (!cin.eof()) {
        string input;
        getline(cin, input);
        istringstream catalog(input);
        vector<int> pages;
        while (!catalog.eof()) {
            int page; char comma;
            catalog >> page >> comma;
            pages.push_back(page);
        }
        if (check_valid(pages)) {
            int middle = pages.size() / 2;
            result += pages[middle];
        }
    }
    cout << result << endl;
    return 0;
}