SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=client
CC:=gcc
CFLAGS:=-g -Wall -lcrypt
$(ELF):$(OBJS)	
	gcc -o $@ $^  -lcrypt
.PHONY:clean
clean:
	rm -rf $(OBJS) $(ELF)
