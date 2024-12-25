#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;
void lfu_algo(vector<int> queue, int frame_size)
{
    vector<int> page_frame;
    unordered_map<int, int> frequency; // Stores frequency of each page
    int page_faults = 0;
    for (int i = 0; i < queue.size(); i++)
    {
        int page = queue[i];
        // Check if page is already in the frame (Page Hit)
        auto it = find(page_frame.begin(), page_frame.end(), page);
        if (it != page_frame.end())
        {
            cout << "Page hit for page " << page << endl;
            frequency[page]++; // Increase the frequency of the page
        }
        else
        {
            // Page Fault occurs i.e. page not found
            page_faults++;
            // If frame is full, remove the least frequently used page
            if (page_frame.size() >= frame_size)
            {
                int lfu_page = page_frame[0];
                int min_freq = frequency[lfu_page];
                // Find the page with the least frequency
                for (int p : page_frame)
                {
                    if (frequency[p] < min_freq)
                    {
                        lfu_page = p;
                        min_freq = frequency[p];
                    }
                }
                // Remove the least frequently used page
                page_frame.erase(remove(page_frame.begin(), page_frame.end(),
                                        lfu_page),
                                 page_frame.end());
                frequency.erase(lfu_page); // Remove its frequency entry
            }
            // Insert the new page
            page_frame.push_back(page);
            frequency[page] = 1; // Initialize its frequency to 1
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
    lfu_algo(queue, frame_size);
    return 0;
}