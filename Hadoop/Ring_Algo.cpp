#include <bits/stdc++.h>
using namespace std;

// Ring Algorithm Class
class RingAlgorithm {
private:
    vector<int> processes; // List of active processes
    int totalProcesses;    // Total number of processes

public:
    // Constructor to initialize the class with processes
    RingAlgorithm(int n) : totalProcesses(n) {
        processes.resize(n);
        for (int i = 0; i < n; i++) {
            cout << "\nEnter process ID for process "<< ": ";
            cin >> processes[i];
        }
    }

    // Function to randomly remove a process
    void removeRandomProcess() {
        srand(time(0)); // Seed for random number generation
        int failedIdx = rand() % totalProcesses;
        cout << "\nProcess " << processes[failedIdx] << " has failed.\n";

        // Remove the failed process
        processes.erase(processes.begin() + failedIdx);
        totalProcesses--; // Decrement the total number of processes
    }

    // Display the list of active processes
    void displayProcesses() {
        cout << "\nRemaining processes: ";
        for (int i = 0; i < processes.size(); i++) {
            cout << processes[i] << " ";
        }
        cout << endl;
    }

    // Function to start the election
    void startElection(int initiatorID) {
        // Find the index of the initiating process
        vector<int>::iterator it = find(processes.begin(), processes.end(), initiatorID);
        if (it == processes.end()) {
            cout << "\nInvalid process ID entered. Exiting election.\n";
            return;
        }

        int initIdx = distance(processes.begin(), it);
        int leader = -1;
        int curr = initIdx;

        cout << "\nProcess " << processes[curr] << " initiates election\n";
        do {
            int next = (curr + 1) % totalProcesses;
            leader = max(leader, processes[next]);
            cout << "Process " << processes[curr] << " sent message to process " << processes[next] << endl;
            curr = next;
        } while (curr != initIdx);

        cout << "\nLeader of all processes:\t" << leader << endl;
    }
};

int main() {
    int n;

    // Input the total number of processes
    cout << "\nEnter number of processes: ";
    cin >> n;

    // Create an instance of the RingAlgorithm class
    RingAlgorithm ringAlgo(n);

    // Randomly remove a process
    ringAlgo.removeRandomProcess();

    // Display remaining processes
    ringAlgo.displayProcesses();

    // Input the process ID to initiate the election
    int initiatorID;
    cout << "\nEnter process ID which initiates election: ";
    cin >> initiatorID;

    // Start the election process
    ringAlgo.startElection(initiatorID);

    return 0;
}

