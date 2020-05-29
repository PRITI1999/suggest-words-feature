#include"trie.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
//#define words 16
#define TRUE 1
#define FALSE 0

char words[50][50];
int row = 0;
char stack[50];
int top = 0;

Node* get_node()
{
	Node* new_node = NULL;
	new_node = (Node*)malloc(sizeof(Node));
	if(new_node)
	{
		int i;
		new_node->isEnd = FALSE;
		new_node->data = '-';
		for(i = 0; i < CHAR_COUNT; i++)
		{
			new_node->children[i] = NULL;
		}
	}
	return new_node;
}

void lowercase(char *temp)
{
	for(; *temp; *temp++)
	{
		*temp = tolower(*temp);
	}
}

void insert(Node* root, char* key)
{
	lowercase(key);
	int index;
	if(root)
	{
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
	lowercase(key);
	if(root)
	{
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

void print_words()
{
	int i;
	for(i = 0; i < row; i++)
	{
		printf("%s\n", words[i]);
	}
}

Node* root_prefix(Node* root, char* prefix)
{
	int i = 0;
	Node* child;
	while(root)
	{
		child = root->children[prefix[i]-97];
		if(!child)
		{
			return NULL;
		}
		stack[top++] = child->data;
		if(prefix[i+1] == '\0')
		{
			return child;
		}
		root = child;
		i++;

	}
	return NULL;
}

void find_words(Node* root)
{
	if(root)
	{
		stack[top++] = root->data;
		if(root->isEnd == TRUE)
		{
			int i;
			for(i = 0; i < top; i++)
			{
				words[row][i] = stack[i];	
			}
			++row;
		}
		int i;
		for(i = 0; i < 26; i++)
		{
			Node* child = root->children[i];
			if(!child)
			{
				continue;
			}
			find_words(child);
		}
		top--;
	}
}

void autosuggestion(Node* root, char* prefix)
{
	top = 0;
	row = 0;
	lowercase(prefix);
	Node* child;
	if(root)
	{
		int i;
		root = root_prefix(root, prefix);
		if(!root)
		{
			printf("No suggestions available!");
			return;
		}
		top--;
		find_words(root);
		print_words();
	}
}

void list_valid_words(Node *root)
{
	top = 0;
	row = 0;
	find_words(root);
	print_words();
}

/*int main()
{
	int i;
	//char key[words][50] = {"light", "like"};
	char key[words][50] = {"LIfe","like","likely","lifeline", "likeness", "live","lively","line","light","lite","likelihood","and","andhadhoon","an","a","andhakanoon"};
	char not_key[2][50] ={"lige","kile"};
	char user_input[50];
	Node* root = get_node();
	for(i = 0; i < words; i++)
	{
		insert(root, key[i]);
	}
	printf("%d", search(root, key[0]));
	printf("%d", search(root, not_key[0]));
	printf("%d", search(root, not_key[1]));
	scanf("%s", user_input);
	autosuggestion(root, user_input);
	scanf("%s", user_input);
	autosuggestion(root, user_input);
	return 0;
}*/

