#ifndef FUNC

#define FUNC

#include "main.h"

Void f(int SOURCE, int n, int **edge, int *dist){ 
  int i, j, count, *found; 
  found = (int *) calloc( n, sizeof(int) ); 
  for(i=0 ; i<n; i++) { 
    found[i] = 0; 
    dist [i] = edge[SOURCE] [i]; 
} 
  
  found[SOURCE] = 1; 
  count = 1; 
  while(count < n ) { 
  j = choose(dist, n, found); 
  found[j] = 1 ; 
  count++; 
  for(i=0; i<n; i++) { 
    if ( !(found[i]) ) 
    dist[i] = min(dist[i],dist[j]+edge[j] [i]; 
} 
      } 
free (found); 
} 
 
int choose(int *dist, int n int *found){ 
int i, tmp, least = INFTY, leastPosition; 
for(i=0; i<n; i++) { 
tmp = dist[i]; 
if( (!found[i]) && (tmp < least) ) { 
least =tmp; 
leastPosition = I; 
} 
} 
teturn leastPosition; 
} 

#endif
