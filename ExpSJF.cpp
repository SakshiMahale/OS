#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // For INT_MAX

using namespace std;

// Structure to hold process information
struct Process {
    int pid;    // Process ID
    int bt;     // Burst time
    int at;     // Arrival time
    int wt;     // Waiting time
    int tat;    // Turnaround time
};

// Comparator function to sort based on arrival time
bool compareByArrivalTime(const Process &a, const Process &b) {
    return a.at < b.at; // Sort by arrival time
}

// Function to calculate waiting time and turnaround time for SJF non-preemptive
void calculateSJF(vector<Process> &processes) {
    int n = processes.size(); // Number of processes
    vector<bool> isCompleted(n, false); // Track completed processes
    int totalTime = 0; // Tracks the current time
    int completed = 0; // Count of completed processes

    while (completed < n) {
        // Find the process with the shortest burst time that has arrived
        int minIndex = -1;
        int minBurst = INT_MAX;

        for (int i = 0; i < n; i++) {
            // Check if the process has arrived and is not completed
            if (processes[i].at <= totalTime && !isCompleted[i]) {
                // Update minIndex if current process has a shorter burst time
                if (processes[i].bt < minBurst) {
                    minBurst = processes[i].bt;
                    minIndex = i;
                }
            }
        }

        // If no process is found, increment time (idle CPU)
        if (minIndex == -1) {
            totalTime++;
        } else {
            // Calculate waiting time for the selected process
            processes[minIndex].wt = totalTime - processes[minIndex].at;

            // Update current time after executing this process
            totalTime += processes[minIndex].bt;

            // Calculate turnaround time
            processes[minIndex].tat = processes[minIndex].wt + processes[minIndex].bt;

            // Mark the process as completed
            isCompleted[minIndex] = true;
            completed++;
        }
    }
}

int main() {
    cout << "Enter the number of processes: ";
    int n;
    cin >> n;

    vector<Process> processes(n); // Use a vector for dynamic array

    // Input process details
    for (int i = 0; i < n; i++) {
        cout << "Enter process ID: ";
        cin >> processes[i].pid;

        cout << "Enter burst time of process " << processes[i].pid << ": ";
        cin >> processes[i].bt;

        cout << "Enter arrival time of process " << processes[i].pid << ": ";
        cin >> processes[i].at;

        processes[i].wt = 0;   // Initialize waiting time
        processes[i].tat = 0;  // Initialize turnaround time
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), compareByArrivalTime);

    // Calculate waiting time and turnaround time using SJF
    calculateSJF(processes);

    // Output the process details and their times
    cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (const auto &process : processes) {
        cout << process.pid << "\t" << process.at << "\t\t" 
             << process.bt << "\t\t" << process.wt << "\t\t" 
             << process.tat << endl;
    }

    // Calculate and output the average waiting time and turnaround time
    double totalWT = 0, totalTAT = 0;
    for (const auto &process : processes) {
        totalWT += process.wt;
        totalTAT += process.tat;
    }

    cout << "\nAverage Waiting Time: " << totalWT / n << endl;
    cout << "Average Turnaround Time: " << totalTAT / n << endl;

    return 0; // Successful termination of the program
}