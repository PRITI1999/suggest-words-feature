#ifndef TRIE
#define CHAR_COUNT 26
#define TRUE 1
#define FALSE 0
typedef struct trie_node
{
	struct trie_node *children[CHAR_COUNT];
	short isEnd;	
} Node;
Node* get_node();
void insert(Node*, char[]);
short search(Node*, char[]);
void insert_from_file(Node*, char*);
#endif
