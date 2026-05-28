# cw
a lighter, way smaller reimplementation of wc

wc is a tool used to count words, lines, largest line length, and more within a file specified. It is much smaller than the GNU
tool made to do the same task called **wc**. 

### installation

Unlike wc, cw requires only a C99 compatible C compiler in order to build, and doesn't pull in any insanely large dependencies. 
A Makefile is provided with cw to automate and ease the process of compiling. To build and install cw to your PATH, simply run:

`make && sudo make install`.

### usage

You use cw the exact same way you use wc. Usage instructions are below.

```sh
cw [file...]
cw [-lwcmL] [file...]
```

### licensing

licensed under The Unlicense
