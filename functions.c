#ifndef FUNC

#define FUNC

#include "main.h"

void f(
        int source,
        int n,
        int *edge,
        int *dist
      )
{
  int i, j, count;
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
    for(i = 0; i < n; i++)
    {
      printf("i = %d\n",i);
      if ( (found[i]) == 0 )
      {
        if (DEBUG_FUNC) { printf("dist[%d] = min(%d,(%d + %d = %d));\n",i,dist[i],dist[j],edge[(j * n) + i],addWithInfinity(dist[j],edge[(j * n) + i])); }
        dist[i] = min(dist[i], addWithInfinity(dist[j],edge[(j * n) + i]));
        if (DEBUG_FUNC) { printf("dist[%d] = %d;\n",i,dist[i]); }
      }
    }
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

#endif
