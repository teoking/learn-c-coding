CC := gcc
CFLAGS := -Wall -g -std=c99 $(DEFS)

ex := $(patsubst %.c,%,$(wildcard ex*.c))
obj := $(patsubst %.c,%.o,$(wildcard *.c))

all: $(ex)

ex19: object.o game.o

clean:
	rm -f $(ex)
	rm -f $(obj)
	rm -fR *.dSYM
	rm -fR *.d

# Generate dependencies automatically
include $(obj:.o=.d)
%.d: %.c
	$(CC) -MM $(CPPFLAGS) $< | sed 's|$*\.o[ :]*|$*.o $*.d: |g' > $@
