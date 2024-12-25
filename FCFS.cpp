#include <iostream>
#include <iomanip> // For std::setw
using namespace std;

void WaitingTime(int BT[], int n)
{
    int wt[15] = {0};
    int TT[15] = {0};

    // Calculate waiting time
    for (int i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + BT[i - 1];
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++)
    {
        TT[i] = BT[i] + wt[i];
    }

    // Display results in a single table
    cout << setw(15) << "Process"
         << setw(20) << "Waiting Time"
         << setw(20) << "Turnaround Time" << endl;
    cout << setfill('-') << setw(55) << "" << setfill(' ') << endl; // Table separator

    for (int i = 0; i < n; i++)
    {
        cout << setw(15) << "P" << i + 1
             << setw(20) << wt[i]
             << setw(20) << TT[i] << endl;
    }

    // Calculate and display total and average
    float TotalWt = 0, TotalTT = 0;
    for (int i = 0; i < n; i++)
    {
        TotalWt += wt[i];
        TotalTT += TT[i];
    }
    float AvgWt = TotalWt / n;
    float AvgTT = TotalTT / n;

    cout << setfill('-') << setw(55) << "" << setfill(' ') << endl; // Final separator
    cout << setw(15) << "Total Waiting Time:" << TotalWt << endl;
    cout << setw(15) << "Average Waiting Time:" << AvgWt << endl;
    cout << setw(15) << "Total Turnaround Time:" << TotalTT << endl;
    cout << setw(15) << "Average Turnaround Time:" << AvgTT << endl;
}

int main()
{
    int n;
    int BT[15];

    cout << "Enter number of processes: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the Burst time for process " << i + 1 << ": ";
        cin >> BT[i];
    }
    WaitingTime(BT, n);

    return 0;
}
