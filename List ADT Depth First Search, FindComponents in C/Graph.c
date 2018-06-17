// Michael Lau
// mlau10
// CMPS 101 - PA5

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

typedef struct GraphObj {
	List *adj;
	int size, order;
	int *color;
	int *parent;
	int *discover;
	int *finish;
} GraphObj;
Graph newGraph(int n) {
	Graph G = malloc(sizeof(struct GraphObj));
	G->adj = malloc(sizeof(List)*(n+1));
	G->color = malloc(sizeof(int)*(n+1));
	G->parent = malloc(sizeof(int)*(n+1));
	G->discover = malloc(sizeof(int)*(n+1));
	G->finish = malloc(sizeof(int)*(n+1));
	G->size = 0;
	G->order = n;
	for(int i = 1; i <= n; i++) {
		G->adj[i] = newList();
		G->color[i] = white;
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}
	return G;
}
void freeGraph(Graph* pG) {
	for(int i = 1; i <= getOrder(*pG); i++) freeList(&(*pG)->adj[i]);
	free((*pG)->adj);
	free((*pG)->color);
	free((*pG)->parent);
	free((*pG)->discover);
	free((*pG)->finish);
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
int getDiscover(Graph G, int u) {
	if(G == NULL) {
		printf("getDiscover: Graph G is null\n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)) {
		printf("getDiscover: input is less than 1 or greater than order\n");
		exit(1);
	}
	return G->discover[u];
}
int getFinish(Graph G, int u) {
	if(G == NULL) {
		printf("getFinish: Graph G is null\n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)) {
		printf("getFinish: input is less than 1 or greater than order\n");
		exit(1);
	}
	return G->finish[u];
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
void Visit(Graph G, List S, int u, int *time) {
	G->color[u] = gray;
	G->discover[u] = ++(*time);
	moveFront(G->adj[u]);
	while(index(G->adj[u]) != -1) {
		if(G->color[get(G->adj[u])] == white) {
			G->parent[get(G->adj[u])] = u;
			Visit(G, S, get(G->adj[u]), time);
		}
		moveNext(G->adj[u]);
	}
	G->color[u] = black;
	G->finish[u] = ++(*time);
	prepend(S, u);
}
void DFS(Graph G, List S) {
	if(G == NULL) {
		printf("DFS: G is null\n");
		exit(1);
	}
	if(S == NULL) {
		printf("DFS: S is null\n");
		exit(1);
	}
	for(int i = 1; i <= getOrder(G); i++) {
		G->color[i] = white;
		G->parent[i] = 0;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}
	int time = 0;
	List L = copyList(S);
	clear(S);
	moveFront(L);
	while(index(L) >= 0) {
		if(G->color[(get(L))] == white) Visit(G, S, get(L), &time);
		moveNext(L);
	}
	freeList(&L);
}
Graph transpose(Graph G) {
	if(G == NULL) {
		printf("transpose: G is null\n");
		exit(1);
	}
	Graph transposed = newGraph(getOrder(G));
	for(int i = 1; i <= getOrder(G); i++) {
		moveFront(G->adj[i]);
		while(index(G->adj[i]) >= 0) {
			addArc(transposed, get(G->adj[i]), i);
			moveNext(G->adj[i]);
		}
	}
	return transposed;
}
Graph copyGraph(Graph G) {
	if(G == NULL) {
		printf("copyGraph: G is null\n");
		exit(1);
	}
	Graph copy = newGraph(getOrder(G));
	for(int i = 1; i <= getOrder(G); i++) {
		moveFront(G->adj[i]);
		while(index(G->adj[i]) >= 0) {
			addArc(copy, i, get(G->adj[i]));
			moveNext(G->adj[i]);
		}
	}
	return copy;
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
	for(int i = 1; i <= getOrder(G); i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->adj[i]);
		fprintf(out, "\n");
	}
}