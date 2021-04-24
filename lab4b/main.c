#include <stdlib.h>

#include "tree.h"
#include "menu.h"

int main(int argc, const char** argv) {
	Tree * tree = tree_new();

	//tree_load(tree, "tree.txt");

	/*tree_add(tree, "key1", 1, 5, " a");
    tree_add(tree, "key2", 2, 4, " b");
    tree_add(tree, "key2", 3, 3, " c");
    tree_add(tree, "key3", 4, 2, " d");
    tree_add(tree, "key4", 5, 1, " e");*/

	start(tree);

	tree_delete(tree->root);
	free(tree);

	return 0;
}
