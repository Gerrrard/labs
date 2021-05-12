#ifndef GRAPH_H
#define GRAPH_H

typedef struct Graph {
	int size;
	struct Node * list;
} Graph;

typedef struct Node {
	char * vert;
	double x, y;

	struct Edge * list;
	struct Node * next;
} Node;

typedef struct Edge {
	int weight;
	int c;

	struct Node * end;
	struct Edge * next;
} Edge;

Graph * graph_new();
void graph_delete(Graph * graph);

Node * node_new(char * vert, double x, double y);
void node_delete(Node * node);

int graph_node_add(Graph * graph, char * vert, double x, double y);
int graph_edge_add(Graph * graph, char * vert1, char * vert2, int weight);
int graph_node_del(Graph * graph, char * vert);
int graph_edge_del(Graph * graph, char * vert1, char * vert2);

int graph_graphviz(Graph * graph);
int graph_adj(Graph * graph);

int graph_bfs(Graph * graph, char * vert1, char * vert2);
int graph_bf(Graph * graph, char * vert1, char * vert2);
int graph_fw(Graph * graph, char * vert1, char * vert2);

int graph_rnd(Graph * graph, int size);

Graph * graph_load();
int graph_save(Graph * graph);

//Node * graph_bfs_visit(Node * node, char * vert2);
//void graph_bfs_print_path(Node * node);

#endif
