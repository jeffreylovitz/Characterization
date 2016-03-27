#include "runner.h"
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int main(){
	int err = 0;
	FILE *input = fopen("input.txt", "r");
	char *word1 = (char *)malloc(LEN * sizeof(char));
	char *word2 = (char *)malloc(LEN * sizeof(char));

	hashtable = initTable();

	regex_t *nameRegex = (regex_t *)malloc(sizeof(regex_t));
	if((err = regcomp(nameRegex, NAME_PATTERN, 0)) != 0){
		printf("Error compiling regular expression: error code %d.\n", err);
		return 1;
	}

	int nameflag = 0;
	char *name = (char *)malloc(LEN * sizeof(char));

	while(fscanf(input, "%s %s", word1, word2) == 2){
		//printf("token 1: %s\t token 2:%s\n", word1, word2);
		/*
		if(err = perror()){
			return 1;
		}
		*/

		if(!(regexec(nameRegex, word1, 0, NULL, 0)) && !(regexec(nameRegex, word2, 0, NULL, 0))){
			printf("name 1: %s\t2: %s\n", word1, word2);
			nameflag = 1;
			strcpy(name, word1);
			strcat(name, " ");
			strcat(name, word2);
		}
	//while(fgets(word1, LEN, input) != NULL){
	//while(fscanf(input, "%s", word1) == 1){
		printf("%s\n", word1);
		if(nameflag++){
			if(insertNode(name, word1)){
				printf("Error inserting key-value pair %s: %s.\n", name, word1);
			}
		}
		if(nameflag == 3){
			nameflag = 0;
		}
		//printf("%s\n", test->indexWord);
	}
	fclose(input);
	// Free stuff here

	int i;
	value *valPtr;
	char *nameWord = NULL;
	char *nonNameWord = NULL;
	for(i = 0; i < ARRAY_SIZE; i++){
		//printf("%d\n", i);
		// The array called hashtable is iterated over sequentially
		valPtr = getHashRow(i);
		printf("row %d\n", i);
		// Each linked list 
		while((valPtr = getNextPtr(valPtr)) != NULL){
			nameWord = getName(valPtr);
			//word1 = "qe";
			if(nameWord){
				printf("%s\t", nameWord);
			}
			nonNameWord = getValue(valPtr);
			if(nonNameWord){
				printf("%s\t", nonNameWord);
			}
			printf("%d\n", getFrequency(valPtr));
		}
	}


	return err;
}

