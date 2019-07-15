SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=client
CC:=gcc
CFLAGS:=-g -Wall 
$(ELF):$(OBJS)	
	gcc -o $@ $^  
.PHONY:clean
clean:
	rm -rf $(OBJS) $(ELF)
