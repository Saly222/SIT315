#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include <chrono>

using namespace std::chrono;
using namespace std;

void randomVector(int vector[], int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100; // Assign random values between 0 and 99
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    unsigned long vector_size = 100000000; // Total size of the vectors
    unsigned long local_size = vector_size / size; // Size of the local portion for each process

    // Allocate memory for the local vectors
    int *v1 = new int[local_size];
    int *v2 = new int[local_size];
    int *v3 = new int[local_size];

    // Initialize random seed only for the master process
    if (rank == 0) {
        int *full_v1 = new int[vector_size];
        int *full_v2 = new int[vector_size];

        randomVector(full_v1, vector_size); // Generate full v1
        randomVector(full_v2, vector_size); // Generate full v2

        // Scatter the vectors to all processes
        MPI_Scatter(full_v1, local_size, MPI_INT, v1, local_size, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(full_v2, local_size, MPI_INT, v2, local_size, MPI_INT, 0, MPI_COMM_WORLD);

        delete[] full_v1;
        delete[] full_v2;
    } else {
        // Scatter empty data to other processes
        MPI_Scatter(NULL, local_size, MPI_INT, v1, local_size, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(NULL, local_size, MPI_INT, v2, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    }

    auto start = high_resolution_clock::now();

    // Perform local vector addition
    for (unsigned long i = 0; i < local_size; i++) {
        v3[i] = v1[i] + v2[i]; // Element-wise addition
    }

    // Calculate the local sum of v3
    int local_sum = 0;
    for (unsigned long i = 0; i < local_size; i++) {
        local_sum += v3[i];
    }

    // Use MPI_Reduce to sum up all local sums into the total_sum variable at the root process
    int total_sum = 0;
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    auto stop = high_resolution_clock::now();
    if (rank == 0) {
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "Time taken by MPI program: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Total sum of all elements in v3: " << total_sum << std::endl;
    }

    // Clean up
    delete[] v1;
    delete[] v2;
    delete[] v3;

    MPI_Finalize();
    return 0;
}
