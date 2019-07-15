SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=server
CC:=gcc
CFLAGS:=-g -Wall -lpthread -I /usr/include/mysql/ -lmysqlclient
$(ELF):$(OBJS)	
	gcc -o $@ $^ -lpthread -I /usr/include/mysql/ -lmysqlclient
.PHONY:clean
clean:
	rm -rf $(OBJS) $(ELF)
