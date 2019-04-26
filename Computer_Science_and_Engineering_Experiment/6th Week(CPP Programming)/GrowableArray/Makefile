CC = g++

OBJECTS = Main.o
SRCS = Main.cpp

TARGET = GrowableArray

$(TARGET): $(OBJECTS) Array.h Array.cpp GrowableArray.h GrowableArray.cpp
	$(CC) -o $(TARGET) $(OBJECTS)

clean:
	rm -rf *.o $(TARGET)

cleanO:
	rm -rf *.o

cleanT:
	rm -rf $(TARGET)
