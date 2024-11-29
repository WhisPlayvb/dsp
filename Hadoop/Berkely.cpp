#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to calculate the average time offset
double calculateAverageOffset(const vector<int> &timeDifferences)
{
    double sum = 0;
    for (int diff : timeDifferences)
    {
        sum += diff;
    }
    return sum / timeDifferences.size();
}

int main()
{
    // Local times of nodes (including the master node)
    vector<int> localTimes = {100, 110, 95, 105}; // Example times
    int masterIndex = 0;                          // Index of the master node
    int masterTime = localTimes[masterIndex];

    // Calculate time differences between master time and other nodes
    vector<int> timeDifferences;
    for (int i = 0; i < localTimes.size(); ++i)
    {
        timeDifferences.push_back(localTimes[i] - masterTime);
    }

    // Calculate the average time offset
    double averageOffset = calculateAverageOffset(timeDifferences);

    // Synchronize all clocks using the average offset
    cout << "Average offset: " << averageOffset << endl;
    for (int i = 0; i < localTimes.size(); ++i)
    {
        localTimes[i] += round(averageOffset) - timeDifferences[i];
        cout << "Node " << i + 1 << " synchronized time: " << localTimes[i] << endl;
    }

    return 0;
}

