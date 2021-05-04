#include <stdlib.h>
#include <stdio.h>
#include "build_graph.h"


struct data* load_data(const char* path)
{
	struct data* d=malloc(sizeof(struct data));
	d->n_garbage=0;
	d->garbage=malloc(sizeof(struct position));

	char c;
	int x;
	int y;
	int xm;
	int ym;

	float xf;
	float yf;
	//float xfm;
	//float yfm;
	struct  position co;

	FILE* coords = NULL;
    coords = fopen(path, "r");
 
    if (coords != NULL)
    {
    	int n=0;
 		while(fscanf(coords,"%c : (%d,%d) ;(%d;%d)\n",&c,&x,&y,&xm,&ym)!=EOF)
 		{
 			xf=(float)(x);
 			yf=(float)(y);
 			co.x=xf;
 			co.y=yf;
 			if(c=='R')
 			{
 				d->robot=co;
 			}
 			else
 			{
 				if(c=='X')
 				{
 					//xfm=(float)(xm);
 					//yfm=(float)(ym);
 					//printf("Mur de (%d,%d) a (%d,%d)\n",x,y,xm,ym);
 				}
 				else
 				{
 					n++;
 					d->garbage=realloc(d->garbage,n*sizeof(struct position));
 					d->garbage[n-1]=co;
 					
 				}	
 			}
 		}
 		d->n_garbage=n;
        fclose(coords);
    }
    else
    {
    	printf("ERREUR: Le fichier n'a pas pu etre charge");
    }
	return d;
}

void print_data(struct data* d)
{
	printf("Robot en position x=%.1f et y=%.1f\n",d->robot.x,d->robot.y);
	printf("Positions des dechets:\n[");
	for(int k=0;k<d->n_garbage;k++)
	{
		printf("[%.1f,%.1f]", d->garbage[k].x, d->garbage[k].y);
		if(k!=d->n_garbage-1)
			printf(",");
	}
	printf("]\n");
}

void free_data(struct data* d)
{
	free(d->garbage);
	free(d);
}
