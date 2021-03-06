#ifndef _GRAPH_H_
#define _GRAPH_H_

#define NO_LINK (-1.0)


struct graph
{
	int n;//nombre de sommet = 1+dechet*(dechet+1) 
	//1+dechet²+dechet=n <=> dechet² + dechet +(1-n)=0
	//D=1-4*(1-n)=4*n-3
	//n=(-1+sqrt(4*n-3))/2 = (sqrt(4*n-3) -1 )/2
	float** M;//Matrice telle que M[i][j] = distance entre i et j
	//                                    = NO_LINK s'il y un obstacle entre i et j	
};

struct graph* graph__create(int n_vertice);

//The function f(int i,int j) returns 1 if the weight beetwen i and j
//has to be fixed to 'distance', and 0 else.
void graph__fill_area(struct graph* g, int (*f)(int,int), float weight);

void graph__fill(struct graph* g, float weight);

void graph__set_weight(struct graph* g, int i, int j, float weight);

void graph__untie(struct graph* g, int i, int j);

float graph__get_weight(struct graph* g, int i, int j);

//retourne 0 s'il y a un obstacle entre i et j, et 1 s'il sont liés
int graph__is_linked(struct graph* g, int i, int j);

void graph__free(struct graph* g);

void graph__fill_diagonal(struct graph* g, float weight);

void graph__fill_vertice(struct graph* g, int v, float weight);

void graph__print(struct graph* g);

int graph__get_n_vertices(struct graph* g);


#endif
