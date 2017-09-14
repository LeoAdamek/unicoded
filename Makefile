CC=clang
LD=clang

SOURCES=$(shell find . -name '*.c')
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

CFLAGS=$(shell pkg-config --cflags icu-uc icu-io)
LDFLAGS=$(shell pkg-config --libs icu-uc icu-io)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

./unicoded: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^


clean:
	rm -f ./unicoded $(OBJECTS)
