#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Message buffer
    char message[20];

    if (world_rank == 0) {
        // Master process (rank 0) sets the message
        strcpy(message, "Hello World!");
        printf("Master is broadcasting the message: %s\n", message);
    }

    // Broadcast the message from the master (rank 0) to all processes
    MPI_Bcast(message, 20, MPI_CHAR, 0, MPI_COMM_WORLD);

    // All processes (including the master) print the message after the broadcast
    printf("Process %d received message: %s\n", world_rank, message);

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}
