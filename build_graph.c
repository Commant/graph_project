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
void print_time(float time)
{
	printf("\033[1;35m (%.2f secondes) \033[1;0m",time);
}
int vertice_to_garbage_dest(int vertice,int n_garbage)
{
	return vertice/(n_garbage+1);
}
int vertice_to_garbage_source(int vertice,int n_garbage)
{
	return vertice%(n_garbage+1);
}
static float square(float x)
{
	return x*x;
}
void print_path(struct graph* g,int* path,int n,struct data d)
{
	//print_tab(path,n);
	printf("\n\033[1;36m===============Chemin===============\033[1;0m\n\n");
	float time_total=sqrt(square(d.robot.x-d.garbage[vertice_to_garbage_source(path[1],d.n_garbage)].x)+square(d.robot.y-d.garbage[vertice_to_garbage_source(path[1],d.n_garbage)].y));
	float time=time_total;
	printf("\033[1;31m[\033[1;33mR\033[1;31m]\033[1;0m(%.0f,%.0f)->\033[1;31m[\033[1;33m%d\033[1;31m]\033[1;0m(%.0f,%.0f)",d.robot.x,d.robot.y,vertice_to_garbage_source(path[1],d.n_garbage),d.garbage[vertice_to_garbage_source(path[1],d.n_garbage)].x,d.garbage[vertice_to_garbage_source(path[1],d.n_garbage)].y);
	print_time(time_total);
	printf("\n");
	for(int k=1;k<n;k++)
	{
		printf("\033[1;31m[\033[1;33m%d\033[1;31m]\033[1;0m(%.0f,%.0f)->\033[1;31m[\033[1;33m%d\033[1;31m]\033[1;0m(%.0f,%.0f)",vertice_to_garbage_dest(path[k-1],d.n_garbage),d.garbage[vertice_to_garbage_dest(path[k-1],d.n_garbage)].x,d.garbage[vertice_to_garbage_dest(path[k-1],d.n_garbage)].y,vertice_to_garbage_dest(path[k],d.n_garbage),d.garbage[vertice_to_garbage_dest(path[k],d.n_garbage)].x,d.garbage[vertice_to_garbage_dest(path[k],d.n_garbage)].y);
		time=graph__get_weight(g,path[k-1],path[k]);
		time_total+=time;
		print_time(time);
		printf("\n");
	}
	printf("\n\033[1;36m============Fin du chemin============\033[1;0m\n\n");
	printf("Le temps total est de \033[1;33m%.2f\033[1;0m secondes\n\n", time_total);	
}