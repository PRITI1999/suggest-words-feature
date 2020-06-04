# suggest-words-feature
Implementation of autosuggest feature using trie in C

<h2>What it does?</h2>
<p>There are two files namely 'common-words.txt' and 'all-words.txt'. The first consists approximately 80000 most commonly used english words while the latter has 300000+ english words.<br>This program takes a string as an input and tries to suggest first five words alphabetically from 'common-words.txt' using the trie data structure.<br> If there are no words in common-words.txt for the entered string, a trie is formed of the words present in all-words.txt and words are suggested using this trie.</p>

# How to run?
1. Clone or download this repository
2. Navigate to suggest-words-feature folder 
3. Run this command to compile `make -f Makefile`
4. Run the program `./a.out <args1> [args2] [...]`
