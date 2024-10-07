#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#include <vector>
#include <functional>

// Mutex for thread-safe output
std::mutex print_mutex;

// A simple task function to run in a thread
void taskFunction(const std::string &message, int count) {
    for (int i = 0; i < count; ++i) {
        {
            // Locking the mutex to ensure thread-safe output
            std::lock_guard<std::mutex> guard(print_mutex);
            std::cout << "Thread ID: " << std::this_thread::get_id() << " - " << message << std::endl;
        }
        // Simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

// Task using std::async with deferred execution
int asyncTask(int x, int y) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    return x + y;
}

int main() {
    // 1. Thread Creation
    std::string message = "Hello from thread!";
    std::thread t1(taskFunction, message, 5);

    // 2. Check if thread is joinable
    if (t1.joinable()) {
        std::cout << "t1 is joinable.\n";
    }

    // 3. Detaching a thread
    std::thread t2([]() {
        std::lock_guard<std::mutex> guard(print_mutex);
        std::cout << "Detached thread ID: " << std::this_thread::get_id() << " - Detached thread is running." << std::endl;
    });
    t2.detach();

    // 4. std::ref: Passing variables by reference
    std::string return_message = "Initial message";
    std::thread t3([&return_message]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        return_message = "Modified by thread!";
        std::lock_guard<std::mutex> guard(print_mutex);
        std::cout << "Thread modified message: " << return_message << std::endl;
    });
    
    // 5. hardware_concurrency
    std::cout << "Hardware concurrency (threads supported by system): " 
              << std::thread::hardware_concurrency() << std::endl;

    // 6. Using std::this_thread namespace
    std::this_thread::yield();  // Yield the main thread to allow others to execute

    // 7. Using async with launch::async and launch::deferred
    std::future<int> result_async = std::async(std::launch::async, asyncTask, 5, 10);  // Launch immediately
    std::future<int> result_deferred = std::async(std::launch::deferred, asyncTask, 3, 4);  // Deferred

    // 8. Waiting for the async tasks to finish
    std::cout << "Result of async task (immediate): " << result_async.get() << std::endl;
    std::cout << "Result of deferred async task: " << result_deferred.get() << std::endl;

    // 9. Lock and Unlock Mutex manually
    print_mutex.lock();
    std::cout << "Main thread acquired the lock." << std::endl;
    print_mutex.unlock();

    // 10. Using std::this_thread::sleep_for and sleep_until
    std::this_thread::sleep_for(std::chrono::seconds(1));  // Sleep for 1 second
    auto now = std::chrono::system_clock::now();
    std::this_thread::sleep_until(now + std::chrono::seconds(1));  // Sleep until 1 second from now

    // 11. Join threads
    if (t1.joinable()) {
        t1.join();
    }
    if (t3.joinable()) {
        t3.join();
    }

    // Check for non-joinable threads
    std::cout << "t2 is non-joinable as it was detached.\n";
    
    return 0;
}
