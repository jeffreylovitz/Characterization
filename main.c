#include "runner.h"


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

	/*
	 * To use mergesort on our word lists, we must
	 * separate the words associated with each name.
	 * We'll allocate space for 500 distinct characters,
	 * as only one pointer is required for each (low overhead).
	 */
	//value **allCharacters = (value **)malloc(500 * sizeof(value*));
	
	value *head = initNode();
	value *tail = initNode();
	head->indexWord = "initial value";
	// tail->next = NULL;
	for(i = 0; i < ARRAY_SIZE; i++){
		//printf("%d\n", i);
		// The array called hashtable is iterated over sequentially
		valPtr = getHashRow(i);
		//printf("row %d\n", i);
		// Each linked list 
		while((valPtr = getNextPtr(valPtr)) != NULL){

			nameWord = getName(valPtr);

			/*
			 * The following will execute when the stored
			 * name no longer matches the current element's key.
			 */
			if(strcmp(nameWord, head->indexWord)){
				tail->next = NULL;
				head = listSort(head);
				while(((head = getNextPtr(head)) != NULL)){
					printf("%s\t", nameWord);
					printf("%s\t", getValue(head));
					printf("%d\n", getFrequency(head));
				}
				head = valPtr;
			}
			tail = valPtr;
		}
	}

	return err;
}

