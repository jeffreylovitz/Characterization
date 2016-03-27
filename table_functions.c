#include "runner.h"

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
	//printf("inserting %s: %s\n", indexWordIn, valueWordIn);
	int i, done = 0;
	value *buildNode;
	i = hash(indexWordIn);
	value *currentNode = hashtable[i];
	value *prev;
	while(currentNode != NULL){
		if((currentNode->valueWord != NULL) &&!(strcmp(currentNode->valueWord, valueWordIn))){
			currentNode->frequency++;
			buildNode = currentNode;
			done = 1;
			break;
		}
		prev = currentNode;
		currentNode = currentNode->next;
	}
	if(!done){
		buildNode = (value *)malloc(sizeof(value));
		buildNode->indexWord = (char *)malloc(LEN * sizeof(char));
		buildNode->valueWord = (char *)malloc(LEN * sizeof(char));
		prev->next = buildNode;
		strcpy(buildNode->indexWord, indexWordIn);
		strcpy(buildNode->valueWord, valueWordIn);
		buildNode->frequency = 1;
		buildNode->next = NULL;
	}
	return 0;
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

 value* getHashRow(int index){
 	return hashtable[index];
 }

 char* getName(value *val){
 	//char *test = (char *)malloc(100 * sizeof(char));
 	//strcpy(testName, val->indexWord);
 	return val->indexWord;
 }

char* getValue(value *val){
	return val->valueWord;
}

value* getNextPtr(value *val){
	return val->next;
}

int getFrequency(value *val){
	return val->frequency;
}