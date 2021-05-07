#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "build_graph.h"
#include "path.h"

//sommet: i:j = sommet du point i sachant qu'on vient du point j 
//poids(i:k --> j:i)=d(i-j)/v + angle(k-i-j)/va

int main(int argc, char* argv[])
{
	struct data* d=load_data("./coords.txt");
	print_data(d);
	free_data(d);

	struct graph* g=graph__create(15);
	graph__fill(g,0.0);
	graph__untie(g,6,5);
	graph__untie(g,3,11);
	graph__untie(g,14,13);
	graph__set_weight(g,8,5,15.0);
	graph__set_weight(g,1,5,3.0);
	graph__set_weight(g,2,14,7.0);
	graph__fill_vertice(g,4,2.0);
	graph__fill_diagonal(g,0.0);

	graph__print(g);
	graph__free(g);

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
	int d =twice(test,3);
	int e =twice(test2,3);
	printf("%d-%d\n",d,e);
	*/
	return 0;
}