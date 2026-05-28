CC	= cc
CFLAGS	= -std=c11 -O2 -Wall -Wextra -Wpedantic -Wshadow
TARGET	= cw
SRCS	= src/*.c
OBJS	= $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c wc.h
	$(CC) $(CFLAGS) -c $< -o $@

install:
	mv

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean install
