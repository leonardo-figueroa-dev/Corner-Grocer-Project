#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;


// CLASS DEFINITION
class GroceryTracker {
private:
    map<string, int> itemFrequency;  // Holds each item and checks how many times it appears

public:
    // Function to read the file and  store info
    void LoadDataFromFile(string filename) {
        ifstream inputFile(filename);
        string item;

        if (!inputFile.is_open()) {
            cout << "Error: Could not open file." << endl;
            return;
        }

        // Reads from file and count it
        while (inputFile >> item) {
            itemFrequency[item]++;
        }

        inputFile.close();

        // create the backup file just incase
        CreateBackupFile();
    }

    // Function to create frequency.dat file
    void CreateBackupFile() {
        ofstream outFile("frequency.dat");
        for (auto const& pair : itemFrequency) {
            outFile << pair.first << " " << pair.second << endl;
        }
        outFile.close();
    }

    // Function to find and print frequency of a specific item
    void FindItemFrequency(string itemName) {
        if (itemFrequency.find(itemName) != itemFrequency.end()) {
            cout << "The item '" << itemName << "' was purchased "
                << itemFrequency[itemName] << " times." << endl;
        }
        else {
            cout << "Item not found in records." << endl;
        }
    }

    // Function to print all items and their frequencies
    void PrintAllFrequencies() {
        cout << left << setw(15) << "Item" << "Frequency" << endl;
        cout << "-------------------------" << endl;
        for (auto const& pair : itemFrequency) {
            cout << left << setw(15) << pair.first << pair.second << endl;
        }
    }

    // Function to print histogram
    void PrintHistogram() {
        cout << "\nItem Purchase Frequency Histogram:\n";
        cout << "-----------------------------------\n";
        for (auto const& pair : itemFrequency) {
            cout << left << setw(15) << pair.first;
            for (int i = 0; i < pair.second; i++) {
                cout << "*";
            }
            cout << endl;
        }
    }
};


int main() {
    GroceryTracker tracker;
    tracker.LoadDataFromFile("CS210_Project_Three_Input_File.txt");

    int choice = 0;
    string item;

    // Menu loop  center
    while (choice != 4) {
        cout << "\n***\n";
        cout << "   Corner Grocer Menu\n";
        cout << "***\n";
        cout << "1. Find frequency of a specific item\n";
        cout << "2. Display all item frequencies\n";
        cout << "3. Display histogram of item frequencies\n";
        cout << "4. Exit program\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            cout << "Enter item name: ";
            cin >> item;
            tracker.FindItemFrequency(item);
            break;
        case 2:
            tracker.PrintAllFrequencies();
            break;
        case 3:
            tracker.PrintHistogram();
            break;
        case 4:
            cout << "Exiting program... Goodbye!\n";
            break;
        default:
            cout << "Invalid selection. Please choose 1–4.\n";
        }
    }

    return 0;
}
