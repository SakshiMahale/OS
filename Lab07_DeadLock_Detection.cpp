#include <iostream>
#include <vector>
using namespace std;
void findCycle(int node, vector<vector<int>> &waitForGraph, vector<bool> &visited,
               vector<bool> &stack, vector<int> &path, bool &cycleFound)
{
    visited[node] = true;
    stack[node] = true;
    path.push_back(node); // Add node to the current path
    for (int i = 0; i < waitForGraph.size(); i++)
    {
        if (waitForGraph[node][i] == 1)
        { // If node is waiting for process i
            if (!visited[i])
            {
                findCycle(i, waitForGraph, visited, stack, path, cycleFound);
            }
            else if (stack[i])
            { // Cycle found
                cycleFound = true;

                // Print the deadlock cycle path
                cout << "Deadlock detected among processes: ";
                for (int j = path.size() - 1; j >= 0; j--)
                {
                    if (path[j] == i)
                        break; // Print path until start of cycle
                    cout << path[j] << " -> ";
                }
                cout << i << " -> " << node << endl;

                return;
            }
        }
    }
    stack[node] = false; // Remove the node from the stack
    path.pop_back();     // Remove the node from the current path
}
bool detectDeadlock(vector<vector<int>> &waitForGraph)
{
    int numProcesses = waitForGraph.size();
    vector<bool> visited(numProcesses, false);
    vector<bool> stack(numProcesses, false);
    vector<int> path;
    bool cycleFound = false;
    for (int i = 0; i < numProcesses; i++)
    {
        if (!visited[i])
        {
            findCycle(i, waitForGraph, visited, stack, path, cycleFound);
            if (cycleFound)
                return true;
        }
    }
    return false;
}
int main()
{
    int numProcesses = 3; // Number of processes
    // Hardcoded wait-for graph with a deadlock cycle
    vector<vector<int>> waitForGraph = {
        {0, 1, 0}, // Process 0 is waiting for Process 1
        {0, 0, 1}, // Process 1 is waiting for Process 2
        {1, 0, 0}  // Process 2 is waiting for Process 0 (cycle here)
    };
    if (!detectDeadlock(waitForGraph))
    {
        cout << "No deadlock detected in the system.\n";
    }
    return 0;
}
