## clangtool

When writing an LLVM pass, the straightforward way to use it is to produce LLVM IR code with `clang -emit-llvm`, then run your tool with `opt`, then link it (`llvm-link`), ccompile it down to a native object file (`llc`), and finally produce a binary (`gcc`). This works, and for development, it's not a terrible way to do things.

When using custom LLVM passes as a research tool, however, it's often necessary to do things like...shudder...build SPEC. This *is* a terrible way to do things, mostly because that build flow for a custom LLVM pass isn't a drop-in replacement for `$(CC)`, and most complicated projects don't expect that.

This can be solved by adding a little bit of code at the end of your LLVM pass which lets Clang discover and add your custom pass to its existing list. That way, instead of having to use all five of the separate steps above, you can just run `clang` with a couple extra options, and everything works.

----

Using `clangtool`:

Two steps:

1. Build your custom LLVM pass the normal way (as a shared library with the appropriate llvm flags).

2. Run `clang` on your input code with the following extra options:

        clang -Xclang -load -Xclang <custom-pass>.so ...

That's it. Your pass will automatically be run at the point you specified in the code.

