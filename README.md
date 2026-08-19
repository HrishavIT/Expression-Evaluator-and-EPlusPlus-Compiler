# Expression Evaluator and E++ Compiler

A C++ compiler and expression evaluator. `e++Compiler` parses a custom "E++" language into expression trees and compiles it to target code, with symbol table-based variable handling. `expressionEvaluator` evaluates arithmetic expressions using arbitrary-precision integers and rationals.

This repository contains two related C++ projects built as coursework:

- **e++Compiler** — a compiler for a custom language called E++
- **expressionEvaluator** — a standalone arithmetic expression evaluator

## Features

### e++Compiler
- Custom lexer and parser for the E++ language
- Builds an AST (expression tree) for each statement
- Supports arithmetic expressions (`+`, `-`, `*`, `/`) with nested parentheses
- Handles variable assignment (`:=`), deletion (`del`), and return statements (`ret`)
- Symbol table for variable resolution
- Min-heap based memory management
- Compiles validated code into target output (`targ.txt`)

### expressionEvaluator
- Parses and evaluates arithmetic expressions
- Supports arbitrary-precision integers (`unlimitedint`)
- Supports arbitrary-precision rationals (`unlimitedrational`)
- Includes test cases for validation

## Folder Structure

```
CompilerEvaluator/
├── e++Compiler/
│   ├── main.cpp            # Entry point — reads input file, validates, compiles
│   ├── eppcompiler.cpp/.h  # Core compiler logic
│   ├── parser.cpp/.h       # Tokenizer + expression tree builder
│   ├── exprtreenode.cpp/.h # AST node definition
│   ├── symtable.cpp/.h     # Symbol table for variables
│   ├── symnode.cpp/.h      # Symbol table node
│   ├── heapnode.cpp/.h     # Heap node for memory management
│   └── minheap.cpp/.h      # Min-heap implementation
│
└── expressionEvaluator/
    ├── entry.cpp/.h             # Entry point
    ├── evaluator.cpp/.h         # Core evaluation logic
    ├── exprtreenode.cpp/.h      # AST node definition
    ├── symtable.cpp/.h          # Symbol table
    ├── unlimitedint.cpp/.h      # Arbitrary-precision integer type
    ├── unlimitedrational.cpp/.h # Arbitrary-precision rational type    
    ├── Makefile
    └── test_cases/              # Sample test inputs/outputs
```

## Build & Run

### e++Compiler
```bash
cd e++Compiler
g++ *.cpp -o e++ 
./e++ <input_file>
```
This generates a `targ.txt` file with the compiled target code, or prints an error if the input is invalid.


### expressionEvaluator
```bash
cd expressionEvaluator
make
./A4Checker <input_file>
```

## Example

**E++ input** (`input.txt`):
```
x := ( 3 + 4 )
ret x
```

**Run:**
```bash
./e++ input.txt
```

**Output:**
```
Targ code for file input.txt generated successfully
```

## Author

Hrishav Raj Singh
