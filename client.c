#include<stdio.h>
#include<string.h>
#include "trie.h"

int main()
{
	int i;
	Node* root = get_node();
	insert_from_file(root, "/home/pchattopadhyay/college-academics/C_Prog/autosuggestion/all-words.txt");
	char user_input[50];
	printf("Enter the prefix to get valid words or ! to exit\n");
	scanf("%s", user_input);
	while(strcmp(user_input, "!"))
	{
		autosuggestion(root, user_input);
		scanf("%s", user_input);
	}
	printf("Have a nice day :):)\n");
	return 0;
}
