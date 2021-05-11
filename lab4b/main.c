#include <stdlib.h>

#include "tree.h"
#include "menu.h"

int main(int argc, const char** argv) {
	Tree * tree = tree_new();

	//tree_load(tree, "tree.txt");

    tree_add(tree, "a", 5, 1, " e");
    tree_add(tree, "m", 5, 1, " e");
    tree_add(tree, "n", 5, 1, " e");
	tree_add(tree, "o", 1, 5, " a");
	tree_add(tree, "a", 5, 1, " e");
	tree_add(tree, "a", 5, 1, " e");
    tree_add(tree, "t", 5, 1, " e");
	tree_add(tree, "u", 1, 5, " a");
    tree_add(tree, "v", 2, 4, " b");
    tree_add(tree, "w", 3, 3, " c");
    tree_add(tree, "p", 2, 4, " b");
    tree_add(tree, "q", 3, 3, " c");
    tree_add(tree, "aq", 5, 1, " e");
    tree_add(tree, "mq", 5, 1, " e");
    tree_add(tree, "agrw", 5, 1, " e");
    tree_add(tree, "mwf", 5, 1, " e");
    tree_add(tree, "mf", 5, 1, " e");
    tree_add(tree, "c", 5, 1, " e");
    tree_add(tree, "d", 5, 1, " e");
    tree_add(tree, "i", 5, 1, " e");
    tree_add(tree, "j", 5, 1, " e");
    tree_add(tree, "k", 5, 1, " e");
    tree_add(tree, "l", 5, 1, " e");
	tree_add(tree, "e", 1, 5, " a");
    tree_add(tree, "f", 2, 4, " b");
    tree_add(tree, "g", 3, 3, " c");
    tree_add(tree, "b", 5, 1, " e");
    tree_add(tree, "h", 4, 2, " d");
    tree_add(tree, "r", 5, 1, " e");
    tree_add(tree, "s", 4, 2, " d");
    tree_add(tree, "x", 5, 1, " e");
    tree_add(tree, "y", 4, 2, " d");
    tree_add(tree, "z", 5, 1, " e");
    tree_add(tree, "s", 4, 2, " d");

	start(tree);

	return 0;
}
