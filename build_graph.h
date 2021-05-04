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
};

struct data* load_data(const char* path);

void free_data(struct data* s);

#endif