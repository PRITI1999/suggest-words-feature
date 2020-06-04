#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include"suggest_feature.h"
#include"logger.h"
#define MAX_SUGGESTION 5

char words[MAX_SUGGESTION][50];
int row;
char stack[50];
int top;

//Print the retrieved words as per prefix
void print_words()
{
	int i;
	for(i = 0; i < row; i++)
	{
		logger(INFO_TAG, words[i]);
		printf("%s\n", words[i]);
	}
}

//To ensure any word exist in the triw with the given prefix
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
		stack[top++] = prefix[i];
		if(prefix[i+1] == '\0')
		{
			//end of prefix indicates the prefix was found in the trie, returns the end of prefix node
			return child;
		}
		root = child;
		i++;

	}
	return NULL;
}

//find words if any for the given prefix
void find_words(Node* root, char data)
{
	//to limit the number of suggestions
	if(row >= MAX_SUGGESTION )
	{
		return;
	}
	if(root)
	{
		//push the root data into the stack
		stack[top++] = data;
		//if a valid word is found the word in the stack is copied to the word list
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
		//Traverse the children of root to branch to the parts of trie that exists
		for(i = 0; i < 26; i++)
		{
			Node* child = root->children[i];
			if(!child)
			{
				continue;
			}
			find_words(child, i+97);
		}
		//pop the root data from the stack
		top--;
	}
}

//To do all the operations required to find suggestions
void autosuggestion(Node* root, char* prefix)
{
	//initialize top and row with 0 to ensure previous value do not incur for a new prefix
	top = 0;
	row = 0;
	char* temp = prefix;
	//Convert the prefix string to lowercase for maintaining uniformity
	for(; *temp; temp++)
	{
		*temp = tolower(*temp);
	}
	Node* child;
	if(root)
	{
		root = root_prefix(root, prefix);
		if(!root)
		{
			/*if no words existed in common-words.txt, the search moves to the words in all-words.txt
			 * this is to maintain a heirarchical structure of suggesting, the program tries to suggest
			 * common-words before moving to any word present first alphabetically*/
			file_name = "all-words.txt";
			root = init_word_trie();
			root = root_prefix(root, prefix);
			//If no words are found in all-words.txt show user no words exists for the prefix
			if(!root)
			{
				logger(INFO_TAG, "No suggestions available");
				printf("No suggestions available!\n");
				return;
			}
		}
		//To avoid duplicate character in the stack
		top--;
		find_words(root, stack[top]);
		char *log_info;
		strcpy(log_info, prefix);
		strcat(log_info, " is the input");
		logger(INFO_TAG, log_info);
		printf("The top words closest to %s in alphabetical order:\n", prefix);
		print_words();
	}
}

//Create a trie and return root
Node* init_word_trie()
{
	//initialize top and row with 0 to ensure no garbage or previous value incurs
	top = 0;
	row = 0;
	//Initialize the root
	Node* root = get_node();
	//Form the trie of words present in the file
	if(root)
	{
		insert_from_file(root, file_name);
		//return the root of trie
		return root;
	}
	logger(ERROR_TAG, "get_node() returned null, memory could not be allocated");
	printf("Uh-oh! Could not initialize trie. Try Again.");
	exit(1);
	return NULL;
}
