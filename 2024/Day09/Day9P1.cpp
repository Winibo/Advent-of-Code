#include <bits/stdc++.h>

using namespace std;

int main()
{
    string filesystem;
    cin >> filesystem;
    vector<int> result;
    int left = 0, right = filesystem.length() - 1;
    if (filesystem.length() % 2 == 0) {
        right -= 1;
    }
    int blockNum = 0, finalBlockNum = ((filesystem.length() + 1) / 2) - 1;
    int partialCopied = 0;
    while (true) {
        // Copy leftmost block
        int length = filesystem[left] - '0';
        for (int i = 0; i < length; i++) {
            // If left == right, we may have already copied some of the block
            if (left < right) {
                result.push_back(blockNum);
            } else {
                // Finish Copying final block
                while (partialCopied < filesystem[right] - '0') {
                    result.push_back(finalBlockNum);
                    partialCopied++;
                }
                break;
            }
        }
        if (left >= right) break;
        left++;
        // Copy Rightmost block into free space
        length = filesystem[left] - '0';
        for (int i = 0; i < length; i++) {
            result.push_back(finalBlockNum);
            partialCopied++;
            if (partialCopied == filesystem[right] - '0') {
                right -= 2; // We don't care about free space, if we need more, everything is already free
                partialCopied = 0;
                finalBlockNum--;
            }
        }
        left++;
        blockNum++;
    }
    long long answer = 0;
    for (int i = 0; i < result.size(); i++) {
        answer += result[i] * i;
    }
    cout << answer << endl;
    return 0;
}