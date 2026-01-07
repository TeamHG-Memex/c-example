COMPILER=gcc
CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG -Xlinker --verbose $(OPTFLAGS)
LDFLAGS=$(OPTLIBS) -lcurl -L./build

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TARGET=build/libhgcrawl.a
LIBDIR=build/

# The Target Build
all: $(TARGET)

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	#combines all objects into one .a file
	ar rcs $@ $(OBJECTS)
	#stores the index of ar rcs .a lib (?)
	ranlib $@

build:
	@mkdir -p build
	@mkdir -p bin
	@mkdir -p headers

#valgrind:
#	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log 
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`
	rm headers/*

# The Install
install: all
	@cp src/*.h headers/
#	install -d ./lib/
#	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true

executable: all
	gcc -Lbuild/ test.c -lhgcrawl -lcurl -o test.out
