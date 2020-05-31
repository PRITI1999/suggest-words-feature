a.out: client.o suggest_feature.o trie.o logger.o
	gcc suggest_feature.o client.o trie.o logger.o

logger.o: logger.c logger.h
	gcc -c logger.c

trie.o: trie.c trie.h logger.h
	gcc -c trie.c

suggest_feature.o: suggest_feature.c suggest_feature.h logger.h
	gcc -c suggest_feature.c

client.o: client.c suggest_feature.h logger.h
	gcc -c client.c
