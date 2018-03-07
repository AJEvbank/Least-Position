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
    j = choose(dist, n, found);
    found[j] = 1 ;
    count++;
    for(i=0; i < n; i++)
    {
      if ( !(found[i]) )
        dist[i] = min(dist[i], dist[j] + edge[(j * n) + i]);
    }
  }
  free (found);
}

int choose(int *dist, int n, int *found)
{
  int i, tmp, least = (int)INFINITY, leastPosition;
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

#endif
