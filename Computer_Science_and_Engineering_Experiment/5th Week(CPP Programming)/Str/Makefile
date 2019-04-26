CC = g++
CFLAGS = -g -c

OBJECTS = Main.o Str.o
SRCS = Main.cpp Str.cpp

TARGET = Str

$(TARGET): $(OBJECTS) Str.h
	$(CC) -o $(TARGET) $(OBJECTS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(TARGET)
cleanO:
	rm -rf *.o

cleanT:
	rm -rf $(TARGET)
