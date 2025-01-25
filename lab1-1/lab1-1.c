#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

unsigned int power(const unsigned int num, const int power){
	unsigned int result = 1;
	for (int i = 0; i < power; ++i){
		result *= num;
	}
	return result;
}

unsigned int getHash(char *ptr, const int len){
	unsigned int resultHash = 0;
	for (int i = 0; i < len; ++i){
		if (ptr[i] < 0){	// if there are Russian letters
			resultHash += (ptr[i] % 3 + 4) % 3 * power(3, i);
		} else 
			resultHash += ptr[i] % 3 * power(3, i);		
	}
	return resultHash;
}


int main(){
	char pattern[MAX_SIZE];
	char line[MAX_SIZE];

	if (fgets(pattern, sizeof(pattern), stdin) == NULL)
		return 0;
	
	for (int i = 0; i < MAX_SIZE; ++i){
		if (pattern[i] == '\n'){
			pattern[i] = '\0';
			break;
		}
	}
	int lenPattern = strlen(pattern);
	unsigned int hashPattern = getHash(pattern, lenPattern);
	printf("%u", hashPattern);

	if (hashPattern == 0){
		printf("0");
		return 0;
	}

	int counter = 1;
	while (fgets(line, MAX_SIZE, stdin) != NULL){
		for (int i = 0; i < MAX_SIZE; ++i){
			if (line[i] == '\n'){
				line[i] = '\0';
				break;
			}
		}
		int lenline = strlen(line);
		
		if (lenPattern > lenline){
			counter += lenline + 1;
			continue;
		}
		for (int i = 0; i < lenline - lenPattern + 1; ++i){
			if (hashPattern == getHash(&line[i], lenPattern)){
				printf(" %i", counter + i);
				if (pattern[0] == line[i]){
					for (int j = 1; j < lenPattern; ++j){
						printf(" %i", i + j	+ counter);
					}
				}
			}
		}
		counter += lenline + 1;
	}
	
	return 0;	
}
