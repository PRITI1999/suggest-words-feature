#include<stdio.h>
#include<string.h>
#include "suggest_feature.h"

int main(int argc, char* argv[])
{
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
		printf("[ERROR]prefix argument missing!\n");
	}
	return 0;
}
