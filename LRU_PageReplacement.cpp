#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void lru_algo(vector<int> pages, int frame_size)
{
    vector<int> page_frame;
    int page_faults = 0;
    for (int i = 0; i < pages.size(); i++)
    {
        int page = pages[i];
        // Check if the page is already in the frame (Page Hit)
        auto it = find(page_frame.begin(), page_frame.end(), page);
        if (it != page_frame.end())
        {
            cout << "Page hit for page " << page << endl;
            // Move this page to the end of the list to mark it as most recently used
            page_frame.erase(it);
            page_frame.push_back(page);
        }
        else
        {
            // Page Fault occurs
            page_faults++;
            // If frame is full, remove the least recently used page
            if (page_frame.size() >= frame_size)
            {
                page_frame.erase(page_frame.begin()); // Remove the LRU page (first in the list)
            }
            // Add the new page as the most recently used
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
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 3};
    int frame_size = 4;
    lru_algo(pages, frame_size);
    return 0;
}
