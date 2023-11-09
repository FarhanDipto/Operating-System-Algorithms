#include<bits/stdc++.h>
using namespace std;

struct process {
    int processID;
    double arrivalTime;
    double cpuTime;
    double waitingTime;
    double turnTime;
    double elapsedTime;
};

void output(struct process p[], int n) {
    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;

    cout<<endl;
    for (int i=0; i<n; i++) {
        cout<<"For process "<<p[i].processID<<",    Waiting Time: "<<p[i].waitingTime<<" & Turnaround Time: " <<p[i].turnTime<<endl;
        totalWaitingTime += p[i].waitingTime;
        totalTurnaroundTime += p[i].turnTime;
    }

    double avgWaitingTime = totalWaitingTime/n;
    double avgTurnaroundTime = totalTurnaroundTime/n;

    cout<<endl;
    cout<<"Average Waiting time: "<<avgWaitingTime<<endl;
    cout<<"Average Turnaround time: "<<avgTurnaroundTime<<endl;
}

void ganttChart(struct process p[], int n) {
    cout << endl;
    cout << "Gantt Chart:" << endl;

    cout<<"|";
    for (int i=0; i<n; i++) {
        cout<<"---P"<<p[i].processID<<"---|";
    }
    cout<<endl<<"0\t ";
    for (int i=0; i<n; i++){
        cout<<p[i].elapsedTime<<"\t ";
    }
    cout << endl;
}

void sortByArrival(struct process p[], int n) {
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-i-1; j++) {
            if (p[j].arrivalTime > p[j+1].arrivalTime) {
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void sortByProcessID(struct process p[], int n) {
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-i-1; j++) {
            if (p[j].processID > p[j+1].processID) {
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    struct process p[n];

    for (int i=0; i<n; i++) {
        p[i].processID = i+1;
        cout<<"Enter the arrival & CPU time for Process " << i + 1 << ": ";
        cin>>p[i].arrivalTime>>p[i].cpuTime;
    }
    sortByArrival(p, n);

    p[0].elapsedTime = p[0].cpuTime;
    for (int i=1; i<n; i++){
        p[i].elapsedTime = p[i-1].elapsedTime + p[i].cpuTime;
        // cout<<"Elapsed time: "<<p[i].elapsedTime;
    }
    
    p[0].waitingTime = 0;
    p[0].turnTime = p[0].waitingTime + p[0].cpuTime;
    for (int i=1; i<n; i++) {
        // p[i].waitingTime = p[i-1].cpuTime + p[i-1].waitingTime - p[i].arrivalTime;
        p[i].waitingTime = p[i-1].elapsedTime - p[i].arrivalTime;
        p[i].turnTime = p[i].waitingTime + p[i].cpuTime;
    }

    ganttChart(p, n);
    sortByProcessID(p, n);
    output(p, n);
    
    return 0;
}
