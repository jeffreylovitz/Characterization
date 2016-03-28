#include "runner.h"


int main(int argc, char *argv[]){
	FILE *input;
	/*
	 * The user may pass the filename of the input corpus
	 * as an argument to the program.
	 */
	if(argc > 1){
		if(!(input = fopen(argv[1], "r"))){
			// Minor error-checking
			printf("%s is not a valid input file.\n", argv[1]);
			return 1;
		}
	}
	else{
		// Program defaults to "input.txt" if run without arguments
		input = fopen("input.txt", "r");
	}
	int err = 0;
	/*
	 * LEN is defined in "runner.h".
	 */
	char *word1 = (char *)malloc(LEN * sizeof(char));
	char *word2 = (char *)malloc(LEN * sizeof(char));
	char *name = (char *)malloc(LEN * sizeof(char));


	/*
	 * In table_functions.c, this call returns a
	 * pointer to an array of zero-initialized nodes.
	 */
	hashtable = initTable();

	// Regex compilation
	regex_t *nameRegex = (regex_t *)malloc(sizeof(regex_t));
	if((err = regcomp(nameRegex, NAME_PATTERN, 0)) != 0){
		printf("Error compiling NAME_PATTERN regular expression: error code %d.\n", err);
		return 1;
	}

	regex_t *sentenceEnd = (regex_t *)malloc(sizeof(regex_t));
	if((err = regcomp(sentenceEnd, SENTENCE_END, 0)) != 0){
		printf("Error compiling SENTENCE_END regular expression: error code %d.\n", err);
		return 1;
	}

	int nameflag = 0;
	/*
	 * The input is read 2 words at a time
	 */
	while(fscanf(input, "%s %s", word1, word2) == 2){
		/*
		 * If both match the "nameRegex" pattern, the strings
		 * are concatenated to be used as a key.
		 */
		if(!(regexec(nameRegex, word1, 0, NULL, REG_EXTENDED)) && !(regexec(nameRegex, word2, 0, NULL, REG_EXTENDED))){
			if(DEBUG){printf("name 1: %s\t2: %s\n", word1, word2);}
			nameflag = 1;
			strcpy(name, word1);
			strcat(name, " ");
			strcat(name, word2);
		}
		/*
		 * If a name has been found in this sentence,
		 * two nodes for the two current words are added.
		 */
		else if(nameflag){
			if(DEBUG){printf("inserting nodes %s and %s\n", word1, word2);}
			
			if(insertNode(name, word1)){
				printf("Error inserting key-value pair %s: %s.\n", name, word1);
			}
			if(insertNode(name, word2)){
				printf("Error inserting key-value pair %s: %s.\n", name, word2);
			}
		}

		// Sentence ends reset the name flag
		if(!(regexec(sentenceEnd, word1, 0, NULL, REG_EXTENDED)) || !(regexec(sentenceEnd, word2, 0, NULL, REG_EXTENDED))){
			nameflag = 0;
		}
	}
	fclose(input);

	int i;
	value *valPtr;
	char *nameWord = NULL;

	/*
	 * The output will be printed both to file and
	 * (in truncated form) in the terminal
	 */
	FILE *output = fopen("output.txt", "w");

	/*
	 * All values associated with each key are sorted
	 * using mergesort (on value frequency) 
	 */
	
	value *head = initNode();
	value *tail = initNode();
	head->indexWord = "initial value";

	for(i = 0; i < ARRAY_SIZE; i++){
		// The array called hashtable is iterated over sequentially
		valPtr = getHashRow(i);
		if(DEBUG){printf("row %d\n", i);}
		// Each linked list is traversed
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
					// MIN_FREQUENCY defined in "runner.h"
					if(getFrequency(head) > MIN_FREQUENCY){
						// Print to terminal
						printf("%s\t", nameWord);
						printf("%s\t", getValue(head));
						printf("%d\n", getFrequency(head));
						// Print to "output.txt"
						fprintf(output, "%s\t", nameWord);
						fprintf(output, "%s\t", getValue(head));
						fprintf(output, "%d\n", getFrequency(head));
					}
				}
				head = valPtr;
			}
			tail = valPtr;
		}
	}
	// err should always be 0
	return err;
}

