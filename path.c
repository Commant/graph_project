#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "graph.h"
#include "path.h"
#include "create_graph.h"

static int n_garbages_n(int n_vertices_graph)
{
	return (int)((sqrt(4*n_vertices_graph-3)-1)/2);
}

void easy(struct graph* g,int* tab){
    int nbr_garbage = n_garbages_n(g->n);
    //printf("IL Y A %d DECHETS\n", nbr_garbage);
    int count = nbr_garbage;
    tab[0]=count;
    count = nbr_garbage+1;
    tab[1]=count;
    for (int i = 2; i<nbr_garbage;i++){
    	//printf("COUNT:%d\n",count );
        count += nbr_garbage+2;
    	//printf("ARRIVE:%d\n",count );
        tab[i]=count;
    }
}

int garbage_to_vertice(int v,int previous, int nbr_garbage){
    return v*nbr_garbage+1 + previous;
}

float shorter_path(struct graph* g,int* tab, int len){
    float sum=0;
    int vertice;
    int previous_vertice=garbage_to_vertice(tab[0],g->n,len);
    for (int i=1;i<len;i++){
        vertice=garbage_to_vertice(tab[i],tab[i-1],len);
        sum += g->M[previous_vertice][vertice];
        previous_vertice = vertice;
    }
    return sum;
}

int twice(int *tab,int len){
    for (int i=0;i<len-1;i++){
        for (int j=i+1;j<len;j++){
            if (tab[i]==tab[j]){
                return 0;
            }
        }
    }
    return 1;
}

void fill_max(int* tab,int len){
    for(int k=0;k<len;k++){
        tab[len-k-1]=k;
    }
}

void fill_incrementation(int* tab,int len){
    for(int k=0;k<len;k++){
        tab[k]=k;
    }
    tab[len-1]-=1;
}

int compare(int* t1,int* t2,int len){
    for (int k=0;k<len;k++){
        if(t1[k]!=t2[k]){
            return 0;
        }
    }
    return 1;
}

void order_to_path(int *order,int *path, int len){
    int vertice;
    for (int i=1;i<len;i++){
        vertice=garbage_to_vertice(order[i],order[i-1],len);
        path[i]=vertice;
    }
}


void less_easy(struct graph* g, int* path){
    int n=graph__get_n_vertices(g);
    int nbr_garbage = n_garbages_n(n);
    float min = 1000000.0;
    float time;
    int max_incrementation[nbr_garbage];
    int incrementation[nbr_garbage];
    fill_max(max_incrementation,nbr_garbage);
    fill_incrementation(incrementation,nbr_garbage);

    while(!compare(max_incrementation,incrementation,nbr_garbage)){
        for (int k=nbr_garbage-1;k>=0;k--){
            incrementation[k]+=1;
            if (incrementation[k]<nbr_garbage){
                if (twice(incrementation,nbr_garbage)){
                    time = shorter_path(g,incrementation,nbr_garbage);
                    if (time < min){
                        min = time;
                        order_to_path(incrementation,path,nbr_garbage);
                    }
                }
                break;
            }
            else{
                incrementation[k]=0;
            }
        }
    }
}
