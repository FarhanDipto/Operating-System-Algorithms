#include<bits/stdc++.h>
using namespace std;

struct process {
    int processID;
    double arrivalTime;
    double cpuTime;
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

void roundRobinScheduling(process p[], int n, double timeQuantum) {
    double remainingTime[n];
    double currentTime = 0;

    for (int i = 0; i < n; i++) {
        remainingTime[i] = p[i].cpuTime;
    }

    while (true) {
        bool allProcessesCompleted = true;

        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                allProcessesCompleted = false;

                if (remainingTime[i] <= timeQuantum) {
                    currentTime += remainingTime[i];
                    p[i].waitingTime = currentTime - p[i].arrivalTime - p[i].cpuTime;
                    p[i].turnTime = currentTime - p[i].arrivalTime;
                    remainingTime[i] = 0;
                } else {
                    currentTime += timeQuantum;
                    remainingTime[i] -= timeQuantum;
                }
            }
        }

        if (allProcessesCompleted) {
            break;
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
        cout << "Enter the arrival time and CPU time for Process " << i + 1 << ": ";
        cin >> p[i].arrivalTime >> p[i].cpuTime;
        p[i].waitingTime = 0;
        p[i].turnTime = 0;
    }

    double timeQuantum;
    cout << "Enter the time quantum: ";
    cin >> timeQuantum;

    roundRobinScheduling(p, n, timeQuantum);
    output(p, n);

    return 0;
}
