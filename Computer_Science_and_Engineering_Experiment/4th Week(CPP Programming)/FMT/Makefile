CC = g++
CFLAGS = -g -c

OBJECTS = main.o Output.o String_Manipulation.o
SRCS = main.cpp Output.cpp String_Manipulation.cpp

TARGET = fmt

$(TARGET): $(OBJECTS) Header.h
	$(CC) -o $(TARGET) $(OBJECTS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

cleanO:
	rm -rf *.o

cleanT:
	rm -rf $(TARGET)
