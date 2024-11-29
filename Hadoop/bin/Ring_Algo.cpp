#include <iostream>
using namespace std;

void ringElection(int numProcesses, int processIDs[], int numInitiators, int initiatorIDs[]) {
    int finalCoordinator = -1;  // Final coordinator process ID
    int finalMaxID = -1;        // Maximum process ID encountered

    // Perform election for each initiator
    for (int i = 0; i < numInitiators; i++) {
        int initiatorID = initiatorIDs[i];
        int initiatorIndex = -1;

        // Find the index of the initiator ID
        for (int j = 0; j < numProcesses; j++) {
            if (processIDs[j] == initiatorID) {
                initiatorIndex = j;
                break;
            }
        }

        if (initiatorIndex == -1) {
            cout << "Invalid initiator ID: " << initiatorID << ". Skipping this initiator." << endl;
            continue;
        }

        cout << "\nElection initiated by Process ID: " << processIDs[initiatorIndex] << endl;

        int current = initiatorIndex;
        int maxID = processIDs[current];
        int coordinator = current;

        // Ring algorithm to find the coordinator
        while (true) {
            current = (current + 1) % numProcesses; // Move to the next process in the ring
            cout << "Passing message to Process ID: " << processIDs[current] << endl;

            // Update coordinator if the process ID is greater
            if (processIDs[current] > maxID) {
                maxID = processIDs[current];
                coordinator = current;
            }

            // Stop when the message returns to the initiator
            if (current == initiatorIndex) {
                break;
            }
        }

        cout << "Coordinator selected in this election: Process ID: " << processIDs[coordinator] << endl;

        // Update the final coordinator if this coordinator has the highest ID
        if (maxID > finalMaxID) {
            finalMaxID = maxID;
            finalCoordinator = coordinator;
        }
    }

    // Display the final coordinator
    cout << "\nFinal Coordinator Process ID: " << processIDs[finalCoordinator] << endl;
}

int main() {
    int numProcesses;

    // Input the number of processes
    cout << "Enter the number of processes in the system: ";
    cin >> numProcesses;

    if (numProcesses <= 1) {
        cout << "There must be at least two processes in the system." << endl;
        return 0;
    }

    int processIDs[numProcesses];

    // Input process IDs
    cout << "\nEnter the Process IDs:" << endl;
    for (int i = 0; i < numProcesses; i++) {
        cout << "Process " << i + 1 << ": ";
        cin >> processIDs[i];
    }

    int numInitiators;

    // Input the number of initiators
    cout << "\nEnter the number of initiators: ";
    cin >> numInitiators;

    if (numInitiators <= 0 || numInitiators > numProcesses) {
        cout << "The number of initiators must be between 1 and the total number of processes." << endl;
        return 0;
    }

    int initiatorIDs[numInitiators];

    // Input the initiators by their process IDs
    cout << "\nEnter the IDs of the initiator processes:" << endl;
    for (int i = 0; i < numInitiators; i++) {
        cout << "Initiator " << i + 1 << ": ";
        cin >> initiatorIDs[i];
    }

    // Call the ring election function
    ringElection(numProcesses, processIDs, numInitiators, initiatorIDs);

    return 0;
}

/*
Enter the number of processes in the system: 5

Enter the Process IDs:
Process 1: 1
Process 2: 2
Process 3: 3
Process 4: 4
Process 5: 5

Enter the number of initiators: 2

Enter the IDs of the initiator processes:
Initiator 1: 2
Initiator 2: 4

Election initiated by Process ID: 2
Passing message to Process ID: 3
Passing message to Process ID: 4
Passing message to Process ID: 5
Passing message to Process ID: 1
Passing message to Process ID: 2
Coordinator selected in this election: Process ID: 5

Election initiated by Process ID: 4
Passing message to Process ID: 5
Passing message to Process ID: 1
Passing message to Process ID: 2
Passing message to Process ID: 3
Passing message to Process ID: 4
Coordinator selected in this election: Process ID: 5

Final Coordinator Process ID: 5


*/


