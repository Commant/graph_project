#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "graph.h"
#include "path.h"
#include "create_graph.h"


void easy(struct graph* g,int* tab){
    int nbr_garbage = floor(sqrt(graph__get_n_vertices(g) - 1));
    tab[0]=0;
    int count = 1;
    for (int i = 0; i<nbr_garbage;i++){
        tab[i+1]=count;
        count += nbr_garbage;
    }
}

int garbage_to_vertice(int v,int previous, int nbr_garbage){
    if (previous<v){
        return ((v-1)*nbr_garbage+previous+1);
    }
    else {
        return ((v-1)*nbr_garbage+previous);
    }
}

float shorter_path(struct graph* g,int* tab, int len){
    float sum=0;
    int vertice;
    int previous_vertice=0;
    for (int i=1;i<len;i++){
        vertice=garbage_to_vertice(tab[i],tab[i-1],len-1);
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
    tab[0]=0;
    for(int k=1;k<len;k++){
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
        vertice=garbage_to_vertice(order[i],order[i-1],len-1);
        path[i]=vertice;
    }
}


void path(struct graph* g, int* path){
    int n=graph__get_n_vertices(g);
    int nbr_garbage = floor(sqrt(n - 1));
    float min = 1000000.0;
    float time;
    int max_incrementation[nbr_garbage+1];
    int incrementation[nbr_garbage+1];
    fill_max(max_incrementation,nbr_garbage+1);
    fill_incrementation(incrementation,nbr_garbage+1);

    while(!compare(max_incrementation,incrementation,nbr_garbage+1)){
        for (int k=nbr_garbage;k>0;k--){
            incrementation[k]+=1;
            if (incrementation[k]<=nbr_garbage){
                if (twice(incrementation,nbr_garbage+1)){
                    time = shorter_path(g,incrementation,nbr_garbage+1);
                    if (time < min){
                        min = time;
                        order_to_path(incrementation,path,nbr_garbage+1);
                    }
                }
                break;
            }
            else{
                incrementation[k]=1;
            }
        }
    }
}
