BigInteger.cpp
This file represents the big integer ADT. It has functions to access the two fields, the sign of the number and the list of digits. The string function, which prints the integer with no leading zeros, and an optional +/-. It also has functions to add, subtract, and multiply big ints. The operators are overloaded for this, including the subassignment and add assignment and mult assignment operators. There are also helper functions to normalize a list, and to negate the sign of a list. the global variables are base and power, and they determine the size of the longs in each list. The base and power don't change the representation however.

BigInteger.h
BigInteger.h is the header file for BigInteger.c, containing all of the necessary public functions for the test files and arithmetic to use.


BigIntegerTest.cpp
This is the file where i tested my functions. I used print statements to guide through the testing process.

List.cpp

List.c is the main C source file. It contains the many functions that make up the List ADT. These functions include deleting and inserting list elements, traversing the list via moving the cursor, which lies vertically between elements, as well as getting and setting elements. There are also functions to access the fields of the list function, such as int length and int position and elements that lie before and after the cursor

List.h
List.h is the header file for List.c, containing all of the necessary public functions for the test files and biginteger to use.

ListTest.c
This is my testing file, it contains thorough testing of all the functions. I used print statements to help guide my way through the test file.

Arithmetic.c
This is the main file. It performs operations on the BigInteger structure, such as adding, subtracting, multiplying, exponentials, and scalar mult. Its usage is in the form of ./Arithmetic <input> <output> and the two numbers on the input file are seperated by a space.

Makefile
The makefile has several commands, two of which to make the BigIntegerClient (tester) and to make the arithmetic program itself, two of which to run valgrind on arithmetic and BigIntegerClient, and one for cleaning the .o files from the current directory. 