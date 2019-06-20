SRCS:=$(wildcard *.c)
OBJS:=$(SRCS:%.c=%.o)
TARGETS:=main
CC:=gcc
CFLAGS：=-Wall

$(TARGETS):$(OBJS)
	$(CC) $^ -o $@

.PHONY:clean
clean:
	rm $(OBJS) $(TARGETS)

