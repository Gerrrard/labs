#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>

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

Node * node_new(char * vert, double x, double y, int id) {
	Node * node = (Node*)calloc(1, sizeof(Node));
	node->vert = (char *)calloc((int)strlen(vert) + 1, sizeof(char));

	if (!node->vert) {
		free(node);
		return NULL;
	}

	strcpy(node->vert, vert);
	node->x = x;
	node->y = y;
	node->id = id;

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

int graph_node_add(Graph * graph, char * vert, double x, double y, int id) {
	Node * curr  = graph->list;
	Node * prev = NULL;

	while (curr) {
		if (strcmp(curr->vert, vert) == 0){
            printf("ERROR: double of vertex");
		}
		prev = curr;
		curr  = curr->next;
	}

	Node * node = node_new(vert, x, y, id);

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
			if (prev) prev->next = curr->next;
			else graph->list = curr->next;

			Node * c_node = graph->list;
			while (c_node) {
				Edge * cur  = c_node->list;
                Edge * prev = NULL;

                while (cur) {
                    if (cur->end == curr) {
                        if (prev) prev->next = cur->next;
                        else c_node->list = cur->next;

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
	return 0;
}
int graph_edge_add(Graph * graph, char * vert1, char * vert2, int weight, int flag) {
	Node * curr  = graph->list;
	Node * start = NULL;
	Node * end = NULL;

	if (strcmp(vert1, vert2) == 0) {
        if(flag) {
            printf("ERROR: Same vertices\n");
            return 0;
        }
        else return 1;
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
                if(flag){
                    printf("ERROR: Double of edge");
                    return 0;
                }
                else return 1;
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
        if(flag){
            printf("ERROR: No such vertex");
            return 0;
        }
		else return 1;
	}
}
int graph_edge_del(Graph * graph, char * vert1, char * vert2) {
    Node * curr  = graph->list;
	Node * start = NULL;
	Node * end = NULL;

	if (strcmp(vert1, vert2) == 0){
        printf("ERROR: Same vertices\n");
        return 0;
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
                return 0;
            }

            prev = cur;
            cur  = cur->next;
        }

        printf("ERROR: no such edge");
        return 0;
	} else {
        printf("ERROR: no such vertex");
        return 0;
	}
}

int graph_graphviz(Graph * graph) {
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
int graph_adj(Graph * graph) {
	Node * curN = graph->list;

	while (curN) {

		Edge * curE = curN->list;

		if(!curE) printf("key: [ %s ], x: [ %lf] , y: [ %lf ]\n", curN->vert, curN->x, curN->y);

		while (curE) {
            printf("key: [ %s ], x: [ %lf] , y: [ %lf ]", curN->vert, curN->x, curN->y);
			printf(" -> key: [ %s ], weight: [ %d ]\n", curE->end->vert, curE->weight);

			curE = curE->next;
		}
		printf("\n");

		curN = curN->next;
	}
	return 0;
}

int graph_rnd(Graph * graph, int size) {
    srand(time(NULL));

    int len = 8;
    int num = 0;

    char * vert = rand_str(len);
    double x = (double)rand_int(100)/(double)(rand_int(10) + 1);
    double y = (double)rand_int(200)/(double)(rand_int(30) + 1);

    graph_node_add(graph, vert, x, y, num);

    free(vert);

    while (num < size) {
        vert = rand_str(len);
        x = (double)rand_int(100)/(double)(rand_int(10) + 1);
        y = (double)rand_int(200)/(double)(rand_int(30) + 1);

        if (!vert) {
            free(vert);
            graph_delete(graph);

            printf("ERROR: Memory is over\n");
            return 1;
        }
        num++;

        graph_node_add(graph, vert, x, y, num);

        free(vert);
    }

    int EdgeC = 0;
    int v1, v2;
    int k = ((double)(rand_int(80)+10)/100) * size * (size - 1)/ 2;

    while (EdgeC < k){
        do{
        v1 = rand_int(num);
        v2 = rand_int(num);
        } while(v1 == v2);

        Node * curr = graph->list;
        Node * V1 = NULL;
        Node * V2 = NULL;

        while((!V1 || !V2) && curr){
            if(curr->id == v1) V1 = curr;
            if(curr->id == v2) V2 = curr;
            curr = curr->next;
        }

        if (graph_edge_add(graph, V1->vert, V2->vert, rand_int(100) + 1, 0)) EdgeC--;
        EdgeC++;
    }
    return 0;
}

char * rand_str(int len) {
    char * str = (char *)calloc(len + 1, sizeof(char));
    if (!str) return NULL;

    char * cur = str;
    int n = 26;
    int d = 'a';
    for (int i = 0; i < len; i++) {
        int r = rand()%n;
        *cur = d + r;
        cur++;
    }
    *cur = '\0';

    return str;
}
int rand_int(int max) {
    return rand()%max;
}

int graph_test(int count) {
    Graph * graph = graph_new();

    srand(time(NULL));

    double t_addN = 0;
    double t_addE = 0;
    int len = 16;
    int num = 0;

    char * vert = rand_str(len);
    double x = (double)rand_int(100)/(double)(rand_int(10) + 1);
    double y = (double)rand_int(200)/(double)(rand_int(30) + 1);

    clock_t t = clock();
    graph_node_add(graph, vert, x, y, 0);

    t_addN += (double)(clock() - t)/CLOCKS_PER_SEC;

    free(vert);

    while (num < count) {
        vert = rand_str(len);
        x = (double)rand_int(100)/(double)(rand_int(10) + 1);
        y = (double)rand_int(200)/(double)(rand_int(30) + 1);

        if (!vert) {
            free(vert);

            graph_delete(graph);

            printf("ERROR: Memory is over\n");
            return 1;
        }

        num++;

        clock_t t = clock();
        graph_node_add(graph, vert, x, y, num);

        t_addN += (double)(clock() - t)/CLOCKS_PER_SEC;

        free(vert);
    }

    int EdgeC = 0;
    int v1, v2;
    int k = 0.5 * count * (count - 1)/ 2;

    while (EdgeC < k){
        do{
        v1 = rand_int(num);
        v2 = rand_int(num);
        } while(v1 == v2);

        Node * curr = graph->list;
        Node * V1 = NULL;
        Node * V2 = NULL;

        while((!V1 || !V2) && curr){
            if(curr->id == v1) V1 = curr;
            if(curr->id == v2) V2 = curr;
            curr = curr->next;
        }

        int weight =  rand_int(100) + 1;
        clock_t t = clock();

        if (!graph_edge_add(graph, V1->vert, V2->vert, weight, 0)){
             t_addE += (double)(clock() - t)/CLOCKS_PER_SEC;
             EdgeC++;
        }
    }

    printf("Number:\t%d\nLength:\t%d\n", num, len);
    printf("Vertex addition: average time\t%.10f\n", (t_addN == 0) ? 0 : t_addN/num);
    printf("Edge addition: average time\t%.10f\n", (t_addE == 0) ? 0 : t_addE/EdgeC);

    graph_delete(graph);

    return 0;
}

Queue * Qcreate() {
    Queue * queue = (Queue *)calloc(1, sizeof(Queue));

    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}
void Qpush(Queue * Q, Node * Gnode) {
	QNode * qnode = (QNode *)calloc(1, sizeof(QNode));

	qnode->node = Gnode;
	qnode->next = NULL;

	if(Q->head && Q->tail){
        Q->tail->next = qnode;
        Q->tail = qnode;
	} else {
	    Q->head = Q->tail = qnode;
	}
}
Node * Qpop(Queue * Q ){
	QNode * qnode = Q->head;
    Node * Gnode = NULL;

	if(Q->head){
        Gnode = qnode->node;
        Q->head = Q->head->next;
	}
	free(qnode);

	return Gnode;
}
void Qdelete(Queue * Q) {
    while(Q->head){
        Qpop(Q);
    }
    Q->head = Q->tail = NULL;
    free(Q);
    Q = NULL;
}

int graph_bfs(Graph * graph, char * V1, char * V2, int flag) {
    Node * temp = graph->list;
    Node * first = NULL;

    Node * nodes[graph->size];
    int vis[graph->size];
    int i = 0;

    while (temp) {
        if (!strcmp(temp->vert,V1)) first = temp;
        temp->id = i;
        vis[i] = 0;
        nodes[i] = NULL;
        temp = temp->next;
        i++;
    }

    if(!first && flag){
        printf("ERROR: No such vertices\n");
        return 0;
    }

	Queue * queue = Qcreate();

	vis[first->id] = 1;
	Qpush(queue, first);

    while (queue->head){
		first = Qpop(queue);
		Edge * edg = first->list;

		while (edg) {
            if (vis[edg->end->id] == 0) {
                vis[edg->end->id] = 1;
                nodes[edg->end->id] = first;
				Qpush(queue, edg->end);
            }

            if (!strcmp(edg->end->vert,V2)) {
                Qdelete(queue);

                if (flag) {
                    BFShelp(nodes, first->id);
                    printf("%s -> %s", first->vert, edg->end->vert);
                }
                return 0;
            }
            edg = edg->next;
		}
	}
	printf("No such path exist\n");
	return 0;
}
void BFShelp(Node * nodes[], int id) {
    Node * prev = nodes[id];
    if(!prev) return;
    BFShelp(nodes, prev->id);
    printf("%s -> ", prev->vert);
}

int graph_bf(Graph *graph, char * vert1, char * vert2, int flag) {
    Node * temp = graph->list;

    int i = 0;

    Node * source = NULL;
    Node * end = NULL;

	while (temp) {
        if (!strcmp(temp->vert,vert1)) source = temp;
        if (!strcmp(temp->vert,vert2)) end = temp;
        temp->id = i;
        temp = temp->next;
        i++;
    }

	int * dist  = (int *)calloc(graph->size, sizeof(int));
	Node ** prev = (Node **)calloc(graph->size, sizeof(Node *));

	for (i = 0; i < graph->size; i++) {
		dist[i] = INT_MAX;
		prev[i] = NULL;
	}

	if(!source || !end){
        if(flag) printf("ERROR: No such vertices\n");
        free(prev);
        free(dist);
        return 0;
	}

	dist[source->id] = 0;

	for (int i = 1; i <= graph->size; i++) {
		Node * curN = graph->list;
		while (curN) {
			int NId = curN->id;

			Edge * curE = curN->list;
			while (curE) {
				int EId = curE->end->id;
				int W  = curE->weight;

				if ((dist[NId] != INT_MAX) && (dist[EId] > dist[NId] + W)) {
					dist[EId] = dist[NId] + W;
					prev[EId] = curN;
				}

				curE = curE->next;
			}
			curN = curN->next;
		}
	}

	if (prev[end->id] == INT_MAX){
        if(flag) printf("WARNING: path not found\n");
        free(prev);
        free(dist);
        return 0;
	}

	if(flag){
        BFShelp(prev, end->id);
        printf("%s\n", end->vert);
	}

    free(prev);
    free(dist);
	return 0;
}

int graph_fw(Graph * graph, char * vert1, char * vert2, int flag) {
}
