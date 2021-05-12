#include "graph.h"
#include "menu.h"

int main(int argc, const char** argv) {

	Graph * graph = graph_new();

    graph_node_add(graph, "1", 1, 1);
    graph_node_add(graph, "2", 2, 2);
    graph_node_add(graph, "3", 3, 3);
    graph_node_add(graph, "4", 4, 4);
    graph_node_add(graph, "5", 5, 5);
    graph_node_add(graph, "6", 6, 6);
    graph_node_add(graph, "7", 7, 7);
    graph_edge_add(graph, "1", "2", 3);
    graph_edge_add(graph, "1", "4", 5);
    graph_edge_add(graph, "2", "4", 6);
    graph_edge_add(graph, "3", "1", 4);
    graph_edge_add(graph, "6", "7", 13);
    graph_edge_add(graph, "7", "6", 31);

	start(graph);

	graph_delete(graph);

	return 0;
}
