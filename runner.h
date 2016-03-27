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
/*
 * Regular expression:
 * Any number of lower-case letters following any single uppercase letter;
 * no non-alphabetic letters.
 * Modify to any word at least
 * 2 letters long, capitalized, optional period (Mr. / Mrs/).
 */
#define NAME_PATTERN "[A-Z][a-z]*$"

value **hashtable;

value** initTable();
value* initNode();
value* insertNode(char *indexWordIn, char *valueWordIn);
value* getHashRow(int index);
char* getName(value *val);
char* getValue(value *val);
int getFrequency(value *val);
value* getNextPtr(value *val);

int hash(char *strVal);

#endif