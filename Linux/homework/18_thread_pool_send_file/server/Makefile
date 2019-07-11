SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=server
CC:=gcc
CFLAGS:=-g -Wall 
$(ELF):$(OBJS)	
	gcc -o $@ $^ -lpthread
.PHONY:clean
clean:
	rm -rf $(OBJS) $(ELF)
