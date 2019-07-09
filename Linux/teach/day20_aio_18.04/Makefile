SRC:=$(wildcard *.c)
TARGETS:=$(patsubst %.c,%,$(SRC))
all:$(TARGETS)
%:%.c
	gcc $< -o $@ -lrt
clean:
	rm -rf $(TARGETS)
