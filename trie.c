#include"trie.h"
#include"logger.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

//To create a new trie node and allocate memory to it
Node* get_node()
{
	Node* new_node = NULL;
	new_node = (Node*)malloc(sizeof(Node)); //allocation of memory 
	//Initialize new node fields with default values
	if(new_node)
	{
		int i;
		new_node->isEnd = FALSE;
		for(i = 0; i < CHAR_COUNT; i++)
		{
			new_node->children[i] = NULL;
		}
	}
	//return the created new node or null if it could'nt be created
	return new_node;
}

//To convert a string to lowercase
void lowercase(char *temp)
{
	//Traverse through the string and convert each charcater to lowercase
	for(; *temp; *temp++)
	{
		*temp = tolower(*temp);
	}
}

//To insert a new key into the trie
void insert(Node* root, char* key)
{
	//convert key to lowercase for maintaining uniformity
	lowercase(key);
	int index;
	if(root)
	{
		Node** child;
		child = &(root->children[key[0] - 97]);
		//If child does not exist, then create a new node
		if(!(*child))
		{

			(*child) = get_node();

		}
		//If end of key, initialize the last character node's isEnd to 1 or TRUE to mark a valid word
		if(key[1] == '\0')
		{
			(*child)->isEnd = TRUE;
			return;
		}
		//recurse to insert each character in order of key into trie
		insert((*child), &key[1]);
	}
}

//To search if a word or key entered is a valid word or not
short search(Node* root, char* key)
{
	//Convert key to lowercase for maintaining uniformity
	lowercase(key);
	if(root)
	{
		Node* child;
		child = root->children[key[0] - 97];
		if(!child)
		{
			return FALSE;
		}
		/*if end of key, then return isEnd as if isEnd is 1 the key was a valid otherwise 0 similar to
		 * what is required to return for this method*/
		if(key[1] == '\0')
		{
			return child->isEnd;
		}
		//If current child existed then recurse for the rest of key
		return TRUE && search(child, key+1);
	}
	return FALSE;
}

//Insert words from a file into a trie
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
		//Traverse the file and extract words till end of file is reached
		while(feof(fp) == 0)
		{
			char word[50];
			fscanf(fp, "%[^' '|| ^\n]%*c", word);
			insert(root, word);
		}
		//close the file
		fclose(fp);
	}
}
