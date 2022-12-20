Gran-Schmitt Process Calculator program

A simple project where I coded a Gran-Schmitt calculator for Rn vectors only. This program should
take a text file as std input by using the '<' in bash cmdline and from that file create a basis/set of
vectors in which to transform into a different set of vectors that are orthogonal/orthonormal to eachother.

The project is not supposed to be comprehensive, just something that I wanted to do in my spare time so there might be a few
bugs that I have not checked or have decided not worth to fix. There is also some misspelling of gran-schmitt sometimes so
just a heads up.

Text file requirements:
	- Each vector must be in its own line, where each number separated by a delimiter (space preferred - have not tested others)
	- no plans for mathamatical notation so please insert decimals for any fractions
	- program will exit if not all of the vectors are the same dimension (ie: all R4, all R2, etc...)

Create the executable using "make" cmd

Usage of program:
$ ./gran_schimit < [filename]


The two input files included are to be used to test program output. I have not manually tested the first input file,
however the second one (in R4) is from a textbook where the values it produced matches what the textbook states is the answer
so the program should reliably work (hopefully???).
