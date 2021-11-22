#include "stdio.h"
#include "string.h"

typedef struct _node {

	char str[100];
	int  count;
	int  inited;
}Node_t;

#define LIST_LENGTH 8

char *string = "Dog Cat Dog Cat Dog Cat Cat Dog test Dog test Cat subject test subject goD taC goD";
Node_t array[100][LIST_LENGTH];
int bitmap [100];

int compare_and_add (int hash, char *word, int len) {
	int iter = 0;
	int free = -1;

	for (iter = 0; iter < LIST_LENGTH; iter ++) {
		if (array[hash][iter].inited) {
		    if(!memcmp(array[hash][iter].str, word, len)) {
			array[hash][iter].count ++;
			return 0;
		    }
		} else {
			if (free == -1) {
				free = iter;
			}
		}
	}

	if (free == -1) {
		return -1;
	}

	strncpy (array[hash][free].str, word, len);
	array[hash][free].str[len] = '\0';
	array[hash][free].count = 1;
	array[hash][free].inited = 1;
	bitmap[hash] = 1;
	return 0;
}

void main() {
	char *tmp = string;
	char word[100];
	int hash = 0;
	int len = 0;
	int i = 0;
	int list = 0;

	memset (word, 0, sizeof(word));
	while (1) {
		if (*tmp != ' ' &&
		    *tmp != '\0') {
			word[len++] = *tmp;
			hash += (int)(*tmp);
		} else {
			hash = hash % 100;
			compare_and_add (hash, word, len);
			hash = 0;
			len = 0;
			memset (word, 0, sizeof(word));
		}

		if (*tmp == '\0') {
			break;
		}
		tmp ++;
	}

	while (i++ < 100) {


		if (bitmap[i] == 0) {
		    continue;
		}

		for (list = 0; list < LIST_LENGTH; list ++) {
			if (array[i][list].inited) {
				printf (":%d Str: %s count: %d \r\n", i, array[i][list].str,array[i][list].count);
			}
		}
	}
	return;
}
