a.out: client.o suggest_feature.o trie.o
	gcc suggest_feature.o client.o trie.o

trie.o: trie.c trie.h
	gcc -c trie.c

suggest_feature.o: suggest_feature.c suggest_feature.h
	gcc -c suggest_feature.c

client.o: client.c suggest_feature.h
	gcc -c client.c
