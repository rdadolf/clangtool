## Using LLVM plugins with clang

The [LLVM docs](http://llvm.org/docs/WritingAnLLVMPass.html) suggest using `opt` to load and run custom passes. This works, but for certain tasks, like building programs with complicated Makefiles or unusual environments, it is less than ideal. Instead, LLVM provides a hook to allow plugin modules to be run automatically when loaded by clang. This lets you add a couple of flags and use clang (and your pass) as a drop-in replacement for your normal C compiler. These files demonstrate how that works.

### Using clangtool:

Two steps:

1. Build your custom LLVM pass the normal way (as a shared library with the appropriate llvm flags).

2. Run `clang` on your input code with the following extra options:

        clang -Xclang -load -Xclang <custom-pass>.so ...

That's it. Your pass will be run automatically. You can specify these with `CFLAGS` in a Makefile, override `CC` or `CXX`, or write a script to wrap clang and use that.

### How it works:

The key is a static class called `RegisterStandardPasses`, which is defined in the `PassManagerBuilder.h` header. The constuctor for this class calls the `addGlobalExtension` function, which in turn adds your custom pass to the list of extensions that are loaded by default.
