SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=server
CC:=gcc
CFLAGS:=-Wall -I../include
$(ELF):$(OBJS)
	gcc $^ -o $@ -lpthread
.PYONY:clean
clean:
	rm -rf $(OBJS) $(ELF)
