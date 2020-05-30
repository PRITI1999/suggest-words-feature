#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"suggest_feature.h"

char words[300000][50];
int row;
char stack[50];
int top;

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
	if(row > 4)
	{
		return;
	}
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
	/*for(; *prefix; prefix++)
	{
		*prefix = tolower(*prefix);
	}*/
	Node* child;
	if(root)
	{
		root = root_prefix(root, prefix);
		if(!root)
		{
			file_name = "all-words.txt";
			root = init_word_trie();
			root = root_prefix(root, prefix);
			if(!root)
			{
				printf("No suggestions available!");
				return;
			}
		}
		top--;
		find_words(root);
		printf("The top words closest to %s in alphabetical order:\n", prefix);
		print_words();
	}
}

Node* init_word_trie()
{
	top = 0;
	row = 0;
	Node* root = get_node();
	if(root)
	{
		insert_from_file(root, file_name);
		return root;
	}
	return NULL;
	printf("Uh-oh! Could not initialize trie. Try Again.");
	exit(1);
}
