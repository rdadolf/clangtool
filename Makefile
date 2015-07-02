all: clangtool.so

# Flags for building shared libraries.
SYSTEM=$(shell uname)
ifeq ($(SYSTEM), Darwin)
	CXXFLAGS= -fno-common 
	LDFLAGS= -dynamiclib -Wl,-flat_namespace -Wl,-undefined,suppress 
endif
ifeq ($(SYSTEM), Linux)
	CXXFLAGS= -fPIC 
	LDFLAGS= -shared 
endif

clangtool.so : %.so: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ `llvm-config --cxxflags` $(LDFLAGS)

CLANGTOOL_FLAGS=-Xclang -load -Xclang clangtool.so

.PHONY: test testO0 testO2
test: testO0 testO2

testO0: test.c clangtool.so
	clang $(CLANGTOOL_FLAGS) -O0 -o test test.c

testO2: test.c clangtool.so
	clang $(CLANGTOOL_FLAGS) -O2 -o test test.c

clean:
	rm -f clangtool.so test

