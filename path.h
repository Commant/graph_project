#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_
#include "build_graph.h"

int first_garbage(struct data* d);

void easy(struct graph* g, int* tab,struct data* d);

int garbage_to_vertice(int v,int previous, int nbr_garbage);

float shorter_path(struct graph* g,int* tab, int len,struct data* d);

int twice(int *tab,int len);

void fill_max(int* tab,int len);

void fill_incrementation(int* tab,int len);

int compare(int* t1,int* t2,int len);

void order_to_path(int *order,int *path, int len);

void less_easy(struct graph* g, int* path,struct data* d);

int in_tab(int number,int* tab,int len);

int min_cost(struct graph*g,int *saw,int len,int nbr_garbage, int position,struct data* d);

void possible_way(struct graph* g, int* path,struct data* d);


#endif