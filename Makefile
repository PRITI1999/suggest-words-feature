a.out: trie.o client.o
	gcc trie.o client.o

trie.o: trie.c trie.h
	gcc -c trie.c

client.o: client.c trie.h
	gcc -c client.c
