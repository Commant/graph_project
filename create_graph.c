#include "create_graph.h"
#include <math.h>


static float square(float x)
{
  return x*x;
}
static float absf(float x)
{
  if(x>=0.0)
    return x;
  return -x;
}

struct graph* build_graph(struct data* d, float v, float va)
{
  struct graph* graph = graph__create(1+(1+d->n_garbage)*d->n_garbage);
  int a1;
  int b1;
  int a2;
  int b2;
  float distance1;
  float distance2;
  float angle;
  for (int i=0; i < graph->n; i++)
    {
      for (int j=0; j < graph->n; j++)
        {
          if(i==j )
            graph->M[i][j]=NO_LINK;
          else
            {
              a1 = i%(1+d->n_garbage);
              b1 = i/(1+d->n_garbage);
              a2 = j%(1+d->n_garbage);
              b2 = j/(1+d->n_garbage);
              //printf("(%d->%d) puis (%d->%d)\n", a1,b1,a2,b2);
              if(b1 == a2 && a1==d->n_garbage && b1!=d->n_garbage && b2!=d->n_garbage 
                && a2!=d->n_garbage && a1!=b1 && a2!=b2 && b2!=a1)
              {
                  distance1 = sqrt(square(d->robot.x-d->garbage[b1].x)+square(d->robot.y-d->garbage[b1].y));
                  distance2 = sqrt(square(d->garbage[a2].x-d->garbage[b2].x)+square(d->garbage[a2].y-d->garbage[b2].y));
                  if(distance2==0 || distance1==0)
                    angle=0.0;
                  else
                  {
                    float ad_angle=0.0;
                    float scalar_product=((d->garbage[b1].x-d->robot.x)*(d->garbage[b2].x-d->garbage[a2].x)+(d->garbage[b1].y-d->robot.y)*(d->garbage[b2].y-d->garbage[a2].y))/(distance1*distance2);
                    if(scalar_product<0.0)
                    {
                      scalar_product=-scalar_product;
                      ad_angle=M_PI/2;
                    }
                    angle = absf(acosf(scalar_product))+ad_angle;
                    //printf("angle entre (%d,%d,%d):%f\n",a1,a2,b2,angle);
                  }
                  //printf("d1:%.2f; d2:%.2f;angle:%.2f\n", angle);
                  graph->M[i][j]=distance2/v + angle/va;
              }
              else
              {
                if( b1 == a2 && b2!=a2 && a1!=b1 && a1!=b2 && b1!=d->n_garbage 
                  && b2!=d->n_garbage && a2!=d->n_garbage)
                  {
                    distance1 = sqrt(square(d->garbage[a1].x-d->garbage[b1].x)+square(d->garbage[a1].y-d->garbage[b1].y));
                    distance2 = sqrt(square(d->garbage[a2].x-d->garbage[b2].x)+square(d->garbage[a2].y-d->garbage[b2].y));
                    if(distance2==0 || distance1==0)
                      angle=0.0;
                    else
                    {
                      float ad_angle=0.0;
                      float scalar_product=((d->garbage[b1].x-d->garbage[a1].x)*(d->garbage[b2].x-d->garbage[a2].x)+(d->garbage[b1].y-d->garbage[a1].y)*(d->garbage[b2].y-d->garbage[a2].y))/(distance1*distance2);
                      if(scalar_product<0.0)
                      {
                        scalar_product=-scalar_product;
                        ad_angle=M_PI/2;
                      }
                      angle = absf(acosf(scalar_product))+ad_angle;
                      //printf("angle entre (%d,%d,%d):%f\n",a1,a2,b2,angle);
                    }
                    //printf("(%d->%d):%.2f\n",a1,b1,d->garbage[a1].x,d->garbage[b1].x);
                    //printf("distance:%.2f et %.2f et %.2f\n",distance1,distance2,angle );
                    //printf("angle:%.2f\n", angle);
                    graph->M[i][j]=distance2/v + angle/va;
                  }
                else
                {
                  graph->M[i][j] = NO_LINK;
                }
              }
            }
        }
    }
  return graph;
}

