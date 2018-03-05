#ifndef FUNC

#define FUNC

#include "main.h"

int mybarrier(MPI_Comm mcw)
{
  int world_rank;
  MPI_Comm_rank(mcw, &world_rank);
  int world_size;
  MPI_Comm_size(mcw, &world_size);
  printf("%d entered function\n",world_rank);

  int level, offset, tag = 0, sig = 1;
  //int max = getMax(world_size);
  MPI_Status status;
  MPI_Request request;

  // Main loop....
  //printf("max = %d\n",max);
  for(
      level = 2, offset = 1;
      level <= world_size;
      level = level * 2, offset = offset * 2
     )
  {
      if((world_rank % level) < offset)
      {
        //printf("world_rank + offset = %d\n",world_rank + offset);
        MPI_Isend(&world_rank, 1, MPI_INT, world_rank + offset, tag, mcw, &request);
        MPI_Recv(&sig, 1, MPI_INT, world_rank + offset, tag, mcw, &status);
      }
      else if((world_rank % level) >= offset)
      {
        //printf("world_rank - offset = %d\n",world_rank - offset);
        MPI_Isend(&world_rank, 1, MPI_INT, world_rank - offset, tag, mcw, &request);
        MPI_Recv(&sig, 1, MPI_INT, world_rank - offset, tag, mcw, &status);
      }
      tag++;
  }

  return 0;
}

int getMax(int world_size)
{
  int start = 1;
  while (start < world_size)
  {
    start = start * 2;
  }
  return start;
}

#endif
