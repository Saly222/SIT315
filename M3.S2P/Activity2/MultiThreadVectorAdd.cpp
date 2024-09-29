#include <iostream>
#include <cstdlib>
#include <vector>
#include <thread>
#include <chrono>

using namespace std::chrono;
using namespace std;

void threadVectorAdd(int* v1, int* v2, int* v3, unsigned long start, unsigned long end) {
    for (unsigned long i = start; i < end; i++) {
        v3[i] = v1[i] + v2[i];
    }
}

int main() {
    unsigned long size = 100000000;
    int num_threads = 4;  // Number of threads to use

    int *v1 = new int[size];
    int *v2 = new int[size];
    int *v3 = new int[size];

    // Initialize vectors with random values
    for (unsigned long i = 0; i < size; i++) {
        v1[i] = rand() % 100;
        v2[i] = rand() % 100;
    }

    // Start timing
    auto start = high_resolution_clock::now();

    std::vector<std::thread> threads;
    unsigned long chunk_size = size / num_threads;

    // Create threads for parallel addition
    for (int i = 0; i < num_threads; i++) {
        unsigned long start_index = i * chunk_size;
        unsigned long end_index = (i == num_threads - 1) ? size : start_index + chunk_size;
        threads.push_back(std::thread(threadVectorAdd, v1, v2, v3, start_index, end_index));
    }

    // Wait for all threads to complete
    for (auto& th : threads) {
        th.join();
    }

    // End timing
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by multi-threaded program: " << duration.count() << " microseconds" << endl;

    // Clean up
    delete[] v1;
    delete[] v2;
    delete[] v3;

    return 0;
}
