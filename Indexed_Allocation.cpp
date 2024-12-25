#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class IndexedAllocation
{
public:
    vector<int> disk;
    unordered_map<int, vector<int>> indexTable;
    int diskSize;
    IndexedAllocation(int size) : diskSize(size)
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
        for (int block : blocks)
        {
            disk[block] = fileId;
        }
        indexTable[fileId] = blocks;
        cout << "File " << fileId << " allocated with blocks: ";
        for (int block : blocks)
            cout << block << " ";
        cout << endl;
        return true;
    }
};
// Usage example
int main()
{
    IndexedAllocation diskIndexed(10);
    diskIndexed.allocate(1, {1, 4, 6});
    diskIndexed.allocate(2, {2, 5, 7});
    return 0;
}
