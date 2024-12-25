#include <iostream>
using namespace std;
#define BUFFER_SIZE 5 // The size of the buffer
// Class Semaphore
class Semaphore
{
private:
    int count; // The semaphore count
public:
    Semaphore(int initial_count)
    {
        count = initial_count; // Initialize the semaphore with a given count
    }
    // Decrement the count
    void wait()
    {
        while (count <= 0)
        {
        }
        count--;
    }
    // Increment the count
    void signal()
    {
        count++;
    }
};
// Shared buffer
int buffer[BUFFER_SIZE];
// 'in' is for producer to add data, 'out' is for consumer to take data
int in = 0, out = 0;
// Semaphores
Semaphore empty_slots(BUFFER_SIZE); // Initially, all buffer slots are empty
Semaphore full_slots(0);            // Initially, no slots are full
Semaphore buffer_mutex(1);          // Mutex to protect the critical section (one can modify buffer)
// Producer function
void producer(int item)
{
    empty_slots.wait();  // Wait if no empty slots
    buffer_mutex.wait(); // Lock the buffer (mutual exclusion)
    // Add item to the buffer
    buffer[in] = item;
    cout << "Produced item: " << item << " at position " << in << endl;
    in = (in + 1) % BUFFER_SIZE; // Move to the next index in a circular manner
    buffer_mutex.signal();       // Release the buffer (mutual exclusion)
    full_slots.signal();         // Increment the count of full slots
}
// Consumer function
void consumer()
{
    full_slots.wait();   // Wait if no full slots
    buffer_mutex.wait(); // Lock the buffer (mutual exclusion)
    int item = buffer[out];
    cout << "Consumed item: " << item << " from position " << out << endl;
    out = (out + 1) % BUFFER_SIZE; // Move to the next index in a circular manner
    buffer_mutex.signal();         // Release the buffer (mutual exclusion)
    empty_slots.signal();          // Increment the count of empty slots
}
int main()
{
    int items_to_produce = 10;
    for (int i = 0; i < items_to_produce; ++i)
    {
        producer(i); // Produce items
        consumer();  // Consume items
    }
    return 0;
}
