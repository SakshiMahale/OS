#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id;             // Process ID
    int burst_time;    // Burst time
    int priority;      // Priority
};

// Function to perform Priority NON PREEMPTIVE  Scheduling
void priorityScheduling(vector<Process>& processes) {
    int n = processes.size();
    vector<int> waiting_time(n, 0);       // Waiting times for each process
    vector<int> turnaround_time(n, 0);    // Turnaround times for each process

    // Sort processes based on priority (ascending order)
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.priority < b.priority; // Higher priority first
    });

    // Calculate waiting time and turnaround time
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            waiting_time[i] = 0; // First process has no waiting time
        } else {
            waiting_time[i] = processes[i - 1].burst_time + waiting_time[i - 1];
        }
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time; // Turnaround time
    }

    // Output results
    cout << "\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << "\t\t" << processes[i].burst_time 
             << "\t\t" << processes[i].priority << "\t\t" 
             << waiting_time[i] << "\t\t" << turnaround_time[i] << endl;
    }
}

int main() {
    int n; // Number of processes

    // Input number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input burst time and priority for each process
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1; // Process ID starts from 1
        cout << "Enter burst time for process " << processes[i].id << ": ";
        cin >> processes[i].burst_time;
        cout << "Enter priority for process " << processes[i].id << ": ";
        cin >> processes[i].priority;
    }

    // Perform Priority Scheduling
    priorityScheduling(processes);

    return 0;
}