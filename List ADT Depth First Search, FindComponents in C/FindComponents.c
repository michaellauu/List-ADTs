// Michael Lau
// mlau10
// CMPS 101 - PA5

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"
#define MAX_LEN 160

int main(int argc, char* argv[]) {
	int order, vert1, vert2, strong, count;
	FILE *in, *out;
	if(argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if(in==NULL ) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if(out==NULL ) {
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	fscanf(in, "%d", &order);
	Graph G = newGraph(order);
	while(fscanf(in, "%d %d", &vert1, &vert2) == 2) {
		if(vert1 == 0 && vert2 == 0) break;
		addArc(G, vert1, vert2);
	}
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out, "\n");
	List L = newList();
	for(int i = 1; i <= getOrder(G); i++) {
		append(L, i);
	}
	DFS(G, L);
	Graph trans = transpose(G);
	DFS(trans, L);
	for(int i = 1; i <= getOrder(G); i++) {
		if(getParent(trans, i) == NIL) strong++;
	}
	fprintf(out, "G contains %d strongly connected components:\n", strong);
	List strongComp = newList();
	moveBack(L);
	while(index(L) >= 0) {
		prepend(strongComp, get(L));
		if(getParent(trans, get(L)) == NIL) {
			count++;
			fprintf(out, "Component %d: ", count);
			printList(out, strongComp);
			fprintf(out, "\n");
			clear(strongComp);
			movePrev(L);
		}
		else movePrev(L);
	}
	freeGraph(&G);
	freeGraph(&trans);
	freeList(&L);
	freeList(&strongComp);
	fclose(in);
	fclose(out);
}
