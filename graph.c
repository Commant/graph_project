#include "graph.h"
#include <stdio.h>
#include <stdlib.h>


struct graph* graph__create(int n_vertice)
{
	struct graph* g=malloc(sizeof(struct graph));

	g->M=malloc(n_vertice*sizeof(float*));
	for(int i=0;i<n_vertice;i++)
	{
		g->M[i]=malloc(n_vertice*sizeof(float));
	}

	g->n=n_vertice;
	return g;
}

//retourner le nombre des sommet du graphe
int graph__get_n_vertices(struct graph* g)
{
	return g->n;
}


//remplir les éléments de la matrice par le poids "weight" si les coordonnées vérifient la fonction f
void graph__fill_area(struct graph* g, int (*f)(int,int), float weight)
{
	for(int i=0;i<g->n;i++)
	{
		for(int j=0;j<g->n;j++)
		{
			if(f(i,j)==1)
				g->M[i][j]=weight;
		}
	}
}

///// fonctions test //////
static int always_true(int i,int j)
{
	return 1;
}


void graph__fill(struct graph* g, float weight)
{
	graph__fill_area(g,always_true,weight);
}
/////////////////////////////////////

//remplir l'élément (i,j) de la matrice d'adjacence par le poids "time"
void graph__set_weight(struct graph* g, int i, int j, float weight)
{
	g->M[i][j]=weight;
}

//casser la liaison entre les 2 sommets i et j
void graph__untie(struct graph* g, int i, int j)
{
	graph__set_weight(g,i,j,NO_LINK);
	graph__set_weight(g,j,i,NO_LINK);
}

//retourner le poids de l'élément (i,j) de la matrice d'adjacence
float graph__get_weight(struct graph* g, int i, int j)
{
	return g->M[i][j];
}

//retourne 0 s'il y a un obstacle entre i et j, et 1 s'il sont liés
int graph__is_linked(struct graph* g, int i, int j)
{
	if(graph__get_weight(g,i,j)<NO_LINK/2.0)
		return 0;
	return 1;
}

//liberer l'espace aloué au graphe
void graph__free(struct graph* g)
{
	for(int i=0;i<g->n;i++)
	{
		free(g->M[i]);
	}
	free(g->M);
	free(g);
}


static int diagonal(int i,int j)
{
	if(i==j)
		return 1;
	return 0;
}

//remplir la diagonale de la matrice d'adjacence par le poids "weight"
void graph__fill_diagonal(struct graph* g, float weight)
{
	graph__fill_area(g,diagonal,weight);
}
//remplir la ième colone de la matrice d'ajacence par "weight"
void graph__fill_vertice(struct graph* g, int v, float weight)
{
	for(int i=0;i<g->n;i++)
	{
		graph__set_weight(g,v,i,weight);
	}
}

//afficher le graphe (s'il est de taille petite)
void graph__print(struct graph* g)
{
	if(g->n>26)
	{
		printf("(Le graphe est trop grand pour etre affiche)\n");
		return;
	}
	char* black="\033[1;30m";
	char* red="\033[1;31m";
	char* green="\033[1;32m";
	char* diag="\033[1;36m";
	char* endc="\033[1;0m";
	char* c;
	printf("[");
	for(int i=0;i<g->n;i++)
	{
		if(i!=0)
			printf(" ");
		printf("[");
		for(int j=0;j<g->n;j++)
		{
			c=black;
			if(graph__is_linked(g,i,j)==0)
				c=red;
			if(i==j)
				c=diag;
			if(graph__get_weight(g,i,j)>0.0)
				c=green;
			printf("%s%.1f%s",c	,g->M[i][j],endc);
			if(j!=g->n-1)
				printf(", ");
		}
		printf("]");
		if(i!=g->n-1)
			printf("\n");
	}
	printf("]\n");
}
