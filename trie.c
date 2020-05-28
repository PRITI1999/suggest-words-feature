#include"trie.h"
#include<stdio.h>
#include<stdlib.h>
Node* get_node()
{
	Node* new_node = NULL;
	new_node = (Node*)malloc(sizeof(Node));
	if(new_node)
	{
		int i;
		new_node->isEnd = FALSE;
		new_node->data = '\0';
		for(i = 0; i < CHAR_COUNT; i++)
		{
			new_node->children[i] = NULL;
		}
	}
	return new_node;
}

char lowercase(char c)
{
	if(c < 97)
	{
		c = c + 32; 
	}
	return c;
}

void insert(Node* root, char* key)
{
	int index;
	if(root)
	{
		key[0] = lowercase(key[0]);
		Node** child; 
		child = &(root->children[key[0] - 97]);
		if(!(*child))
		{
			
			(*child) = get_node();
			(*child)->data = key[0];
		       		
		}
		if(key[1] == '\0')
		{
			(*child)->isEnd = TRUE;
			return;	
		}
		insert((*child), &key[1]);	
	}
}

short search(Node* root, char* key)
{
	if(root)
	{
		key[0] = lowercase(key[0]);
		Node* child; 
		child = root->children[key[0] - 97];
		if(!child)
		{
			return FALSE;
		}
		if(key[1] == '\0')
		{
			return child->isEnd;
		}
		return TRUE && search(child, key+1);
	}
	return FALSE;
}

/*int main()
{
	char key[2][50] = {"life","like"};
	char not_key[2][50] ={"lige","kile"};
	Node* root = get_node();
	insert(root, key[0]);
	insert(root, key[1]);
	printf("%d", search(root, key[0]));
	printf("%d", search(root, not_key[0]));
	printf("%d", search(root, not_key[1]));
	return 0;
}*/

