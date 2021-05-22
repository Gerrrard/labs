#include "graph.h"
#include "menu.h"

int main(int argc, const char** argv) {

	Graph * graph = graph_new();

	graph_node_add(graph, "a", 1, 1, 0);
	graph_node_add(graph, "b", 1, 1, 0);
	graph_node_add(graph, "c", 1, 1, 0);
	graph_node_add(graph, "d", 1, 1, 0);
	graph_node_add(graph, "e", 1, 1, 0);
	graph_node_add(graph, "f", 1, 1, 0);
	graph_node_add(graph, "g", 1, 1, 0);
	graph_node_add(graph, "h", 1, 1, 0);
	graph_node_add(graph, "i", 1, 1, 0);
	graph_edge_add(graph, "a", "b", 3, 0);
	graph_edge_add(graph, "a", "e", 3, 0);
	graph_edge_add(graph, "a", "g", 3, 0);
	graph_edge_add(graph, "b", "h", 3, 0);
	graph_edge_add(graph, "b", "c", 3, 0);
	graph_edge_add(graph, "c", "h", 3, 0);
	graph_edge_add(graph, "c", "i", 3, 0);
	graph_edge_add(graph, "e", "c", 3, 0);
	graph_edge_add(graph, "e", "f", 3, 0);
	graph_edge_add(graph, "e", "g", 3, 0);
	graph_edge_add(graph, "f", "a", 3, 0);
	graph_edge_add(graph, "i", "e", 3, 0);
	graph_edge_add(graph, "g", "c", 3, 0);
	graph_edge_add(graph, "h", "g", 3, 0);


	start(graph);

	graph_delete(graph);

	return 0;
}
