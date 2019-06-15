#include <stdio.h>
#include <stdlib.h>
#include "MGraph.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void print_data(MVertex* v)
{
    printf("%s", (char*)v);
}

int main(int argc, char *argv[])
{
    MVertex* v[] = {"A", "B", "C", "D", "E", "F"};
    MGraph* graph = MGraph_Create(v, 6);
    
    MGraph_AddEdge(graph, 0, 1, 1);
    MGraph_AddEdge(graph, 0, 2, 1);
    MGraph_AddEdge(graph, 0, 3, 1);
    MGraph_AddEdge(graph, 1, 5, 1);
    MGraph_AddEdge(graph, 1, 4, 1);
    MGraph_AddEdge(graph, 2, 1, 1);
    MGraph_AddEdge(graph, 3, 4, 1);
    MGraph_AddEdge(graph, 4, 2, 1);
    
    MGraph_Display(graph, print_data);
    
    MGraph_DFS(graph, 0, print_data);
    MGraph_BFS(graph, 0, print_data);
    
    MGraph_Destroy(graph);
    
	return 0;
}
