#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

/*
 * Because multiple keys will hash into each bucket,
 * the value struct (a node in a singly linked list)
 * contains the key, the value, the pair's frequency,
 * and a pointer to the next node. 
 */
typedef struct value{
	char * indexWord;
	char * valueWord;
	int frequency;
	struct value *next;
} value;

// Extensive printing
#define DEBUG 0

/*
 * LEN is used repeatedly when allocating space for a char array
 */ 
#define LEN 100
 /*
  * ARRAY_SIZE denotes the number of buckets to be used.
  */
#define ARRAY_SIZE 100

  /*
   * Minimum word repititions required for printing output
   * (< 2 will print all)
   */
#define MIN_FREQUENCY 2
/*
 * Regular expressions:
 * NAME_PATTERN: Any number of lower-case letters following any single 
 * uppercase letter; no non-alphabetic letters within name - ending with
 * a period is acceptable, though in this implementation the period is stripped.
 * Match examples: "Mrs.", "Lily".
 */
#define NAME_PATTERN "[A-Z][a-z]*$"
/*
 * SENTENCE_END: Any string of exclusively lower-case letters ending in a period.
 */
 #define SENTENCE_END "[a-z]\\.$"
/*
 * The only global variable is the hashtable struct,
 * an array of pointers to values.
 */
value **hashtable;

/*
 * Hashtable operations
 */
value** initTable();
value* initNode();
value* insertNode(char *indexWordIn, char *valueWordIn);
value* getHashRow(int index);
char* getName(value *val);
char* getValue(value *val);
int getFrequency(value *val);
value* getNextPtr(value *val);

int hash(char *strVal);

/*
 * Sort function headers
 */
int comparator(value *val1, value *val2);
value* listSort(value *list);

#endif