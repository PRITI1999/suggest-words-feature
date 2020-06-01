#include<stdio.h>
#include<string.h>
#include "suggest_feature.h"
#include"logger.h"

int main(int argc, char* argv[])
{
	//open or create the log file
	init_log();
	//Check if atleast one prefix was provided
	if(argc > 1)
	{
		file_name = "common-words.txt"; //filename to insert words to trie
		argv++; //to send 2nd argument onwards for suggestion 
		Node* root = init_word_trie();
		//Loop through the arguments and provide suggestions
		for(; *argv; argv++)
		{
			autosuggestion(root, *argv);
		}
	}
	else
	{
		logger(ERROR_TAG, "prefix argument missing!");
		printf("prefix argument missing!\n");
	}
	//Closing the lop file
	cleanup_log();
	return 0;
}
