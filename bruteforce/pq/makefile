TARGET = bruteforce

CC = gcc
CFLAGS = -Wall -Wextra -O3 -funroll-loops -fomit-frame-pointer -flto -DTRY_REAL=1 #-DDEBUG=1
LDFLAGS = -flto

OBJECTS := main.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@ -lgmp

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

brute-force:
	tmux \
		new-session   "./bruteforce" \; \
		split-window  "./bruteforce" \; select-layout tiled \; \
		split-window  "./bruteforce" \; select-layout tiled \; \
		split-window  "./bruteforce" \; select-layout tiled \; \
		split-window  "./bruteforce" \; select-layout tiled \; \
		split-window  "./bruteforce" \; select-layout tiled \; \
		split-window  "./bruteforce" \; select-layout tiled \; \
		split-window  "./bruteforce" \; select-layout tiled \; \
		split-window  "./bruteforce" \; select-layout tiled \; \
		split-window  "./bruteforce" \; select-layout tiled \; \
		split-window  "./bruteforce" \; select-layout tiled \; \
		split-window  "./bruteforce" \; select-layout tiled

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean

