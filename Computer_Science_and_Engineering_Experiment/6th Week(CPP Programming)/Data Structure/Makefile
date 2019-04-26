CC = g++

OBJECTS = Main.o
SRCS = Main.cpp

TARGET = List

$(TARGET): $(OBJECTS) Stack.h LinkedList.h
	$(CC) -o $(TARGET) $(OBJECTS)

clean:
	rm -rf *.o $(TARGET)

cleanO:
	rm -rf *.o

cleanT:
	rm -rf $(TARGET)
