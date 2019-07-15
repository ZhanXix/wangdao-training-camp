SRCS:=$(wildcard ../src/*.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=server
CC:=gcc
CFLAGS:=-g -Wall -lpthread -I /usr/include/mysql/ -lmysqlclient -lcrypt
$(ELF):$(OBJS)	
	gcc -o $@ $^ -lpthread -I /usr/include/mysql/ -lmysqlclient -lcrypt
.PHONY:clean
clean:
	rm -rf $(OBJS) $(ELF)
