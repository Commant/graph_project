#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "build_graph.h"
#include "path.h"
#include "create_graph.h"

//sommet: i:j = sommet du point i sachant qu'on vient du point j 
//poids(i:k --> j:i)=d(i-j)/v + angle(k-i-j)/va

int main(int argc, char* argv[])
{
	struct data* d=load_data("./test.txt");
	print_data(d);

	struct graph* g=build_graph(d,10.0,1.0);

	graph__print(g);
	graph__free(g);
	free_data(d);
	return 0;
}