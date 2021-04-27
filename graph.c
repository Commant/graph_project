#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

struct graph* graph__create(int n_vertice)
{
	return NULL;
}

void graph__fill(struct graph* g, float distance)
{

}

void graph__set_weight(struct graph* g, int i, int j, float distance)
{

}

float graph__get_weight(struct graph* g, int i, int j)
{
	return 0.0;
}
//retourne 0 s'il y a un obstacle entre i et j, et 1 s'il sont liés
int graph__is_linked(struct graph* g, int i, int j)
{
	return 0;
}

void graph__free(struct graph* g)
{

}