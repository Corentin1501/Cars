CC = gcc


SRCDIRS := $(shell find . -type d)
SRCS := $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))
OBJS := $(SRCS:.c=.o)


%.o: %.c
	$(CC)  -c $< -o $@



Cars : $(OBJS)
	$(CC) main.c $(OBJS) -o $@

 
