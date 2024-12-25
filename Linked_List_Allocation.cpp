#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class LinkedAllocation
{
public:
    vector<int> disk;
    unordered_map<int, int> links; // maps each block to the next block in the file
    int diskSize;
    LinkedAllocation(int size) : diskSize(size)
    {
        disk.resize(size, -1); // -1 indicates free space
    }
    bool allocate(int fileId, const vector<int> &blocks)
    {
        for (int block : blocks)
        {
            if (block >= diskSize || disk[block] != -1)
            {
                cout << "Allocation failed for File " << fileId << ": some blocks are already occupied or out of range." << endl;
                return false;
            }
        }
        for (size_t i = 0; i < blocks.size(); ++i)
        {
            disk[blocks[i]] = fileId;
            links[blocks[i]] = (i + 1 < blocks.size()) ? blocks[i + 1] : -1; // -1 indicates end of file
        }
        cout << "File " << fileId << " allocated with linked blocks: ";
        for (int block : blocks)
            cout << block << " -> ";
        cout << "END" << endl;
        return true;
    }
};
// Usage example
int main()
{
    LinkedAllocation diskLinked(10);
    diskLinked.allocate(1, {2, 5, 7});
    diskLinked.allocate(2, {3, 6, 8});
    return 0;
}
