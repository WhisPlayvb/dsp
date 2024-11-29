#include <iostream>
#include <algorithm>
#include <vector>
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

void displayClocks(const vector<Lamport>& processes) {
    cout << "\n-------------------------------\n";
    for (size_t i = 0; i < processes.size(); ++i) {
        cout << "Process " << i + 1 << " Lamport Clock: " << processes[i].getTime() << endl;
    }
    cout << "-------------------------------\n";
}

int main() {
    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    if (cin.fail() || numProcesses < 2) {
        cout << "Invalid number of processes! Exiting..." << endl;
        return 1;
    }

    vector<Lamport> processes(numProcesses);
    int choice, p1, p2;

    cout << "\nLamport Logical Clock Simulation\n";
    cout << "---------------------------------\n";

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Tick a process clock\n";
        cout << "2. Send a message from one process to another\n";
        cout << "3. Display current clock times\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 4) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid choice! Please enter a number between 1 and 4.\n";
            continue;
        }

        switch (choice) {
            case 1:
                cout << "\nEnter the process number to tick (1 to " << numProcesses << "): ";
                cin >> p1;

                if (cin.fail() || p1 < 1 || p1 > numProcesses) {
                    cout << "Invalid process number!\n";
                    break;
                }

                cout << "\nProcess " << p1 << " clock tick.\n";
                processes[p1 - 1].tick();
                break;

            case 2:
                cout << "\nEnter the sender process number (1 to " << numProcesses << "): ";
                cin >> p1;
                cout << "Enter the receiver process number (1 to " << numProcesses << "): ";
                cin >> p2;

                if (cin.fail() || p1 < 1 || p1 > numProcesses || p2 < 1 || p2 > numProcesses || p1 == p2) {
                    cout << "Invalid process numbers or sender and receiver are the same!\n";
                    break;
                }

                cout << "\nProcess " << p1 << " sends a message to Process " << p2 << ".\n";
                processes[p1 - 1].send();
                processes[p2 - 1].receive(processes[p1 - 1]);
                break;

            case 3:
                displayClocks(processes);
                break;

            case 4:
                cout << "\nFinal Clock States:\n";
                displayClocks(processes);
                cout << "Exiting the program. Goodbye!\n";
                return 0;
        }
    }
}


