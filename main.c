#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "build_graph.h"
#include "path.h"
#include "create_graph.h"
#include <math.h>

//sommet: i:j = sommet du point i sachant qu'on vient du point j 
//poids(i:k --> j:i)=d(i-j)/v + angle(k-i-j)/va
float v_rot=2.0;
float v=1.0;
char* datas_path;

void fix_args(int argc, char* argv[])
{
	if(argc>=2)
	{
		v_rot=(float)(atof(argv[1]));
	}
	if(argc>=3)
	{
		datas_path=argv[2];
	}
	else
	{
		datas_path="./coords.txt";
	}
}

#define NBRE_GARBAGE_MAX_ALL_POSSIBLE_PATHS 8

int main(int argc, char* argv[])
{
	printf("\n\033[1;33m");
	printf("======================================\n");
	printf("========== LE ROBOT RAMASSEUR=========\n");
	printf("======================================\033[1;0m\n");
	fix_args(argc,argv);
	struct data* d=load_data(datas_path);
	//printf("\n");print_data(d);		
	struct graph* g=build_graph(d,v,v_rot);
	//graph__print(g);
	//printf("Angle inital négligé\n");
	printf("\n\033[1;32m-Vitesse de rotation du robot:\033[1;31m %.2f\033[1;0m\n",v_rot);
	printf("\033[1;32m-Nombre de déchets:\033[1;31m %d\033[1;0m\n",d->n_garbage);
	int path[d->n_garbage*(d->n_garbage+1)+1];

	if(d->n_garbage<=NBRE_GARBAGE_MAX_ALL_POSSIBLE_PATHS)
	{
		printf("\033[1;32m-Nombre de déchets inférieur à \033[1;31m%d,\033[1;32m algorithme utilisé:\033[1;0m\n",NBRE_GARBAGE_MAX_ALL_POSSIBLE_PATHS+1);
		printf("\033[1;34m-Calcul de toutes les possibilitées\033[1;0m\n");
		all_possible_paths(g,path,d);
	}
	else
	{
		printf("\033[1;32m-Nombre de déchets supérieur à \033[1;31m%d,\033[1;32m algorithme utilisé:\033[1;0m\n",NBRE_GARBAGE_MAX_ALL_POSSIBLE_PATHS);
		printf("\033[1;35m-Plus proche voisin\033[1;0m\n");
		closest_garbages(g,path,d);
	}
	


	print_path(g,path,d->n_garbage,*d);

	graph__free(g);
	free_data(d);
	/*
	int a = garbage_to_vertice(2,0,3);
	int b = garbage_to_vertice(2,3,3);
	printf("%d-%d\n",a,b);

	struct graph* g = graph__create(5);
	g->M[0][3]=2;
	g->M[3][2]=3;
	int order[3]={0,2,1};
	int c = shorter_path(g,&order[0],3);
	printf("%d\n",c);

	int test[3]={0,2,1};
	int test2[3]={0,2,2};
	int e =twice(test2,3);
	printf("%d-%d\n",d,e);
	*/
	printf("\033[1;33m");
	printf("======================================\n");
	printf("======================================\033[1;0m\n\n");
	return 0;
}