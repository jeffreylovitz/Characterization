#include <stdio.h>
#include <stdlib.h>

#define LEN 100
#define NUM_ENTRIES 100

typedef struct value_struct{
	char * indexWord;
	char * valueWord;
	int frequency;
} value;

//int endsWith(char *in);
value** initTable();

int main(){
	FILE *input = fopen("input.txt", "r");
	char *line = (char *)malloc(LEN * sizeof(char));

	int i;
	for(i = 0; i < 100; i++){
		fscanf(input, "%s", line);
		//printf("%s\n", line);

	}
	initTable();
	fclose(input);
	return 0;
}

value** initTable(){
	value **table = (value **)malloc(NUM_ENTRIES * sizeof(value *));
	return table;

}