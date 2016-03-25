#ifndef HEADER
#define HEADER

typedef struct value{
	char * indexWord;
	char * valueWord;
	int frequency;
	struct value *next;
} value;

#define LEN 100
#define ARRAY_SIZE 100

value **hashtable;

value** initTable();
value* initNode();
value* insertNode(char *indexWordIn, char *valueWordIn);

int hash(char *strVal);

#endif