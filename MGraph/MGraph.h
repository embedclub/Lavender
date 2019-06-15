
#ifndef _MGRAPH_H_
#define _MGRAPH_H_

typedef void MGraph;
typedef void MVertex;
typedef void (MGraph_Printf)(MVertex*);

MGraph* MGraph_Create(MVertex** v, int n);

void MGraph_Destroy(MGraph* graph);

void MGraph_Clear(MGraph* graph);

int MGraph_AddEdge(MGraph* graph, int v1, int v2, int w);

int MGraph_RemoveEdge(MGraph* graph, int v1, int v2);

int MGraph_GetEdge(MGraph* graph, int v1, int v2);

int MGraph_TD(MGraph* graph, int v);

int MGraph_VertexCount(MGraph* graph);

int MGraph_EdgeCount(MGraph* graph);

void MGraph_DFS(MGraph* graph, int v, MGraph_Printf* pFunc);

void MGraph_BFS(MGraph* graph, int v, MGraph_Printf* pFunc);

void MGraph_Display(MGraph* graph, MGraph_Printf* pFunc);

#endif
