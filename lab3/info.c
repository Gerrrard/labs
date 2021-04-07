#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "info.h"

Info * info_new(Info info) {
	Info *inf_new = (Info *)calloc(1, sizeof(Info));
	char *str = (char *)calloc(strlen(info.str) + 1, sizeof(char));

	strcpy(str, info.str);
	inf_new->str = str;

	return inf_new;
}

void info_del(Info *info) {
	free(info->str);
	free(info);
}

void info_print(Info *info) {
	if (!info) printf("-NULL-");
	else printf("-%s-", info->str);
}
