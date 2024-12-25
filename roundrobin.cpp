#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Process {
    int id;            // Process ID
    int burst_time;     // Burst time
    int remaining_time; // Remaining burst time
};

// Function to perform Round Robin Scheduling
void roundRobin(vector<Process>& processes, int time_quantum) {
    int n = processes.size();
    vector<int> waiting_time(n, 0);       // Waiting times for each process
    vector<int> turnaround_time(n, 0);    // Turnaround times for each process
    
    queue<Process> process_queue;
    
    // Initialize remaining times for all processes
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        process_queue.push(processes[i]);
    }

    int current_time = 0;
    
    while (!process_queue.empty()) {
        Process current_process = process_queue.front();
        process_queue.pop();
        
        if (current_process.remaining_time > time_quantum) {
            // If process cannot finish within the quantum
            current_time += time_quantum;
            current_process.remaining_time -= time_quantum;
            process_queue.push(current_process);  // Put it back in the queue
        } else {
            // Process finishes within the quantum
            current_time += current_process.remaining_time;
            current_process.remaining_time = 0;
            
            // Calculate waiting time and turnaround time
            int process_id = current_process.id - 1; // For zero-based indexing
            turnaround_time[process_id] = current_time;
            waiting_time[process_id] = turnaround_time[process_id] - processes[process_id].burst_time;
        }
    }
    
    // Output results
    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << "\t\t" << processes[i].burst_time 
             << "\t\t" << waiting_time[i] << "\t\t" << turnaround_time[i] << endl;
    }
}

int main() {
    int n; // Number of processes
    int time_quantum;

    // Input number of processes and time quantum
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> time_quantum;

    vector<Process> processes(n);

    // Input burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter burst time for process " << processes[i].id << ": ";
        cin >> processes[i].burst_time;
    }

    // Perform Round Robin Scheduling
    roundRobin(processes, time_quantum);

    return 0;
}