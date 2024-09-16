CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = 
EXEC = huff
EXEC2 = dehuff
TEST1 = pqtest
TEST2 = nodetest
TEST3 = brtest
TEST4 = bwtest
HEADERS = bitreader.h bitwriter.h node.h pq.h

SOURCES1 = bitreader.c bitwriter.c node.c pq.c huff.c
SOURCES2 = pq.c node.c bitwriter.c bitreader.c dehuff.c

SOURCES3 = node.c pq.c pqtest.c
SOURCES4 = node.c pq.c nodetest.c
SOURCES5 = bitreader.c brtest.c
SOURCES6 = bitwriter.c bwtest.c

OBJECTS1= $(SOURCES1:.c=.o)
OBJECTS2= $(SOURCES2:.c=.o)

OBJECTS3= $(SOURCES3:.c=.o)
OBJECTS4= $(SOURCES4:.c=.o)
OBJECTS5= $(SOURCES5:.c=.o)
OBJECTS6= $(SOURCES6:.c=.o)

all: $(EXEC) $(EXEC2) $(TEST1) $(TEST2) $(TEST3) $(TEST4)

$(EXEC): $(OBJECTS1)
	$(CC) $^ $(LFLAGS) -o $(EXEC)

$(EXEC2): $(OBJECTS2)
	$(CC) $^ $(LFLAGS) -o $(EXEC2)

$(TEST1): $(OBJECTS3)
	$(CC) $^ $(LFLAGS) -o $(TEST1)

$(TEST2): $(OBJECTS4)
	$(CC) $^ $(LFLAGS) -o $(TEST2)

$(TEST3): $(OBJECTS5)
	$(CC) $^ $(LFLAGS) -o $(TEST3)

$(TEST4): $(OBJECTS6)
	$(CC) $^ $(LFLAGS) -o $(TEST4)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXEC) $(EXEC2) $(TEST1) $(TEST2) $(TEST3) $(TEST4) *.o

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format

