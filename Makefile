CC      = cc
CFLAGS  = -std=c11 -O2 -Wall -Wextra -Wpedantic -Wshadow -Isrc
TARGET  = cw
SRCS    = $(wildcard src/*.c)
OBJS    = $(patsubst src/%.c, %.o, $(SRCS))
PREFIX  = /usr/local

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: src/%.c src/cw.h
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	install -m 755 $(TARGET) $(PREFIX)/bin/$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean install
