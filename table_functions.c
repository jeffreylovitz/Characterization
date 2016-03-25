#include "runner.h"
#include <stdio.h>
#include <stdlib.h>

value** initTable(){
	value **table = (value **)malloc(ARRAY_SIZE * sizeof(value*));
	int i;
	for(i = 0; i < ARRAY_SIZE; i++){
		table[i] = initNode();
	}
	return table;

}

/*
 * Empty constructor
 */
value* initNode(){
	value *v = (value *)malloc(sizeof(value));
	v->indexWord = NULL;
	v->valueWord = NULL;
	v->frequency = 0;
	v->next = NULL;
	return v;
}

/*
 * Defined constructor
 */
value* insertNode(char *indexWordIn, char *valueWordIn){
	int i, done = 0;
	value *buildNode;
	i = hash(indexWordIn);
	value *currentNode = hashtable[i];
	while(currentNode != NULL){
		if(currentNode->valueWord == valueWordIn){
			currentNode->frequency++;
			buildNode = currentNode;
			done = 1;
			break;
		}
		currentNode = currentNode->next;
	}
	if(!done){
		buildNode = (value *)malloc(sizeof(value));
		currentNode = buildNode;
		buildNode->indexWord = indexWordIn;
		buildNode->valueWord = valueWordIn;
		buildNode->frequency = 1;
		buildNode->next = NULL;
	}
	return buildNode;
}

/*
 * Hashing function:
 * Takes the name string, sums its ASCII values,
 * multiplies by 31 then takes the modulo
 * to create an array index value.
 */
 int hash(char *strVal){
 	int sum = 0;
 	char current;
 	while((current = *strVal++) != '\0'){
 		sum += (int)current;
 	}
 	sum *= 31;
 	sum = sum % ARRAY_SIZE;
 	return sum;
 }