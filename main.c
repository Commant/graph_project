#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "build_graph.h"

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
	return 0;
}