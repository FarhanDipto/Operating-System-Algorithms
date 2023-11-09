#include <bits/stdc++.h>
using namespace std;

int main() {
    int numOfPageReferences = 22;
    vector<int> referenceString = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int numOfMemoryPageFrames = 3;

    unordered_set<int> memorySet;
    double pageFaults = 0;

    for (int i = 0; i < numOfPageReferences; i++) {
        if (memorySet.size() < numOfMemoryPageFrames) {
            if (memorySet.find(referenceString[i]) == memorySet.end()) {
                memorySet.insert(referenceString[i]);
                pageFaults++;
            }
        } else {
            if (memorySet.find(referenceString[i]) == memorySet.end()) {
                int pageToReplace = -1;
                int farthestUseIndex = -1;

                for (int page : memorySet) {
                    int nextUseIndex = find(referenceString.begin() + i, referenceString.end(), page) - referenceString.begin();
                    if (nextUseIndex == numOfPageReferences) {
                        pageToReplace = page;
                        break;
                    }

                    if (nextUseIndex > farthestUseIndex) {
                        farthestUseIndex = nextUseIndex;
                        pageToReplace = page;
                    }
                }

                memorySet.erase(pageToReplace);
                memorySet.insert(referenceString[i]);
                pageFaults++;
            }
        }
    }

    double pageFaultRate = pageFaults / numOfPageReferences * 100;

    cout << "Number of page fault using Optimal Page replacement Algorithm: " << pageFaults << endl;
    cout << "Page Fault Rate: " << fixed << setprecision(2) << pageFaultRate << "%" << endl;

    return 0;
}
