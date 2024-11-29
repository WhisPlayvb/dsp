#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

const int NUM_PHILOSOPHERS = 5;

// Mutex for each chopstick
std::mutex chopsticks[NUM_PHILOSOPHERS];

// Function to simulate thinking
void think(int philosopher) {
   std::cout << "Philosopher " << philosopher << " is thinking.\n";
   std::this_thread::sleep_for(std::chrono::milliseconds(100 + rand() % 100));
}

// Function to simulate eating
void eat(int philosopher) {
   std::cout << "Philosopher " << philosopher << " is eating.\n";
   std::this_thread::sleep_for(std::chrono::milliseconds(100 + rand() % 100));
}

// Philosopher's actions
void philosopher(int id) {
   int left = id;                     // Left chopstick
   int right = (id + 1) % NUM_PHILOSOPHERS; // Right chopstick

   while (true) {
       think(id);

       // Pick up chopsticks
       if (id % 2 == 0) {
           chopsticks[left].lock();
           chopsticks[right].lock();
       } else {
           chopsticks[right].lock();
           chopsticks[left].lock();
       }

       eat(id);

       // Put down chopsticks
       chopsticks[left].unlock();
       chopsticks[right].unlock();
   }
}

int main() {
   std::vector<thread> philosophers;

   // Create philosopher threads
   for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
       philosophers.emplace_back(philosopher, i);
   }

   // Join threads
   for (auto& p : philosophers) {
       p.join();
   }

   return 0;
}


