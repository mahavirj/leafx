/*
 * Feel Free To Re-distribute with credit to Author
 * Mahavir Jain <mahavirpj@gmail.com>
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct table {
	char *word;
	struct table *next;
} table_t;

//#define TABLE_SIZE (256)
#define TABLE_SIZE (256*256)

static table_t *nodes[TABLE_SIZE];

int hash(char *word)
{
	//return (word[0]) % TABLE_SIZE;
	return ((word[0] * 256) + word[1]) % TABLE_SIZE;
}

bool lookup_table(table_t *nodes[], char *word)
{
	bool found = false;
	int l_element = hash(word);

	table_t *node = nodes[l_element];

	while (node) {
		if (!strcmp(word, node->word)) {
			found = true;
			break;
		}
		node = node->next;
	}

	return found;
}

int create_hashtable(char *word)
{
	unsigned index = hash(word);

	if (lookup_table(nodes, word))
		return 0;

	table_t *node = (table_t *) malloc(sizeof(table_t));
	if (!node) {
		perror("malloc failed");
		return -1;
	}

	node->word = (char *) malloc(strlen(word) + 1);
	if (!node->word) {
		perror("malloc failed");
		return -1;
	}

	strcpy(node->word, word);
	node->next = nodes[index];
	nodes[index] = node;
	return 0;
}

void cleanup_hashtable(table_t *nodes[])
{
	int i;
	for (i = 0; i < TABLE_SIZE; i++) {
		table_t *node = nodes[i];
		while (node) {
			table_t *tmp = node;
			node = tmp->next;
			free(tmp->word);
			free(tmp);
		}
	}
}

int main(void)
{
	char word[256];
	int c;

	FILE *fp = fopen("wordlist", "r");
	if (!fp) {
		perror("failed to open file");
		return -1;
	}

	do {
		c = fscanf(fp, "%s", word);
		if (word[0] != '\0')
			create_hashtable(word);
	} while (c != EOF);
	rewind(fp);

	int found = 0;
	do {
		c = fscanf(fp, "%s", word);
		if (lookup_table(nodes, word) == true)
			found++;
	} while (c != EOF);

	int ret = lookup_table(nodes, "woodgrain");
	printf("MJ return val is %d %d\n", found, ret);
	cleanup_hashtable(nodes);
	fclose(fp);

	return 0;
}
