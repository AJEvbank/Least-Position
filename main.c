#include "main.h"

int main(int argc, char ** argv)
{
  MPI_Init(&argc,&argv);
  int world_rank;
  MPI_Comm_rank(MCW, &world_rank);
  int world_size;
  MPI_Comm_size(MCW, &world_size);
  srand(time(NULL));

  if (world_rank == 0)
  {
    printf("World_size = %d.\n\n",world_size);
  }
  else
  {
    sleep(1);
  }

  printf("Rank: %d PRE-barrier.\n",world_rank);

  if (world_rank == (rand()%world_size)) { printf("World Rank %d going to sleep in MAIN.\n",world_rank); sleep(5);}
  mybarrier(MCW);

  printf("Rank: %d POST-barrier.\n",world_rank);


  MPI_Finalize();
  return 0;
}
