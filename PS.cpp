#include<bits/stdc++.h>
using namespace std;

struct process {
    int processID;
    double arrivalTime;
    double cpuTime;
    int priority;
    double waitingTime;
    double turnTime;
};

void output(process p[], int n) {
    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;

    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << "For process " << p[i].processID << ", Waiting Time: " << p[i].waitingTime << " & Turnaround Time: " << p[i].turnTime << endl;
        totalWaitingTime += p[i].waitingTime;
        totalTurnaroundTime += p[i].turnTime;
    }

    double avgWaitingTime = totalWaitingTime / n;
    double avgTurnaroundTime = totalTurnaroundTime / n;

    cout << endl;
    cout << "Average Waiting time: " << avgWaitingTime << endl;
    cout << "Average Turnaround time: " << avgTurnaroundTime << endl;
}

void sortByArrival(process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrivalTime > p[j + 1].arrivalTime) {
                process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void priorityScheduling(process p[], int n) {
    sortByArrival(p, n);

    double currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        int highestPriorityIndex = -1;
        int highestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && p[i].priority < highestPriority && p[i].cpuTime > 0) {
                highestPriority = p[i].priority;
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex == -1) {
            currentTime++;
        } else {
            int currentProcessIndex = highestPriorityIndex;
            p[currentProcessIndex].cpuTime--;

            if (p[currentProcessIndex].cpuTime == 0) {
                completedProcesses++;
                double endTime = currentTime + 1;
                p[currentProcessIndex].waitingTime = endTime - p[currentProcessIndex].arrivalTime - p[currentProcessIndex].turnTime;
                p[currentProcessIndex].turnTime = endTime - p[currentProcessIndex].arrivalTime;
            }

            currentTime++;
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    process p[n];

    for (int i = 0; i < n; i++) {
        p[i].processID = i + 1;
        cout << "Enter the arrival, CPU time, and priority for Process " << i + 1 << ": ";
        cin >> p[i].arrivalTime >> p[i].cpuTime >> p[i].priority;
        p[i].waitingTime = 0;
        p[i].turnTime = 0;
    }

    priorityScheduling(p, n);
    output(p, n);

    return 0;
}
