#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys\timeb.h>

/* Variables to control the time measuring */
struct timeb start, end;
int finalTime;

int sizeFractal;

int main(int argc, char *argv[])
{
  /* initialize MPI */
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD, &sizeMPI);

  /*Image size total
  Create a matrix to save image
  slaveJob = divided sizeFractal em slave's jobs */
  sizeFractal= atoi(argv[3]);
  int *img = (int*)malloc(sizeFractal*sizeFractal*sizeof(int));
  int slaveJob = (sizeFractal*sizeFractal)/(size -1);

  //http://www.hpc.cam.ac.uk/using-clusters/compiling-and-development/parallel-programming-mpi-example
  //https://github.com/JRWynneIII/Mandelbrot/blob/master/openmp_mpi_mandelbrot.c

  /* Start a counter */
  ftime(&start);

  if (rank == 0) {

  //master functions
  int startJob = 0;
  int endJob = 0;

  //send start x end to slave
  for (i = 1; i<size; i++){
  startJob=  sizeFractal * (i-1);
  endJob = (((i+1) * sizeFractal)-1);

  MPI_Send(&startJob, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
  MPI_Send(&endJob, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
  }

  MPI_Status status;
  }else {
     //slaves
  }

  MPI_Finalize();

  /* End the timer and get result */
  ftime(&end);
  finalTime = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
  printf("\nTime to create a fractal with MPI SIZE %d: %d milliseconds", size, finalTime);
}
