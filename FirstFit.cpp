#include <iostream>
#include <vector>
using namespace std;

void firstFit(vector<int>& memoryHoles, vector<int>& memoryRequests) {
    int totalHoles = memoryHoles.size();
    int totalRequests = memoryRequests.size();

    vector<int> allocationStatus(totalRequests, -1);
    vector<int> memoryBlocks = memoryHoles;

    for (int i = 0; i < totalRequests; i++) {
        for (int j = 0; j < totalHoles; j++) {
            if (memoryBlocks[j] >= memoryRequests[i]) {
                allocationStatus[i] = j + 1;
                memoryBlocks[j] -= memoryRequests[i];
                break;
            }
        }
    }

    cout << "First Fit" << endl;
    cout << "Memory Allocation Step by step:" << endl;

    for (int i = 0; i < totalRequests; i++) {
        cout << "Allocation of " << memoryRequests[i] << ": ";
        if (allocationStatus[i] != -1) {
            cout << memoryRequests[i] << " Allocated in Block " << allocationStatus[i];
        } else {
            cout << "Can not be allocated";
        }
        cout << endl;
    }

    int externalFragmentation = 0;
    for (int block : memoryBlocks) {
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

    firstFit(memoryHoles, memoryRequests);

    return 0;
}
