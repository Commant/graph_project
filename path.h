#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

void easy(struct graph* g, int* tab);

int garbage_to_vertice(int v,int previous, int nbr_garbage);

float shorter_path(struct graph* g,int* tab, int len);

int twice(int *tab,int len);

void fill_max(int* tab,int len);

void fill_incrementation(int* tab,int len);

int compare(int* t1,int* t2,int len);

void order_to_path(int *order,int *path, int len);

void path(struct graph* g, int* path);

#endif