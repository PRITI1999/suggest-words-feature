#ifndef TRIE
#define CHAR_COUNT 26
#define TRUE 1
#define FALSE 0
typedef struct trie_node
{
	struct trie_node *children[CHAR_COUNT];
	char data;
	short isEnd;	
} Node;
Node* get_node();
void insert(Node*, char[]);
short search(Node*, char[]);
#endif
