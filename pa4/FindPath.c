// Michael Lau
// mlau10
// CMPS 101 - PA4

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"
#define MAX_LEN 160

int main(int argc, char* argv[]) {
	int order, vert1, vert2;
	FILE *in, *out;
	if(argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if( out==NULL ){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	fscanf(in, "%d", &order);
	Graph G = newGraph(order);
	while(fscanf(in, "%d %d", &vert1, &vert2) == 2) {
		if(vert1 == 0 && vert2 == 0) break;
		addEdge(G, vert1, vert2);
	}
	printGraph(out, G);
	List L = newList();
	while(fscanf(in, "%d %d", &vert1, &vert2) == 2) {
		if(vert1 == 0 && vert2 == 0) break;
		BFS(G, vert1);
		getPath(L, G, vert2);
		if(getDist(G, vert2) == -10) { 
			fprintf(out, "\nThe distance from %d to %d is infinity\n", vert1, vert2);
			fprintf(out, "No %d-%d path exists\n", vert1, vert2);
		}
		else {
			fprintf(out, "\nThe distance from %d to %d is %d\n", vert1, vert2, getDist(G, vert2));
			fprintf(out, "A shortest %d-%d path is: ", vert1, vert2);
			printList(out, L);
			fprintf(out, "\n");
		}
		clear(L);
	}
	
	fclose(in);
	fclose(out);
	freeList(&L);
	freeGraph(&G);
}