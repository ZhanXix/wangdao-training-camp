SRCS:=$(wildcard *.c)
TARGETS:=$(SRCS:%.c=%)
all:$(TARGETS)
	@for i in $(TARGETS);do gcc -o $${i} $${i}.c;done
clean:
	rm $(TARGETS)
