#ifndef __EXPR2STR__H
#define __EXPR2STR__H

//element of the operation-stack
typedef struct member
{
	char operation;
	struct member* nextmem;
} structure;

char* expr2str(char*);
char Pop(structure**);
structure* Push(structure*, char);
int Priority(char);

#endif
