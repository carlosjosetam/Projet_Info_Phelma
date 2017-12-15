Projet info PHELMA - ASSEMBLEUR MIPS32

This project is a binary code generator for the language assembly for MIPS32 processors.

The program recieves an assembly file (.s), make the analysis and give to the user
the warnings and errors in the code.
If there is no error, the program generates a file file.l with all the addresses
that is on the file assembly.

Compiling the project:
- Release version: $ make release
- Debug version (with debug prints): $ make debug

Executing file:
- $ ./as-mips assembly.s
(assembly.s is the file to be analysed)

Cleaning compiled files (for a clean compile)
- $ make clean

The structure of the project is the folowing :
.
├── tests (all test files used to develop and test)
│
├── outputs (all the output files are delivered here)
│
├── src (all .c files with core functions)
│   ├── analyse_lexicale (for the analyse of the raw text)
│   │
│   ├── analyse_gramatical (for the gramatical interpretation, operands verifications, relocation and creation of code binaire)
│   │
│   ├── structures (all the structures are declared here)
│   │
│   ├── global.c (global functions)
│   ├── global.h
│   ├── main.c (main program that reads the file)
│   └── main.h
│
├── include (for message printing)
│   └── notify.h
│
├── testing (for testing the program with a shell. Not ready yet)
│
├── .gitignore
├── README.txt
├── Makefile
└── Doxyfile
