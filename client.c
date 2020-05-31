#include<stdio.h>
#include<string.h>
#include "suggest_feature.h"
#include"logger.h"

int main(int argc, char* argv[])
{
	init_log();
	if(argc > 1)
	{
		file_name = "common-words.txt";
		Node* root = init_word_trie();
		argv++;
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
	cleanup_log();
	return 0;
}
