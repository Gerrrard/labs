#ifndef	TREE_H
#define TREE_H

#define N 10

typedef struct Node{
    char * key;
    int int1;
    int int2;
    char * str;
    int version;
    struct Node * left;
    struct Node * right;
    struct Node * parent;
    struct Node * next;
    int len;
} Node;

typedef struct Tree{
    Node * root;
} Tree;

Tree * tree_new();
Node * node_new(char * key, int version, int len, int int1, int int2, char * str, Node * left, Node * right, Node * parent);
int n_side(Node * ptr);
int n_size(Node * ptr);

void tree_delete(Node * root);

Node * tree_find_min(Node * ptr);
Node * tree_find_max(Node * ptr);
Node * tree_find_prev(Node * ptr);
Node * tree_find_next(Node * ptr);

Node * tree_find(Tree * tree, char * key, int version);

void next_print(Node * ptr);
void next_delete(Node * ptr);

void tree_print(Node * ptr);
void tree_graphviz(Node * ptr);
void tree_show(Node * ptr, int level);
void tree_print_str(Tree * tree, char * substr);

int node_add(Tree * tree, char * key, int int1, int int2, char * str);
Node * tree_to_list1(Node * ptr);
Node * list_to_node1(Node * ptr, int ind);
Node * tree_rebuild1(Node * ptr, Node * par, int size);

void tree_rebuild2(Tree * tree, Node * unbal, Node * unbal_par);
int tree_to_arr(Node * ptr, Node ** arr, int ind);
Node * arr_to_tree(Node ** arr, int ind, int size);

int tree_add(Tree * tree, char * key, int int1, int int2, char * str);

void tree_remove(Tree * tree, char * key, int version);  //-1 for oldest

int tree_load(Tree * tree, char *filep);

char * rand_str(int len);
int rand_int(int max);
int tree_test(int count);

#endif
