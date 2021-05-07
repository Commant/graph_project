#include "create_graph.h"
#include <math.h>

struct graph* build_graph(struct data* d, float v, float va)
{
  struct graph* graph = graph__create(1+d->n_garbage);
  graph->n=1+d->n_garbage*d->n_garbage;
  for (int i=0; i < graph->n; i++)
    {
      for (int j=0; j < graph->n; j++)
        {
          if( j==graph->n || i==j )
            graph->M[i][j]=NO_LINK;
          else
            {
              int a1 = i%d->n_garbage;
              int b1 = i/d->n_garbage;
              int a2 = j%d->n_garbage;
              int b2 = j/d->n_garbage;
              if( b1 == a2 )
                {
                  float distance1 = sqrt((d->garbage[a1].x-d->garbage[b1].x)*(d->garbage[a1].x-d->garbage[b1].x)+(d->garbage[a1].y-d->garbage[b1].y)*(d->garbage[a1].y-d->garbage[b1].y));
                  float distance2 = sqrt((d->garbage[a2].x-d->garbage[b2].x)*(d->garbage[a2].x-d->garbage[b2].x)+(d->garbage[a2].y-d->garbage[b2].y)*(d->garbage[a2].y-d->garbage[b2].y));
                  float angle = acosf(((d->garbage[b1].x-d->garbage[a1].x)*(d->garbage[b2].x-d->garbage[a2].x)+(d->garbage[b1].y-d->garbage[a1].y)*(d->garbage[b2].y-d->garbage[a2].y))/(distance1*distance2));
                  graph->M[i][j]=distance2/v + angle/va;
                }
              else
                graph->M[i][j] = NO_LINK;
            }
        }
    }
  return graph;
}

