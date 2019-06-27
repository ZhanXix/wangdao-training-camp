SRCS:=$(wildcard *.c)
ELFS:=$(SRCS:%.c=%)
CC:=gcc
all:${ELFS}

%:%.c
	${CC} $^ -o $@ -lpthread

.PHONY:clean
clean:
	rm -rf ${ELFS}

