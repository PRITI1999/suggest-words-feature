#include"trie.h"
#include<stdio.h>

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
	return 0;
}
