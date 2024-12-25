#include <iostream>
using namespace std;
// Class semaphore
class Semaphore
{
private:
    int count; // The semaphore count
public:
    Semaphore(int initial_count)
    {
        count = initial_count; // Initialize the semaphore with a given count
    }
    // Decrement Semaphore Count
    void down()
    {
        while (count <= 0)
        {
            cout << "Semaphore value Decremented";
        }
        count--;
    }
    // Increment Semaphore count
    void up()
    {
        cout << "Semaphore value Incremented";
        ++count;
    }
};
int main()
{
    return 0;
}
