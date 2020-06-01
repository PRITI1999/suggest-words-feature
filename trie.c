#include"trie.h"
#include"logger.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

Node* get_node()
{
	Node* new_node = NULL;
	new_node = (Node*)malloc(sizeof(Node));
	if(new_node)
	{
		int i;
		new_node->isEnd = FALSE;
		//new_node->data = '-';
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
			//(*child)->data = key[0];

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

void insert_from_file(Node* root, char* file_address)
{
	if(root)
	{
		FILE *fp = fopen(file_address, "r");
		if(fp == NULL)
		{
			logger(ERROR_TAG, "Words file could not be opened!");
			printf("Error! Could not find dictionary file\n");
			exit(1);
		}
		while(feof(fp) == 0)
		{
			char word[50];
			fscanf(fp, "%[^' '|| ^\n]%*c", word);
			insert(root, word);
		}
		fclose(fp);
	}
}

/*int main()
{
	Node* root = get_node();
	insert_from_file(root, "3000-words.txt");
	//list_valid_words(root);
	char user_input[50];
	scanf("%s", user_input);
	autosuggestion(root, user_input);
	return 0;
}*/
