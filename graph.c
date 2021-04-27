#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

struct graph* graph__create(int n_vertice);

void graph__fill(struct graph* g, float distance);

void graph__set_distance(struct graph* g, int i, int j, float distance);

float graph__get_distance(struct graph* g, int i, int j);

//retourne 0 s'il y a un obstacle entre i et j, et 1 s'il sont liés
int graph__is_linked(struct graph* g, int i, int j);

void graph__free(struct graph* g);