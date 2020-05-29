#ifndef TRIE
#define CHAR_COUNT 26
typedef struct trie_node
{
	struct trie_node *children[CHAR_COUNT];
	char data;
	short isEnd;	
} Node;
Node* get_node();
void insert(Node*, char[]);
short search(Node*, char[]);
void autosuggestion(Node*, char[]);
void list_valid_words(Node*);
#endif
