Dictionary.cpp
this is the main file for the creation of the dictionary adt. the file consists of functions for iterate through the red black binary tree, to change, add and remove values from the tree, and to clear, create, copy, and compare trees. These functions also fix the tree to fit the red black structure It uses a doubly linked list for the structure. there is one singular valgrind error when running the model test.

dictionary.h
this file is the header for the function, it keeps all of the functions for public use.

order.cpp
this uses the in order and pre order tree walk strings to create ordered lists of dictionaries. It prints the key value pairs in alphabetical order then prints the keys in preorder walk (the order in which they were added.) the input is key value pairs in an input file seperated by newlines

wordfrequency.cpp
this file takes in a large input file and outputs the word frequencies of each token. i added in \r to the delimiter string because i am on windows. if this breaks the code for you please keep this in mind, because my code passed all the tests. it prints the keys and frequencies in alphabetical order.

Dictionarytest.cpp
this is the file that i tested my code in. I used print statements to guide my way through the testing process.

Makefile
This file has commands for cleaning .o files, making the testing and main programs and checking the programs under valgrind.

