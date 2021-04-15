#include <stdlib.h>

#include "tree.h"
#include "menu.h"

int main(int argc, const char** argv) {
	Tree * tree = tree_new();

	tree_add(tree, "1 a", "2 a", 1);
    tree_add(tree, "1 b", "2 b", 1);
    tree_add(tree, "1 c", "2 c", 2);
    tree_add(tree, "1 d", "2 d", 2);
    tree_add(tree, "1 e", "2 e", 2);
    tree_add(tree, "1 f", "2 f", 3);
    tree_add(tree, "1 g", "2 g", 4);
    tree_add(tree, "1 h", "2 h", 5);
    tree_add(tree, "1 i", "2 i", 6);
    tree_add(tree, "1 j", "2 j", 7);
    tree_add(tree, "1 k", "2 k", 1);
    tree_add(tree, "1 l", "2 l", 10);

	start(tree);

	tree_delete(tree->root);
	free(tree);

	return 0;
}
