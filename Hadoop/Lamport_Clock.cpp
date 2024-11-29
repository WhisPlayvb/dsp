#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

class Lamport {
public:
    Lamport() : time(0) {}
    
    void tick() {
        time++;
        cout << "Clock ticked. Current time: " << time << endl;
    }
    
    void send() {
        time++;
        cout << "Message sent. Current time: " << time << endl;
    }
    
    void receive(const Lamport& sender) {
        time = max(time, sender.time + 1);
        cout << "Message received. Current time: " << time << endl;
    }
    
    int getTime() const {
        return time;
    }

private:
    int time;
};

void displayClocks(const Lamport& l1, const Lamport& l2) {
    cout << "\n-------------------------------\n";
    cout << "Process 1 Lamport Clock: " << l1.getTime() << endl;
    cout << "Process 2 Lamport Clock: " << l2.getTime() << endl;
    cout << "-------------------------------\n";
}

int main() {
    Lamport l1, l2;
    int choice;

    cout << "\nLamport Logical Clock Simulation\n";
    cout << "---------------------------------\n";

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. P1 Tick\n";
        cout << "2. P2 Tick\n";
        cout << "3. P1 sends a message to P2\n";
        cout << "4. P2 sends a message to P1\n";
        cout << "5. Display current clock times\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 6) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid choice! Please enter a number between 1 and 6.\n";
            continue;
        }

        switch (choice) {
            case 1:
                cout << "\nProcess 1 clock tick.\n";
                l1.tick();
                break;
            case 2:
                cout << "\nProcess 2 clock tick.\n";
                l2.tick();
                break;
            case 3:
                cout << "\nProcess 1 sends a message to Process 2.\n";
                l1.send();
                l2.receive(l1);
                break;
            case 4:
                cout << "\nProcess 2 sends a message to Process 1.\n";
                l2.send();
                l1.receive(l2);
                break;
            case 5:
                displayClocks(l1, l2);
                break;
            case 6:
                cout << "\nFinal Clock States:\n";
                displayClocks(l1, l2);
                cout << "Exiting the program. Goodbye!\n";
                return 0;
            default:
                cout << "\nInvalid choice! Try again.\n";
                break;
        }
    }
}


