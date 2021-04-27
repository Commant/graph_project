#ifndef _GRAPH_H_
#define _GRAPH_H_

#define NO_LINK (-1.0)

struct graph
{
	int n;//nombre de sommet = 1+(dechets+obstacles*4)^2
	float** M;//Matrice telle que M[i][j] = distance entre i et j
	//                                    = NO_LINK s'il y un obstacle entre i et j	
};

struct graph* graph__create(int n_vertice);

void graph__fill(struct graph* g, float distance);

void graph__set_weight(struct graph* g, int i, int j, float distance);

float graph__get_weight(struct graph* g, int i, int j);

//retourne 0 s'il y a un obstacle entre i et j, et 1 s'il sont liés
int graph__is_linked(struct graph* g, int i, int j);

void graph__free(struct graph* g);

#endif