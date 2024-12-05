#include <bits/stdc++.h>

using namespace std;

struct page {
    int pageNumber;
    vector<int> previousPages;
    vector<int> laterPages;
};

map<int, page> pages;

void addPage(int page, int laterPage) {
    pages[page].pageNumber = page;
    pages[page].laterPages.push_back(laterPage);
    pages[laterPage].previousPages.push_back(page);
}

bool checkValid(vector<int> pageList) {
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

vector<int> fixCatalog(vector<int> catalog) {
    vector<int> newCatalog;
    for (int i : catalog) {
        bool inserted = false;
        for (int j = 0; j < newCatalog.size(); j++) {
            auto position = find(pages[i].previousPages.begin(), pages[i].previousPages.end(), newCatalog[j]);
            if (position == pages[i].previousPages.end()) {
                newCatalog.insert(newCatalog.begin() + j,i);
                inserted = true;
                break;
            }
        }
        if (!inserted) {
            newCatalog.push_back(i);
        }
    }
    return newCatalog;
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
        if (!checkValid(pages)) {
            // Correct the catalog
            pages = fixCatalog(pages);
            int middle = pages.size() / 2;
            result += pages[middle];
        }
    }
    cout << result << endl;
    return 0;
}