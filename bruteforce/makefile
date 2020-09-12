TARGET = bruteforce

CC = gcc
CFLAGS = -Wall -Wextra -O3 -flto #-DDEBUG=1
LDFLAGS = -flto

OBJECTS := main.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@ -lgmp

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
