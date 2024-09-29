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

    if (world_rank == 0) {
        // Master process (rank 0) sends "Hello World!" to all worker processes
        char message[] = "Hello World!";
        for (int i = 1; i < world_size; i++) {
            MPI_Send(message, strlen(message) + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
            printf("Master sent message to process %d\n", i);
        }
    } else {
        // Worker process receives the message from the master
        char message[20];
        MPI_Recv(message, 20, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Worker %d received message: %s\n", world_rank, message);
    }

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}
