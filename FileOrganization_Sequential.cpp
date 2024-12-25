#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Structure to represent a record in the file
struct Record
{
    int id;
    string name;
    float salary;
};

// Function to write a string to a binary file
void writeString(ofstream &outFile, const string &str)
{
    size_t length = str.length();                                           // Get the length of the string
    outFile.write(reinterpret_cast<const char *>(&length), sizeof(length)); // Write the length of the string
    outFile.write(str.c_str(), length);                                     // Write the string itself
}

// Function to read a string from a binary file
string readString(ifstream &inFile)
{
    size_t length;
    inFile.read(reinterpret_cast<char *>(&length), sizeof(length)); // Read the length of the string

    char *buffer = new char[length + 1]; // Allocate memory for the string (including null terminator)
    inFile.read(buffer, length);         // Read the string content
    buffer[length] = '\0';               // Null-terminate the string

    string result(buffer); // Convert the char array to a string
    delete[] buffer;       // Free the allocated memory
    return result;
}

// Function to create and write records to a sequential file
void createFile(const string &fileName)
{
    ofstream outFile(fileName, ios::binary); // Open file in binary mode

    if (!outFile)
    {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    // Writing some sample records to the file
    Record record1 = {101, "John Doe", 50000.0};
    Record record2 = {102, "Jane Smith", 60000.0};
    Record record3 = {103, "Alice Brown", 55000.0};

    // Writing records sequentially to the file
    outFile.write(reinterpret_cast<const char *>(&record1.id), sizeof(record1.id));
    writeString(outFile, record1.name); // Write the name explicitly
    outFile.write(reinterpret_cast<const char *>(&record1.salary), sizeof(record1.salary));

    outFile.write(reinterpret_cast<const char *>(&record2.id), sizeof(record2.id));
    writeString(outFile, record2.name); // Write the name explicitly
    outFile.write(reinterpret_cast<const char *>(&record2.salary), sizeof(record2.salary));

    outFile.write(reinterpret_cast<const char *>(&record3.id), sizeof(record3.id));
    writeString(outFile, record3.name); // Write the name explicitly
    outFile.write(reinterpret_cast<const char *>(&record3.salary), sizeof(record3.salary));

    cout << "Records have been written to the file sequentially." << endl;

    outFile.close();
}

// Function to read and display records from a sequential file
void readFile(const string &fileName)
{
    ifstream inFile(fileName, ios::binary); // Open file in binary mode

    if (!inFile)
    {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    Record record;

    // Read records sequentially from the file
    while (inFile.read(reinterpret_cast<char *>(&record.id), sizeof(record.id)))
    {
        record.name = readString(inFile); // Read the name explicitly
        inFile.read(reinterpret_cast<char *>(&record.salary), sizeof(record.salary));

        cout << "ID: " << record.id << ", Name: " << record.name << ", Salary: " << record.salary << endl;
    }

    inFile.close();
}

int main()
{
    string fileName = "sequential_file.dat";

    // Create a file and write some records
    createFile(fileName);

    // Read and display records from the file
    cout << "\nReading from the file:\n";
    readFile(fileName);

    return 0;
}
