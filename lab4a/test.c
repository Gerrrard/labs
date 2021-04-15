#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

#include "tree.h"
#include "test.h"

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

int test(int count) {
    Tree * tree = tree_new();

    srand(time(NULL));

    int * keys = (int *)calloc(count, sizeof(int));
    if (!keys) return 1;

    double t_add = 0, t_find = 0, t_remove = 0;
    int len = 10 * (int)(2 * log(count) / log(26.0));
    int num = 0;

    while (num < count) {
        int key = rand_int(20);
        char * info1 = rand_str(len);
        char * info2 = rand_str(len);

        if (!info1 || !info2) {
            free(info1);
            free(info2);
            free(keys);

            tree_delete(tree->root);

            printf("ERROR: Memory is over\n");
            return 1;
        }

        keys[num] = key;
        num++;

        clock_t t = clock();
        tree_add(tree, info1, info2, key);

        t_add += (double)(clock() - t)/CLOCKS_PER_SEC;

        free(info1);
        free(info2);
    }
    t_add /= count;

    for (int i = 0; i < count; i++) {
        clock_t t = clock();
        tree_find(tree, keys[i], 0);
        t_find += (double)(clock() - t)/CLOCKS_PER_SEC;
    }
    t_find /= count;

    for (int i = 0; i < count; i++) {
        clock_t t = clock();
        tree_remove(tree, keys[i], -1);
        t_remove += (double)(clock() - t)/CLOCKS_PER_SEC;
    }
    t_remove /= count;

    free(keys);

    printf("Number:\t%d\nLength:\t%d\n", count, len);
    printf("Addition: average time\t%.10f\n", t_add);
    printf("Finding: average time\t%.10f\n", t_find);
    printf("Removing: average time\t%.10f\n", t_remove);

    tree_delete(tree->root);

    return 0;
}
