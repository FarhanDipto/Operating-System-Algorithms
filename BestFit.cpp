#include <bits/stdc++.h>
using namespace std;

void bestFit(vector<int>& memoryHoles, vector<int>& memoryRequests) {
    int totalHoles = memoryHoles.size();
    int totalRequests = memoryRequests.size();

    vector<int> allocationStatus(totalRequests, -1);

    for (int i = 0; i < totalRequests; i++) {
        int bestFitIndex = -1;
        int minBlockSize = INT_MAX;

        for (int j = 0; j < totalHoles; j++) {
            if (memoryHoles[j] >= memoryRequests[i] && memoryHoles[j] - memoryRequests[i] < minBlockSize) {
                bestFitIndex = j;
                minBlockSize = memoryHoles[j] - memoryRequests[i];
            }
        }

        if (bestFitIndex != -1) {
            allocationStatus[i] = bestFitIndex + 1;
            memoryHoles[bestFitIndex] -= memoryRequests[i];
        }
    }

    cout << "Best Fit" << endl;
    cout << "Memory Allocation Step by step" << endl;

    for (int i = 0; i < totalRequests; i++) {
        cout << "Allocation of " << memoryRequests[i] << ": ";
        if (allocationStatus[i] != -1) {
            cout << memoryRequests[i] << " Allocated in Block " << allocationStatus[i];
        } else {
            cout << "CANT be allocated";
        }
        cout << endl;
    }

    int externalFragmentation = 0;
    for (int block : memoryHoles) {
        externalFragmentation += block;
    }

    if (externalFragmentation > 0) {
        cout << "External Fragmentation: " << externalFragmentation << endl;
    } else {
        cout << "No External Fragmentation" << endl;
    }
}

int main() {
    vector<int> memoryHoles = {50, 200, 70, 115, 15};
    vector<int> memoryRequests = {100, 10, 35, 15, 23, 6, 25, 55, 88, 40};

    bestFit(memoryHoles, memoryRequests);

    return 0;
}
