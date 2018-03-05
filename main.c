#include "main.h"

int main(int argc, char ** argv)
{
  MPI_Init(&argc,&argv);
  int world_rank;
  MPI_Comm_rank(MCW, &world_rank);
  int world_size;
  MPI_Comm_size(MCW, &world_size);
  srand(time(NULL));

  int n = 10, source 0;
  int * edge = (int *)calloc(n * n, sizeof(int));
  int * dist = (int *)calloc(n,sizeof(int));

  f(source,n,edge,dist);

  for (i = 0; i < n; i++)
  {
    printf("%d\n",dist[i]);
  }


  MPI_Finalize();
  return 0;
}
