//2222222222
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BullyAlgorithm {
private:
    int id;                    // ID of the initiating process
    vector<int> processIds;    // List of all process IDs
    int coordinator;           // Current coordinator ID

public:
    BullyAlgorithm(int processId, const vector<int>& ids)
        : id(processId), processIds(ids), coordinator(-1) {}

    void startElection() {
        cout << "Process {" << id << "} initiates an election.\n";

        vector<int> higherIds; // IDs of processes with IDs greater than the initiating process
        for (size_t i = 0; i < processIds.size(); ++i) {
            if (processIds[i] > id) {
                cout << "Process " << id << " sends 'Election' message to Process " << processIds[i] << endl;
                higherIds.push_back(processIds[i]);
            }
        }

        if (higherIds.empty()) {
            // No higher ID exists, the current process becomes the coordinator
            coordinator = id;
            announceCoordinator();
        } else {
            // Simulate receiving 'Ok' messages from all higher ID processes
            for (size_t i = 0; i < higherIds.size(); ++i) {
                cout << "Process " << id << " receives 'Ok' from Process " << higherIds[i] << endl;
            }

            // The highest ID process declares itself as the coordinator
            coordinator = *max_element(higherIds.begin(), higherIds.end());
            cout << "Process " << id << " acknowledges Process " << coordinator << " as the coordinator.\n";

            // Coordinator informs all processes
            for (size_t i = 0; i < processIds.size(); ++i) {
                if (processIds[i] != coordinator) {
                    cout << "Process " << coordinator << " sends 'Coordinator' message to Process " << processIds[i] << endl;
                }
            }
        }
    }

    void announceCoordinator() {
        cout << "Process {" << id << "} becomes the coordinator.\n";
        for (size_t i = 0; i < processIds.size(); ++i) {
            if (processIds[i] != id) {
                cout << "Process " << id << " sends 'Coordinator' message to Process " << processIds[i] << endl;
            }
        }
    }

    int getCoordinator() const {
        return coordinator;
    }
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> processIds;
    cout << "Enter the IDs of the processes:\n";
    for (int i = 0; i < n; i++) {
        int processId;
        cin >> processId;
        processIds.push_back(processId);
    }

    int initiatingProcessId;
    cout << "Enter the ID of the process initiating the election: ";
    cin >> initiatingProcessId;

    BullyAlgorithm initiatingProcess(initiatingProcessId, processIds);

    cout << "\n<--- Bully Algorithm Election --->\n";
    initiatingProcess.startElection();

    cout << "\nElected Coordinator: Process " << initiatingProcess.getCoordinator() << endl;

    return 0;
}