LLVM_BIN?=$(error Please set LLVM_BIN to wherever llvm and clang are installed)
# LLVM_BIN should be the bin/ directory, just like if you were adding it to your path.

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
	$(CXX) $(CXXFLAGS) $< -o $@ `$(LLVM_BIN)/llvm-config --cxxflags` $(LDFLAGS)

CLANGTOOL_FLAGS=-Xclang -load -Xclang clangtool.so

test: test.c
	$(LLVM_BIN)/clang $(CLANGTOOL_FLAGS) -O2 -o test test.c

clean:
	rm -f clangtool.so test

