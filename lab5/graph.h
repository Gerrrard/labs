#ifndef GRAPH_H
#define GRAPH_H

typedef struct Graph {
	int size;
	int esize;

	struct Node * list;
} Graph;

typedef struct Node {
	char * vert;
	double x, y;
	int id;

	struct Edge * list;
	struct Node * next;
} Node;

typedef struct Edge {
	int weight;
	int c;

	struct Node * end;
	struct Edge * next;
} Edge;

typedef struct QNode{
	struct Node * node;
	struct QNode * next;
} QNode;

typedef struct Queue{
	QNode * head;
	QNode * tail;
} Queue;

Graph * graph_new();
void graph_delete(Graph * graph);

Node * node_new(char * vert, double x, double y, int id);
void node_delete(Node * node);

int graph_node_add(Graph * graph, char * vert, double x, double y, int id);
int graph_edge_add(Graph * graph, char * vert1, char * vert2, int weight, int flag);
int graph_node_del(Graph * graph, char * vert);
int graph_edge_del(Graph * graph, char * vert1, char * vert2);

int graph_graphviz(Graph * graph);
int graph_adj(Graph * graph);

int graph_bfs(Graph * graph, char * vert1, char * vert2, int flag);
int graph_bf(Graph * graph, char * vert1, char * vert2, int flag);
int graph_fw(Graph * graph, char * vert1, char * vert2, int flag);

int graph_rnd(Graph * graph, int size);
int graph_test(int count);

char * rand_str(int len);
int rand_int(int max);

void Qdelete(Queue * Q);
Node * Qpop(Queue * Q);
void Qpush(Queue * Q, Node * Gnode);
Queue * Qcreate();

void BFShelp(Node * nodes[], int id);

#endif
