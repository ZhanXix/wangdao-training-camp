SRCS:=$(wildcard *.c)
ELFS:=$(SRCS:%.c=%)
CC:=gcc
all:${ELFS}

%:%.c
	${CC} $^ -o $@ -lpthread

.PHONY:clean,cleanup
clean:
	rm -rf ${ELFS}
cleanup:
	rm -rf ${ELFS} Makefile

