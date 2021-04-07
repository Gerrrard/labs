#ifndef INFO
#define INFO

typedef struct Info{
	char *str;
} Info;

Info * info_new(Info info);
void info_del(Info *info);
void info_print(const Info *info);

#endif
