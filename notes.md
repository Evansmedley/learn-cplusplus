Note: This is just things from [learncpp](https://www.learncpp.com/) that I wanted to record for my own reference later (generally differences between C and C++).

# 1 Basics

## 1.1 Statements and Program Structure

### Types of statements
- Declaration
- Jump
- Expression
- Compound
- Selection (conditionals)
- Iteration (loops)
- Try

### Preprocessor directives
```
#include <iostream>
```

## 1.4 Initialization
```
int a;         // no initializer (default initialization)
int b = 5;     // initial value after equals sign (copy initialization)
int c( 6 );    // initial value in parenthesis (direct initialization)

// List initialization methods (C++11) (preferred)
int d { 7 };   // initial value in braces (direct list initialization)
int e = { 8 }; // initial value in braces after equals sign (copy list initialization)
int f {};      // initializer is empty braces (value initialization)
```

- Copy initialization is used whenever values are passed to a function by value
- Direct initialization is used when casting variables to another type
- Copy initializations is not as efficient as other methods but is a bit better in C++17
- Direct initialization is not great because it is confusing to differentiate between variables and functions, don't use
- List initialization is modern, use curly braces, works in most cases, compiler can detect initialization type errors
- USE DIRECT LIST INITIALIZATION
- Empty list initialization will initialize to 0 or empty or something safe(ish)
- Best practise is to initialize variables upon creation

```
int e { 9 }, f { 10 };     // direct brace initialization
```

- Maybe unused can be used to supress warnings about use of variables (C++17)
```
[[maybe_unused]] pi { 3.14159 };
```

## 1.5 Intro to 'iostream'

- 'std::cout' send data to the console to be printed as text
- '<<' is the insertion operator and is used to pass argument to cout, can be used multiple times in a row to link together outputs
- 'std:endl' is one way to output a newline, best practise is to do so after every line of output, it flushes the buffer (which is slow)
- 'std::cout' is buffered (program can crash while an error message is still in the buffer and not shown in the console)
- Use newline character instead of std::endl (it's faster)
- Single quotes for single characters
- 'std::cin' reads input
- '>>' is the extraction operator
