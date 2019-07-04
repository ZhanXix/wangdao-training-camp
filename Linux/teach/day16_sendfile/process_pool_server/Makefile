SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=process_pool_server
CC:=gcc
CFLAGS:=-g -Wall
$(ELF):$(OBJS)	
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -rf $(OBJS) $(ELF)
