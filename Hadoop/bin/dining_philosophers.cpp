//go to tools>compiler options>in general paste:
//-std=c++11 
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

using namespace std;

class DiningPhilosophers
{
private:
    vector<mutex> forks;             // Mutex for each fork
    vector<condition_variable> cond; // Condition variables for philosophers
    vector<string> states;           // States: Thinking, Hungry, Eating
    mutex mtx;                       // Mutex for shared access to states

    void test(int i)
    {
        if (states[i] == "Hungry" &&
            states[(i + forks.size() - 1) % forks.size()] != "Eating" &&
            states[(i + 1) % forks.size()] != "Eating")
        {
            states[i] = "Eating";
            cond[i].notify_one(); // Notify the philosopher
        }
    }

public:
    explicit DiningPhilosophers(int n) : forks(n), cond(n), states(n, "Thinking") {}

    void pickupForks(int i)
    {
        unique_lock<mutex> lock(mtx);
        states[i] = "Hungry";
        cout << "Philosopher " << i + 1 << " is Hungry.\n";
        test(i);
        while (states[i] != "Eating")
        {
            cond[i].wait(lock); // Wait until forks are available
        }
        cout << "Philosopher " << i + 1 << " starts Eating.\n";
    }

    void putdownForks(int i)
    {
        unique_lock<mutex> lock(mtx);
        states[i] = "Thinking";
        cout << "Philosopher " << i + 1 << " stops Eating and starts Thinking.\n";
        // Notify neighbors
        test((i + forks.size() - 1) % forks.size());
        test((i + 1) % forks.size());
    }

    void philosopher(int i)
    {
        while (true)
        {
            // Think
            cout << "Philosopher " << i + 1 << " is Thinking.\n";
            this_thread::sleep_for(chrono::milliseconds(1000));
            // Pick up forks
            pickupForks(i);
            // Eat
            this_thread::sleep_for(chrono::milliseconds(1000));
            // Put down forks
            putdownForks(i);
        }
    }
};

int main()
{
    int n;
    cout << "Enter the number of philosophers: ";
    cin >> n;

    DiningPhilosophers dp(n);
    vector<thread> philosophers;

    for (int i = 0; i < n; i++)
    {
        philosophers.emplace_back(&DiningPhilosophers::philosopher, &dp, i);
    }

    for (auto &philosopher : philosophers)
    {
        philosopher.join();
    }

    return 0;
}




