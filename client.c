#include<stdio.h>
#include "trie.h"

int main()
{
	int i;
	char keys[4][50] = {"hello","hell","yellow","elbow"};
	Node* root = get_node();
	for(i = 0; i < 4; i++)
	{
		insert(root, keys[i]);
	}
	for(i = 0; i < 4; i++)
	{
		printf("%d",search(root, keys[i]));
	}
	char user_input[50];
	scanf("%s", user_input);
	autosuggestion(root, user_input);
	list_valid_words(root);
	return 0;
}
