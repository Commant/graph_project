#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "graph.h"
#include "path.h"


void easy(struct graph* g,int* tab){
    int nbr_garbage = floor(sqrt(graph__get_n_vertices(g) - 1));
    tab[0]=0;
    int count = 1;
    for (int i = 0; i<nbr_garbage;i++){
        tab[i+1]=count;
        count += nbr_garbage;
    }
}


