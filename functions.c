#ifndef FUNC

#define FUNC

#include "main.h"

void f(
        int source,
        int n,
        int *edge,
        int *dist,
        MPI_Comm mcw
      )
{
  int world_rank;
  MPI_Comm_rank(mcw, &world_rank);
  int world_size;
  MPI_Comm_size(mcw, &world_size);

  int i, j, count, slice = n/world_size, start = world_rank * slice;
  int * found = (int *) calloc( n, sizeof(int) );
  for(i = 0; i < n; i++)
  {
    found[i] = 0;
    dist[i] = edge[(source * n) + i];
  }

  found[source] = 1;
  count = 1;
  while(count < n )
  {
    printf("choosing...\n");
    j = choose(dist, n, found);
    found[j] = 1;
    count++;
    if (DEBUG_FUNC) printf("j = %d\n",j);
    for(i = start; i < slice; i++)
    {
      printf("i = %d\n",i);
      if ( (found[i]) == 0 )
      {
        if (DEBUG_FUNC) { printf("dist[%d] = min(%d,(%d + %d = %d));\n",i,dist[i],dist[j],edge[(j * n) + i],addWithInfinity(dist[j],edge[(j * n) + i])); }
        dist[i] = min(dist[i], addWithInfinity(dist[j],edge[(j * n) + i]));
        if (DEBUG_FUNC) { printf("dist[%d] = %d;\n",i,dist[i]); }
      }
    }
    Reduce_Bcast_Distances(mcw,dist,n);
  }
  free(found);
}

int choose(int *dist, int n, int *found)
{
  int i, tmp, least = (int)INFINITY, leastPosition = 0;
  for(i = 0; i < n; i++)
  {
      tmp = dist[i];
      if( (!found[i]) && (tmp < least) ) {
        least = tmp;
        leastPosition = i;
      }
  }
  return leastPosition;
}

int min(int i, int j)
{
  if (i < j)
  {
    return i;
  }
  return j;
}

int isConnected(int connectivity)
{
  return ((rand() % connectivity) == 0);
}

void makeGraph(int n, int * edge, int max_num, int connectivity)
{
  int i,j,row;
  for (i = 0; i < n; i++)
  {
    row = i * n;
    for (j = 0; j < n; j++)
    {
      if (i != j && isConnected(connectivity))
      {
        edge[row + j] = QUAN;
      }
      else
      {
        edge[row + j] = (int)INFINITY;
      }
    }
  }
}

int addWithInfinity(int A, int B)
{
  if (A == (int)INFINITY)
  {
    return A;
  }
  else if (B == (int)INFINITY)
  {
    return B;
  }
  else
  {
    return (A + B);
  }
}

void Reduce_Bcast_Distances(MPI_Comm mcw, int * dist, int n)
{
  int world_rank;
  MPI_Comm_rank(mcw, &world_rank);
  int world_size;
  MPI_Comm_size(mcw, &world_size);

  int level, offset, tag = 0, slice = n/world_size, start = world_rank * slice, myStart = start, mySlice = slice;
  int senderStart, senderSlice;
  MPI_Status status;
  int max = getMax(world_size);

  // Initial loop....
  for(level = 2, offset = 1;
    level <= max;
    level = level * 2, offset = offset * 2)
  {
      if((world_rank % level) == offset)
      {
        //send
        MPI_Send(&dist[myStart], mySlice, MPI_INT,
          world_rank - offset, tag, mcw);
      }
      else if((world_rank % level) == 0)
      {
        //receive iff the sender actually exists
        if ((world_rank + offset) < world_size)
        {
          senderStart = (world_rank + offset) * slice;
          senderSlice = mySlice;
          MPI_Recv(&dist[senderStart], senderSlice, MPI_INT,
            world_rank + offset, MPI_ANY_TAG, mcw, &status);
        }
      }
      else {
        continue;
      }
      mySlice *= 2;
  }

  tag++;
  printf("%d going to sleep...\n",world_rank);
  sleep(3);

  // Broadcast of all-clear signal from world_rank 0.
  for (level = max,
       offset = max/2;
       level >= 2;
       level = level / 2,
       offset = offset / 2
       )
   {
     if ((world_rank % level) == 0)
     {
       // Process is a sender and must relay its all-clear to its recipient,
       // but only if the recipient actually exists.
       if ((world_rank + offset) < world_size)
       {
         MPI_Send(&sig,1,MPI_INT,world_rank + offset,tag,mcw);
       }
     }
     else if ((world_rank % level) == offset)
     {
       // Process is a receiver and must wait for a check-in from its sender.
       MPI_Recv(&sig,1,MPI_INT,world_rank - offset,MPI_ANY_TAG,mcw,&status);
     }
     else
     {
       // Process is neither a sender nor a receiver on this iteration.
       continue;
     }
  }


  return 0;
}

int getMax(int world_size)
{
  int max = 2;
  while (max < world_size)
  {
    max *= 2;
  }
  return max;
}

#endif
