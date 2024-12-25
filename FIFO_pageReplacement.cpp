#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void fifo_algo(vector<int> queue, int frame_size)
{
    vector<int> page_frame;
    int page_faults = 0;
    for (int i = 0; i < queue.size(); i++)
    {
        int page = queue[i];
        // Check if page is already in the frame (Page Hit)
        if (find(page_frame.begin(), page_frame.end(), page) != page_frame.end())
        {
            cout << "Page hit for page " << page << endl;
        }
        else
        {
            // Page Fault occurs i.e. page not found
            page_faults++;
            // If frame is full, remove the page that came in first
            if (page_frame.size() >= frame_size)
            {
                page_frame.erase(page_frame.begin());
            }
            // Insert the new page
            page_frame.push_back(page);
        }
        // Display current frame
        for (int j = 0; j < page_frame.size(); j++)
        {
            cout << page_frame[j] << " ";
        }
        cout << endl;
    }
    cout << "Total Page Faults: " << page_faults << endl;
}
int main()
{
    vector<int> queue = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 3};
    int frame_size = 4;
    fifo_algo(queue, frame_size);
    return 0;
}
