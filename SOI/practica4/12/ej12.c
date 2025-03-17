#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int sum, received_value;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if ((size % 2) != 0) {
        if (rank == 0) {
            printf("El número de procesos debe ser potencia de 2.\n");
        }
        MPI_Finalize();
        return 1;
    }

    sum = rank + 1; 

    for (int step = 1; step < size; step *= 2) {
        if (rank % (step * 2) == 0) {
            if (rank + step < size) {
                MPI_Recv(&received_value, 1, MPI_INT, rank + step, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                sum += received_value;
            }
        } 
        else {
            MPI_Send(&sum, 1, MPI_INT, rank - step, 0, MPI_COMM_WORLD);
            break;
        }
    }

    MPI_Bcast(&sum, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Proceso: %d. La suma total es %d\n", rank, sum);


    MPI_Finalize();
    return 0;
}
