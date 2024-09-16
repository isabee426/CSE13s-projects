#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  makeWordFrequency        makes WordFrequency
#  makeOrder                makes Order	
#  make DictionaryClient    makes DictionaryClient
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg
#  make DictionaryCheck     runs DictionaryClient under valgrind
#------------------------------------------------------------------------------
MAIN1           = Order
MAIN2           = WordFrequency
ADT            = Dictionary
SOURCE1         = $(MAIN1).cpp
OBJECT1         = $(MAIN1).o
SOURCE2         = $(MAIN2).cpp
OBJECT2         = $(MAIN2).o
ADT_TEST       = $(ADT)Client
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN1): $(OBJECT1) $(ADT_OBJECT)
	$(LINK) $(MAIN1) $(OBJECT1) $(ADT_OBJECT)

$(MAIN2): $(OBJECT2) $(ADT_OBJECT)
	$(LINK) $(MAIN2) $(OBJECT2) $(ADT_OBJECT)	

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(OBJECT1): $(SOURCE1) $(ADT_HEADER)
	$(COMPILE) $(SOURCE1)

$(OBJECT2): $(SOURCE2) $(ADT_HEADER)
	$(COMPILE) $(SOURCE2)

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean:
	$(REMOVE) $(MAIN1) $(MAIN2) $(ADT_TEST) $(OBJECT1) $(OBJECT2) $(ADT_TEST).o $(ADT_OBJECT)

$(MAIN1)Check: $(MAIN1)
	$(MEMCHECK) $(MAIN1) Gutenberg myGutenberg-out

$(MAIN2)Check: $(MAIN2)
	$(MEMCHECK) $(MAIN2) Gutenberg myGutenberg-out

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)