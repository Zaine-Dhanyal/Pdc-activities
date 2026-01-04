#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);  // MPI start

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // process ka number
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // total processes

    // Laptop ka info print karna
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    printf("Hello from process %d of %d on %s\n", rank, size, processor_name);

    MPI_Finalize();  // MPI end
    return 0;
}
