#ifndef _BUILD_GRAPH_H_
#define _BUILD_GRAPH_H_ 

#include "graph.h"

struct position
{
	float x;
	float y;
};

struct data
{
	struct position robot;
	struct position* garbage;
	int n_garbage;
};

struct data* load_data(const char* path);

void free_data(struct data* s);

void print_data(struct data* d);

void print_path(struct graph* g,int* path,int n,struct data d);

int vertice_to_garbage_dest(int vertice,int n_garbage);

int vertice_to_garbage_source(int vertice,int n_garbage);

#endif