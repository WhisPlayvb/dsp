   #include <iostream>
using namespace std;

struct Process {
    int id;            // Unique ID for each process
    bool active;       // Status: active or inactive
    bool isCoordinator; // Flag to indicate if the process is already the coordinator
};

void bullyAlgorithm(Process processes[], int numProcesses, int initiator) {
    if (!processes[initiator].active) {
        cout << "Error: Initiator process is not active!" << endl;
        return;
    }

    cout << "Process " << processes[initiator].id << " initiates election." << endl;

    bool higherActive = false;

    // Send election messages to all higher-numbered active processes
    for (int i = initiator + 1; i < numProcesses; i++) {
        if (processes[i].active) {
            cout << "Process " << processes[initiator].id 
                 << " sends election message to Process " << processes[i].id << endl;
            higherActive = true;

            // Higher process responds
            cout << "Process " << processes[i].id 
                 << " responds to Process " << processes[initiator].id << "'s election message." << endl;
        }
    }

    // If higher active processes exist, let each one initiate its own election
    if (higherActive) {
        for (int i = initiator + 1; i < numProcesses; i++) {
            if (processes[i].active && !processes[i].isCoordinator) {
                bullyAlgorithm(processes, numProcesses, i);
            }
        }
    } else {
        // If no higher active process exists, the initiator becomes the coordinator
        if (!processes[initiator].isCoordinator) { // Check if already coordinator
            cout << "Process " << processes[initiator].id << " becomes the coordinator." << endl;
            processes[initiator].isCoordinator = true; // Mark as coordinator
        }
    }
}

int main() {
    int numProcesses;

    // Get the number of processes from the user
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    Process* processes = new Process[numProcesses];

    // Get the active status of each process
    cout << "Enter the status of each process (1 for active, 0 for inactive):" << endl;
    for (int i = 0; i < numProcesses; i++) {
        processes[i].id = i + 1;
        processes[i].isCoordinator = false; // Initialize coordinator flag
        cout << "Is Process " << processes[i].id << " active? ";
        int status;
        cin >> status;
        processes[i].active = (status == 1);
    }

    // Display the initial process status
    cout << "\nInitial Process Status:" << endl;
    for (int i = 0; i < numProcesses; i++) {
        cout << "Process " << processes[i].id << ": " 
             << (processes[i].active ? "Active" : "Inactive") << endl;
    }
    cout << endl;

    // Get the initiator process
    int initiator;
    cout << "Enter the initiator process ID: ";
    cin >> initiator;

    // Convert initiator ID to index (ID starts from 1, index starts from 0)
    initiator -= 1;

    if (initiator < 0 || initiator >= numProcesses) {
        cout << "Error: Invalid initiator process ID!" << endl;
        delete[] processes;
        return 1;
    }

    // Run the Bully Algorithm
    bullyAlgorithm(processes, numProcesses, initiator);

    delete[] processes; // Free dynamically allocated memory
    return 0;
}
/*
Output:
Enter the number of processes: 5
Enter the status of each process (1 for active, 0 for inactive):
Is Process 1 active? 1
Is Process 2 active? 1
Is Process 3 active? 0
Is Process 4 active? 1
Is Process 5 active? 1

Initial Process Status:
Process 1: Active
Process 2: Active
Process 3: Inactive
Process 4: Active
Process 5: Active

Enter the initiator process ID: 2
Process 2 initiates election.
Process 2 sends election message to Process 4
Process 4 responds to Process 2's election message.
Process 2 sends election message to Process 5
Process 5 responds to Process 2's election message.
Process 4 initiates election.
Process 4 sends election message to Process 5
Process 5 responds to Process 4's election message.
Process 5 initiates election.
Process 5 becomes the coordinator.

Theory:
Output:
Enter the number of processes: 5
Enter the status of each process (1 for active, 0 for inactive):
Is Process 1 active? 1
Is Process 2 active? 1
Is Process 3 active? 0
Is Process 4 active? 1
Is Process 5 active? 1

Initial Process Status:
Process 1: Active
Process 2: Active
Process 3: Inactive
Process 4: Active
Process 5: Active

Enter the initiator process ID: 2
Process 2 initiates election.
Process 2 sends election message to Process 4
Process 4 responds to Process 2's election message.
Process 2 sends election message to Process 5
Process 5 responds to Process 2's election message.
Process 4 initiates election.
Process 4 sends election message to Process 5
Process 5 responds to Process 4's election message.
Process 5 initiates election.
Process 5 becomes the coordinator.

*/

