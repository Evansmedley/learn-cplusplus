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


# 2 Functions
## 2.2 Function return values

- 'cstdlib' can be included to be able to use EXIT_SUCCESS and EXIT_FAILURE as opposed to returning 0 in the main function
- Functions with non-void return types must return a value in all cases

## 2.4 Function args and params

- When a function is called all params are created as variables using copy initialization (COPIED), this is called pass by value
- Unused parameter will generate compiler warning, can use an unnamed parameter ('int', etc.) instead which will not generate a warning.
- For unnamed parameters, give them a name inside a '/*...*/' (good practise)

## 2.5 Local scope

- Temporary objects (anonymous objects) are unnamed objexcts created by the compiler to store a value temporarily
- Temporary objects have no scope
- Return values are stored in a temporary object while variables in a function scope are destroyed, before returning to the caller function scope

## 2.7 Forward declarations and definitions

- Forward definition:  define functions before they are called in a file
- Forward declaration: decalre function return value, name and params (but not body) before it is to be called, and then define behavior later
- Forward declarations are most often used when managing multiple code files (sometimes when there are two functions that call one another they are also needed)
- If forward declaration is made but no body is defined, compiler will be ok but linker will complain

## 2.9 Naming collisions and namespaces

- If two functions with the same name exist (in different files), even if one isn't called, the linker will still protest
- If two functions are introduced in the same file, the compiler will protest
- Namespace group related identifiers in a large project so that they don't collide with others
- Global namespace/scope should not have variables defined in it
- std is the name of the namespace that cout and cin are a part of
- '::' is scope resolution operator, global namespace is assumed unless a namespace is provided to the left of the '::'
- Using directive statement would be 'using namespace std' at the beginning of a file and then you could just use cout without the 'std::', THIS IS BAD DON'T USE

## 2.10 Preprocessor intro

- Before compilation, each file is preprocessed
- Preprocessing, compiling and linking together are called translation
- Scans looking for preprocessor directives such as '#include', '#define'
- '#define' is used to create a macro (rule that defines how input text is converted into replacement output text)
- Object-like macros (good for constants, use all caps for identifier) and function-like macros (act like functions, unsafe, DON'T USE)
- Object like macros with no value are useful for other
- Conditional compilation '#ifdef' or '#ifndef' along with '#endif'
- #if 0 ... #endif  is used to exclude a block of code from compilation (if 1 will make block back to normal)\
- Using #define inside of a header file that is included in another file will make any macros defined in the header file usable in the including file

## 2.11 Header files

- Use quotes, not '<>'
- Good practise for all code files to #include their paired header file
- Don't #include .cpp files
- Don't use relative paths for including files in other directories, instead just add those directories to the compiler path

## 2.12 Header guards

square.h
```
#ifndef SQUARE_H
#define SQUARE_H

int getSquare()
{
    return 4;
}

#endif
```

wave.h
```
#ifndef WAVE_H
#DEFINE WAVE_H

#include "square.h"

#endif
```

```
#include "square.h"
#include "wave.h"

int main()
{
    return 0;
}
```

# 3 Debugging C++

## 3.1 Syntax and semantic errors

- Syntax error: you write a statement that is not valid according to C++ grammar (eg. missing semicolon)
- Semantic error: a statement is syntactically valid but does not do what was intended (harder to find)

## 3.4 Debugging tactics

- Use std::cerr instead of std::cout because std::cout may be buffered so logs may not be displayed, also displays as an error

## 3.5 Other debugging tactics (logging)

- Can use std::clog as built in log system
- Better to use plog [link](src/3.5.cpp)

```
#include <plog/Log.h>
#include <plog>Initializers/RollingFileInitializer.h>
#include <iostream>

int getUserInput()
{
    PLOGD << "getUserInput() called";
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;
    return x;
}

int main()
{
    plog::init(plog::debug, "Logfile.txt"); // Initialize logger

    PLOGD << "main() called"; // Output to log

    int x{ getUserInput() };
    std::cout << "You entered: " << x << '\n';

    return 0
}
```
## 3.6 Debugging

- To ensure that cout always results in a buffer flush use the following statement at the top of main
```
std::cout << std::unitbuf; // enable automatic flushing for std::cout (for debugging)
```
- Can wrap this code in #ifndef in order to only have it run when a DEBUG flag is up

### Steps

- Step into: executes the next statement in the normal execution path of the program and then pauses, goes into functions
- Step over: executes next statement but will not enter function calls, executes an entire function without stopping and pauses after function call
- Step out: Executes all remaining code in the function currently being executed and pauses after the current function has completely run
- Continue: go to next breakpoint or end of program
