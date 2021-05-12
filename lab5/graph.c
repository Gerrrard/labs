#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "graph.h"

Graph * graph_new(){
	Graph * graph = (Graph *)calloc(1, sizeof(Graph));
	if (!graph) return NULL;

	graph->size = 0;
	graph->list = NULL;

	return graph;
}
void graph_delete(Graph * graph) {
	Node * curr = graph->list;
	Node * prev = NULL;

	while (curr) {
		prev = curr;
		curr = curr->next;
		node_delete(prev);
	}

	free(graph);
}

Node * node_new(char * vert, double x, double y) {
	Node * node = (Node*)calloc(1, sizeof(Node));
	node->vert = (char *)calloc((int)strlen(vert) + 1, sizeof(char));

	if (!node->vert) {
		free(node);
		return NULL;
	}

	strcpy(node->vert, vert);
	node->x = x;
	node->y = y;

	node->list = NULL;
	node->next = NULL;

	return node;
}
void node_delete(Node *node) {
	Edge * cur_edge = node->list;
	Edge * edge = NULL;

	while (cur_edge) {
		edge = cur_edge;
		cur_edge = cur_edge->next;
		free(edge);
	}

	free(node->vert);
	free(node);
}

int graph_node_add(Graph * graph, char * vert, double x, double y) {
	Node * curr  = graph->list;
	Node * prev = NULL;

	while (curr) {
		if (strcmp(curr->vert, vert) == 0){
            printf("ERROR: double of vertex");
		}
		prev = curr;
		curr  = curr->next;
	}

	Node * node = node_new(vert, x, y);

	if (prev)
		prev->next  = node;
	else
		graph->list = node;

	graph->size++;

	return 0;
}
int graph_node_del(Graph * graph, char * vert) {
	Node * curr  = graph->list;
	Node * prev = NULL;

	while (curr) {
		if (strcmp(curr->vert, vert) == 0) {
			if (prev)
				prev->next  = curr->next;
			else
				graph->list = curr->next;

			Node * c_node = graph->list;
			while (c_node) {
				Edge * cur  = c_node->list;
                Edge * prev = NULL;

                while (cur) {
                    if (cur->next == curr) {
                        if (prev)
                            prev->next = cur->next;
                        else
                            c_node->list = cur->next;

                        free(cur);
                        break;
                    }

                    prev = cur;
                    cur = cur->next;
                }
				c_node = c_node->next;
			}

			node_delete(curr);
			graph->size--;
			return 0;
		}

		prev = curr;
		curr = curr->next;
	}

	printf("ERROR: no such vertex");
	return 1;
}
int graph_edge_add(Graph * graph, char * vert1, char * vert2, int weight) {
	Node * curr  = graph->list;
	Node * start = NULL;
	Node * end = NULL;

	if (strcmp(vert1, vert2) == 0) {
        printf("ERROR: Same vertices\n");
        return 1;
	}

	while (curr) {
		if (strcmp(vert1, curr->vert) == 0) {
			start = curr;
			if (end) break;
		}

		if (strcmp(vert2, curr->vert) == 0) {
			end = curr;
			if (start) break;
		}

		curr  = curr->next;
	}

	if (start && end) {
        Edge * cur  = start->list;
        Edge * prev = NULL;

        while (cur) {
            if (cur->end == end) {
                printf("ERROR: Double of edge");
                return 1;
            }

            prev = cur;
            cur  = cur->next;
        }

        Edge * edge = (Edge *)calloc(1, sizeof(Edge));

        edge->weight = weight;
        edge->c = weight;
        edge->end = end;
        edge->next = NULL;

        if (prev)
            prev->next = edge;
        else
            start->list = edge;

        return 0;
    } else {
        printf("ERROR: No such vertex");
		return 1;
	}
}
int graph_edge_del(Graph * graph, char * vert1, char * vert2) {
    Node * curr  = graph->list;
	Node * start = NULL;
	Node * end = NULL;

	if (strcmp(vert1, vert2) == 0){
        printf("ERROR: Same vertices\n");
        return 1;
	}

	while (curr) {
		if (strcmp(vert1, curr->vert) == 0) {
			start = curr;
			if (end) break;
		}

		if (strcmp(vert2, curr->vert) == 0) {
			end = curr;
			if (start) break;
		}

		curr  = curr->next;
	}

	if (start && end) {
        Edge * cur = start->list;
        Edge * prev = NULL;

        while (cur) {
            if (cur->end == end) {
                if (prev)
                    prev->next = cur->next;
                else
                    start->list = cur->next;

                free(cur);
                break;
            }

            prev = cur;
            cur  = cur->next;
        }

        printf("ERROR: no such edge");
        return 1;
	}else{
        printf("ERROR: no such vertex");
        return 1;
	}
}

int graph_graphviz(Graph * graph){
	printf("\n");
	printf("digraph G {\n");

	Node * c_node = graph->list;
	while (c_node) {
		Edge * c_edge = c_node->list;

		if(!c_edge){
            printf("\"%s\";\n", c_node->vert);
		}

		while (c_edge) {
			printf("\"%s\" -> \"%s\"[label = %d];\n", c_node->vert, c_edge->end->vert, c_edge->weight);

			c_edge = c_edge->next;
		}
		c_node = c_node->next;
	}

   	printf("}\n\n");
}
int graph_adj(Graph * graph);

int graph_bfs(Graph * graph, char * vert1, char * vert2);
int graph_bf(Graph * graph, char * vert1, char * vert2);
int graph_fw(Graph * graph, char * vert1, char * vert2);

int graph_rnd(Graph * graph, int size);

Graph * graph_load();
int graph_save(Graph * graph);
