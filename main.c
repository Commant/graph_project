#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "build_graph.h"
#include "path.h"
#include "create_graph.h"

//sommet: i:j = sommet du point i sachant qu'on vient du point j 
//poids(i:k --> j:i)=d(i-j)/v + angle(k-i-j)/va
float v_rot=2.0;
float v=1.0;

void fix_args(int argc, char* argv[])
{
	if(argc>=2)
	{
		v_rot=(float)(atof(argv[1]));
	}
}

int main(int argc, char* argv[])
{
	fix_args(argc,argv);
	struct data* d=load_data("./coords.txt");
	print_data(d);
	struct graph* g=build_graph(d,v,v_rot);
	graph__print(g);
	printf("\n\033[1;32mVitesse de rotation du robot:\033[1;31m %.2f\033[1;0m\n",v_rot);
	int path[d->n_garbage*(d->n_garbage+1)+1];
	easy(g,path);

	print_path(path,d->n_garbage,*d);

	graph__free(g);
	free_data(d);
	return 0;
}