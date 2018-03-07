#include "main.h"

int main(int argc, char ** argv)
{
  MPI_Init(&argc,&argv);
  int world_rank;
  MPI_Comm_rank(MCW, &world_rank);
  int world_size;
  MPI_Comm_size(MCW, &world_size);



  int n, source, i, j, row, seed, max_num, connectivity, print;

  CommLineArgs(argc,argv,&seed,&max_num,&n,&source,&connectivity,&print);

  srand(seed);
  int * edge = (int *)calloc(n * n,sizeof(int));
  int * dist = (int *)calloc(n,sizeof(int));

  printf("n = %d, source = %d, seed = %d, max_num = %d, connectivity = %d\n",n,source,seed,max_num,connectivity);

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
      if (edge[row + j] == (int)INFINITY)
      {
        printf("--,");
      }
      else
      {
        printf("%d,",edge[row + j]);
      }
    }
    printf("\n");
  }

  printf("\n");
  f(source,n,edge,dist);
  printf("\n");

  for (i = 0; i < n; i++)
  {
    if (dist[i] == (int)INFINITY)
    {
      printf("--,\n");
    }
    else
    {
      printf("%d\n",dist[i]);
    }
  }

  free(edge);
  free(dist);
  MPI_Finalize();
  return 0;
}
