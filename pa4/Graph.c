// Michael Lau
// mlau10
// CMPS 101 - PA4

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

typedef struct GraphObj {
	List *adj;
	int size, order, source;
	int *color;
	int *distance;
	int *parent;
} GraphObj;
Graph newGraph(int n) {
	Graph G = malloc(sizeof(struct GraphObj));
	G->adj = malloc(sizeof(List)*(n+1));
	G->color = malloc(sizeof(int)*(n+1));
	G->distance = malloc(sizeof(int)*(n+1));
	G->parent = malloc(sizeof(int)*(n+1));
	G->size = 0;
	G->order = n;
	G->source = NIL;
	for(int i = 1; i <= n; i++) {
		G->adj[i] = newList();
		G->color[i] = white;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	return G;
}
void freeGraph(Graph* pG) {
	for(int i = 1; i <= getOrder(*pG); i++) freeList(&(*pG)->adj[i]);
	free((*pG)->adj);
	free((*pG)->color);
	free((*pG)->distance);
	free((*pG)->parent);
	free(*pG);
	*pG = NULL;
}
int getOrder(Graph G) {
	if(G == NULL) {
		printf("getOrder: Graph G is null\n");
		exit(1);
	}
	return G->order;
}
int getSize(Graph G) {
	if(G == NULL) {
		printf("getSize: Graph G is null\n");
		exit(1);
	}
	return G->size;
}
int getSource(Graph G) {
	if(G == NULL) {
		printf("getSource: Graph G is null\n");
		exit(1);
	}
	return G->source;
}
int getParent(Graph G, int u) {
	if(G == NULL) {
		printf("getParent: Graph G is null\n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)) {
		printf("getParent: input is less than 1 or greater than order\n");
		exit(1);
	}
	return G->parent[u];
}
int getDist(Graph G, int u) {
	if(G == NULL) {
		printf("getDist: Graph G is null\n");
		exit(1);
		if(u < 1 || u > getOrder(G)) {
			printf("getDist: input is less than 1 or greater than order\n");
			exit(1);
		}
	}
	if(getSource(G) == NIL) return INF;
	else return G->distance[u];
}
void getPath(List L, Graph G, int u) {
	if(G == NULL) {
		printf("getPath: Graph G is null\n");
		exit(1);
	}
	if(L == NULL) {
		printf("getPath: List L is null\n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)) {
		printf("getDist: input is less than 1 or greater than order\n");
		exit(1);
	}
	if(u == getSource(G)) append(L, u);
	else if(G->parent[u] == NIL) append(L, NIL);
	else {
		getPath(L, G, G->parent[u]);
		append(L, u);
	}
}
void makeNull(Graph G) {
	if(G == NULL) {
		printf("makeNull: Graph G is null\n"); // ironic isn't it?
		exit(1);
	}
	for(int i = 1; i <- getOrder(G); i++) {
		clear(G->adj[i]);
		G->color[i] = white;
		G->distance[i] = NIL;
		G->parent[i] = INF;
	}
	G->size = 0;
	G->source = NIL;
}
void addEdge(Graph G, int u, int v) {
	if(G == NULL) {
		printf("addEdge: Graph is null\n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)) {
		printf("addEdge: input u is less than 1 or greater than order\n");
		exit(1);
	}
	if(v < 1 || v > getOrder(G)) {
		printf("addEdge: input v is less than 1 or greater than order\n");
		exit(1);
	}
	addArc(G, u, v); // +1
	addArc(G, v, u); // +1
	G->size--; // -1
}
void addArc(Graph G, int u, int v) {
	if(G == NULL) {
		printf("addArc: Graph is null\n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)) {
		printf("addArc: input u is less than 1 or greater than order\n");
		exit(1);
	}
	if(v < 1 || v > getOrder(G)) {
		printf("addArc: input v is less than 1 or greater than order\n");
		exit(1);
	}
	if(length(G->adj[u]) == 0) {
		append(G->adj[u], v);
		G->size++;
		return;
	}
	for(moveFront(G->adj[u]); index(G->adj[u]) != -1; moveNext(G->adj[u])) {
		if(v < get(G->adj[u])) {
			insertBefore(G->adj[u], v);
			G->size++;
			break;
		}
	}
	if(index(G->adj[u]) == -1) {
		append(G->adj[u], v);
		G->size++;
	}
}
void BFS(Graph G, int s) {
	for(int i = 1; i <= getOrder(G); i++) {
		G->color[i] = white;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->source = s;
	G->color[s] = gray;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	List L = newList();
	append(L, s);
	while(length(L) > 0) {
		int x = front(L);
		deleteFront(L);
		for(moveFront(G->adj[x]); index(G->adj[x]) != -1; moveNext(G->adj[x])) {
			int y = get(G->adj[x]);
			if(G->color[y] == white) {
				G->color[y] = gray;
				G->distance[y] = G->distance[x] + 1;
				G->parent[y] = x;
				append(L, y);
			}
		}
		G->color[x] = black;
	}
	freeList(&L);
}
void printGraph(FILE* out, Graph G) {
	if(out == NULL) {
		printf("printGraph: out is null\n");
		exit(1);
	}
	if(G == NULL) {
		printf("printGraph: G is null\n");
		exit(1);
	}
	for (int i = 1; i <= getOrder(G); i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->adj[i]);
		fprintf(out, "\n");
	}
}