#include <bits/stdc++.h>
using namespace std;

int main() {
    int numOfPageReferences = 22;
    vector<int> referenceString = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int numOfMemoryPageFrames = 3;

    queue<int> memoryQueue;
    unordered_set<int> memorySet;
    double pageFaults = 0;

    for (int i = 0; i < numOfPageReferences; i++) {
        if (memorySet.size() < numOfMemoryPageFrames) {
            if (memorySet.find(referenceString[i]) == memorySet.end()) {
                memoryQueue.push(referenceString[i]);
                memorySet.insert(referenceString[i]);
                pageFaults++;
            }
        } else {
            if (memorySet.find(referenceString[i]) == memorySet.end()) {
                int oldestPage = memoryQueue.front();
                memoryQueue.pop();
                memorySet.erase(oldestPage);
                
                memoryQueue.push(referenceString[i]);
                memorySet.insert(referenceString[i]);
                pageFaults++;
            }
        }
    }

    double pageFaultRate = pageFaults / numOfPageReferences * 100;

    cout << "Number of page fault using FIFO Page replacement Algorithm: " << pageFaults << endl;
    cout << "Page Fault Rate: " << fixed << setprecision(2) << pageFaultRate << "%" << endl;

    return 0;
}
