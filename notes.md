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


# 4 Fundamental Data Types

## 4.1 Intro

| Types                               | Category                | Meaning                                    | Example   |
|-------------------------------------|-------------------------|--------------------------------------------|-----------|
| float                               | Floating Point          | a number with a fractional part            | 3.14159   |
| double                              | Floating Point          | a number with a fractional part            | 3.14159   |
| long double                         | Floating Point          | a number with a fractional part            | 3.14159   |
| bool                                | Integral (Boolean)      | true or false                              | true      |
| char                                | Integral (Character)    | a single character of text                 | ‘c’       |
| wchar_t                             | Integral (Character)    | a single character of text                 | ‘c’       |
| char8_t (C++20)                     | Integral (Character)    | a single character of text                 | ‘c’       |
| char16_t (C++11)                    | Integral (Character)    | a single character of text                 | ‘c’       |
| char32_t (C++11)                    | Integral (Character)    | a single character of text                 | ‘c’       |
| short int                           | Integral (Integer)      | positive and negative whole numbers, 0     | 64        |
| int                                 | Integral (Integer)      | positive and negative whole numbers, 0     | 64        |
| long int                            | Integral (Integer)      | positive and negative whole numbers, 0     | 64        |
| long long int (C++11)               | Integral (Integer)      | positive and negative whole numbers, 0     | 64        |
| std::nullptr_t (C++11)              | Null Pointer            | a null pointer                             | nullptr   |
| void                                | Void                    | no type                                    | n/a       |


## Void

- Means no type, incomplete type (declared but not yet defined)


## Object Sizes

| Category         | Type            | Minimum Size | Typical Size        | Note                   |
|------------------|-----------------|--------------|---------------------|------------------------|
| Boolean          | bool            | 1 byte       | 1 byte              |                        |
| character        | char            | 1 byte       | 1 byte              | always exactly 1 byte  |
|                  | wchar_t         | 1 byte       | 2 or 4 bytes        |                        |
|                  | char8_t         | 1 byte       | 1 byte              |                        |
|                  | char16_t        | 2 bytes      | 2 bytes             |                        |
|                  | char32_t        | 4 bytes      | 4 bytes             |                        |
| integer          | short           | 2 bytes      | 2 bytes             |                        |
|                  | int             | 2 bytes      | 4 bytes             |                        |
|                  | long            | 4 bytes      | 4 or 8 bytes        |                        |
|                  | long long       | 8 bytes      | 8 bytes             |                        |
| floating point   | float           | 4 bytes      | 4 bytes             |                        |
|                  | double          | 8 bytes      | 8 bytes             |                        |
|                  | long double     | 8 bytes      | 8, 12, or 16 bytes  |                        |
| pointer          | std::nullptr_t  | 4 bytes      | 4 or 8 bytes        |                        |

- 'sizeof(...)' can be used to check size, does not include dynamically allocated memory used of course

## Signed Ints

- By default all ints are signed
- Signed keyword prefix and int suffix are redundant (goes before name during declaration)
- Overflow can occur
- n-bit signed variable has a range og (-2^(n-1), 2^(n-1)-1)
- Integer division is like floor(x/y), remainder is dropped

## Unsigned Ints

- Use unsigned prefix to use unsigned ints
- Out of range unsigned value is integer-divided by 1+largest_number_of_type (eg. 255 + 1)
- AVOID
- Math between unsigned and signed will convert signed to unsigned
- Good for bit manipulation, array indexing

## Fixed Width Ints

- C++ only guarantees that integer variables will have a minimum size (could be larger)
- C99 defined set of fixed-width integers (accessed with <cstdint> in std namespaces)
- Best practice
  - Prefer int when size doesn't matter and variable is short lived
  - Use std::int#_t for storing a quantity that needs a guaranteed range
  - Use std::uint#_t for bit manipulation (or well-defined wrap around behavior)
- Avoid
  - short and long
  - Unsigned types
  - 8-bit fixed-width ints (may be treated like a char instead of int)
  - fast and least width types
  - Compiler-specific fixed width ints
- What integral type does sizeof return? -> std::size_t (implementation defined unsigned int)
- std::size_t imposes a strict upper limit to object sizes

## Scientific Notation

- 1.2 * 10^4 -> 1.2e4

## Floats

- By default std::cout does not print the fractional part of a number if it is 0
- Can override default precision of std::cout using output manipulator << std::setprecision(5)
- Favour double over float
- posinf, neginf and nan are sometimes available

## Booleans

- Use bool
- Printing booleans: 0 -> false, 1 -> true
- Output manipulators: std::boolalpha and std::noboolalpha to print as true and false
- For std::cin to interpret true and false for bools, use std::boolalpha input manipulator

## Chars

- SINGLE QUOTES 
- \x6F is how hex digits are written, they will be converted to char type
- Use stand-along chars in single quotes, easier for compiler to optimize

## Type Conversion and Static Cast

- int to double is safe, double to int is not
- Explicit type conversion static_cast<new_type>(expression) (no warnings about data loss when you explicit cast)


# 5 Constants and Strings

## Constant variables

- 3 types -> constan vars, object-like macros, enumerated constants

### 'const'
- Declared with 'const' qualifier before type (good practise), must be initialized upon definition
- Common naming techniques include all-caps (from C), k prefix (more common in C++, e.g. kEarthGravity), name the same as regular variables (this is good!)
- Function params can be constants (value not changed inside the function), don't declare constant params when passing by value
- Return values can also be const, again don't use when returning by value

### '#define MACRO'
- Preprocessor macros just substitute values during compilation
- Prefer 'const' to preprocessor macros because
  - They don't follow normal scoping rules
  - Hard to debug
  - Macro substitution behaves differently than everything else in C++

### Type Qualifiers
- Keyword that is applied to a type that modifies how the type behaves
- 'const' and 'volatile' are type qualifiers
- 'volatile' is used to tell the compiler that an object may have its value changed at any time (rarely used)

## Literals
- Values inserted directly into code (e.g. 5, true, 4.5, "Test", '\n')
- Literal suffixes can be used to change the type (mostly not used except for f, use 'L' over 'l')
- Floating point literals have a type of double by default, f or F is used
- Strings are enclosed in "", char literals are enclosed in ''
- Strings are not a fundamental type in C++, instead have a strange and complicated type that is hard to work with (C strings inherited from C)
- Important things to know about c-style string literals
  - All c-style literals have implicit null terminator '\0'
  - c-style string literals are const objects that are created at the start of a program and guaranteed to exist for the entirety of the program
  - std::string and std::string_view literals create temporary objects (must be used immediately and are destroyed at the end of the full expression in which they are created)
- Don't use magic numbers (name variables so that readers understand what the magic number represents)

| Data type       | Suffix                                | Meaning                               |
|-----------------|---------------------------------------|---------------------------------------|
| integral        | u or U                                | unsigned int                          |
| integral        | l or L                                | long                                  |
| integral        | ul, uL, Ul, UL, lu, lU, Lu, LU        | unsigned long                         |
| integral        | ll or LL                              | long long                             |
| integral        | ull, uLL, Ull, ULL, llu, llU, LLu, LLU | unsigned long long                    |
| integral        | z or Z                                | The signed version of std::size_t (C++23) |
| integral        | uz, uZ, Uz, UZ, zu, zU, Zu, ZU        | std::size_t (C++23)                   |
| floating point  | f or F                                | float                                 |
| floating point  | l or L                                | long double                           |
| string          | s                                     | std::string                           |
| string          | sv                                    | std::string_view                      |

## Decimal, Octal, Hex, Binary
```
int main()
{
  int octal { 012 };      // '0' indicates octal
  int decimal { 12 };     // Always assumes decimal
  int hex { 0x AA };      // "0x" indicates hex
  int bin { 0b00 };       // "0b" indicates binary
}
```
- Can use ' quotation mark as a digit separator when writing numbers (but cannot occur before the first digit of a value)
- By default, all C++ values are outputted in decimal (output format can be changed using std::dec, std::oct and std::hex I/O manipulators, effect is lasting)
```
int main()
{
  std::cout << x      // Default decimal
  std::cout << std::hex << x      // Now hex
  std::cout << x       // Still hex
  std::cout << std::dec << x     // Back to decimal
}
```
- Printing binary values is done using std::bitset type, define std::bitset variable
```
int main()
{
  std::bitset<8> bin{ 0b1100'0101 };
  std::cout << bin1;
}
```
- C++20 and 23 provide better options available via format library in 20 and print library in 23

## Constant expressions and compile-time optimization
- Prefer 'int x { 7 };' over 'int x { 3 + 4 };' because the former can be evaluated at compile time while the latter will be evaluated at runtime
- Constant expressions are expressions containing only compile-time constants and operators/functions that support compile-time evaluation
  - Includes: literals, const integral variables with a constant expression initializer, constexpr variables, enumerators, non-type template params
```
int main()
{
    // Non-const variables:
    int a { 5 };                 // 5 is a constant expression
    double b { 1.2 + 3.4 };      // 1.2 + 3.4 is a constant expression

    // Const integral variables with a constant expression initializer
    // are compile-time constants:
    const int c { 5 };           // 5 is a constant expression
    const int d { c };           // c is a constant expression
    const long e { c + 2 };      // c + 2 is a constant expression

    // Other const variables are runtime constants:
    const int f { a };           // a is not a constant expression
    const int g { a + 1 };       // a + 1 is not a constant expression
    const long h { a + c };      // a + c is not a constant expression
    const int i { getNumber() }; // getNumber() is not a constant expression

    const double j { b };        // b is not a constant expression
    const double k { 1.2 };      // 1.2 is a constant expression

    return 0;
}
```
- Constant expressions -> always eligible for compile-time evaluation (faster + smaller code), more likely to show errors at compile time (safer, easier to test)
- Runtime expressions -> only the type of the expression is known at compile-time
- Subexpressions can be optimized if constant
- Learn more about constant expressions

## Constexpr variables
- One way to make a compile-time constant variable is to use the const keyword, if const variable has an integral type and a constant expression initialized, it is a compile-time constant
- When using const, integral variables could end up as either compile-time costs or runtime consts depending on whether the initializer is a constant expression or not (hard to tell whether const variable is actually a compile-time constant or not)
```
int a { 5 };       // not const at all
const int b { a }; // obviously a runtime const (since initializer is non-const)
const int c { 5 }; // obviously a compile-time const (since initializer is a constant expression)

const int d { someVar };    // not obvious whether this is a runtime or compile-time const
const int e { getValue() }; // not obvious whether this is a runtime or compile-time const
```

### Constexpr keywork
- constexpr instead of const indicates a variable that is always a compile-time constant, therefore must be initialized with a constant expression, otherwise a compilation error witll occur
- constexpr works for both integral and non-integral types
- constexpr variables are implicitly const (not vice versa)
```
#include <iostream>

int five()
{
    return 5;
}

int main()
{
    constexpr double gravity { 9.8 }; // ok: 9.8 is a constant expression
    constexpr int sum { 4 + 5 };      // ok: 4 + 5 is a constant expression
    constexpr int something { sum };  // ok: sum is a constant expression

    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    constexpr int myAge { age };      // compile error: age is not a constant expression
    constexpr int f { five() };       // compile error: return value of five() is not a constant expression

    return 0;
}
```
### Constants best practice
- Any constant var whose initializer is a constant expression should be declared as constexpr
- Any constant var whose initializer is not a constant expression should be declared as const
- Types that use dynamic memory allocation are not fully compatible with constexpr (use const instead of constexpr or pick a different type)
- Function calls are evaluated at runtime therefore const function parameters are treated as runtime constants and function parameters cannot be declared as constexpr (functions that can be evaluated at compile-time exist in C++, covered later)

## Conditional operator
- 'condition ? return_if_true : return_if_false' is arithmetic
- Best practise: parenthesize the conditional operator in a compound expression
- If x is a constexpr, then x != 5 is a constant expression, therefore can use if constexpr
- Avoid conditional operator in complicated expressions

## Inline functions and variables
- Perform discrete tasks, read input from user, output to file, calculate a value
- Inline expansion is a process where a fn call is replaced by the code from the called function's definition if it's easy
- Inline keyword (originally intended to be a hint to the compiler that a function can be inline), not used for many reasons
- Other use for inline in modern C++ is that it means multiple definitions allowed and can be defined in multiple header files but must be the same in all cases
- Inlines are typically defined in header files and can be included in any code file

```
pi.h
#ifndef PI_H
#define PI_H

inline double pi() { return 3.14159; }

#endif
```
```
main.cpp
#include "pi.h" // will include a copy of pi() here
#include <iostream>

double circumference(double radius); // forward declaration

int main()
{
    std::cout << pi() << '\n';
    std::cout << circumference(2.0) << '\n';

    return 0;
}
```

- Functions defined inside a class, struct or union type definition, constexpr/consteval fns and functions implicitly instantiated from function templates are all implicity inline
- Don't mark as inline unless defining them in a header file


## Constexpr and consteval functions
- Function call to a normal function is not allowed in constant expressions
- When using a function in variable initialization, name both the function and the variable as constexpr and both can be evaluated at compile-time
- Arguments to a constexpr function must be known at compile time (constant expressions)
- constexpr functions cannot have parameters declared as constexpr (so using them to initialize another constexpr variable is not possible)
- If arguments to constexpr function are not constexpr it will instead be evaluated at run-time
- consteval forces compile-time evaluation of a function
- Forward function declarations for constexpr functions do not suffice, this means they may need to be defined fully in many places, to avoid violating the one-definition rule, they are explicitly inline
- constexpr/consteval function sused in multiple s ource files should be defined in a header file so they can be included into each source file
- consteval functions are called immediate functions
- std::is_constant_evaluated() doesn't tell you what the compiler is doing but it will say whether or not a constexpr function can be evaluated at compile-time
- The following shows using a const-eval helper function to determine whether a function is evaluated at compile-time or not
```
#include <iostream>

// Uses abbreviated function template (C++20) and `auto` return type to make this function work with any type of value
consteval auto compileTimeEval(auto value)
{
    return value;
}

constexpr int greater(int x, int y) // function is constexpr
{
    return (x > y ? x : y);
}

int main()
{
    std::cout << greater(5, 6) << '\n';                  // may or may not execute at compile-time
    std::cout << compileTimeEval(greater(5, 6)) << '\n'; // will execute at compile-time

    int x { 5 };
    std::cout << greater(x, 6) << '\n';                  // we can still call the constexpr version at runtime if we wish

    return 0;
}
```

## std::string
- C-style string variables behave oddly, avoid them, use std::string and std::string_view instead
- std::string is the easiest way to work with strings (in \<string\> header)
```
int main()
{
  std::string name {}; // empty
  std::string name2 { "Evan" }; //
  name2 = "Smedley";      // Can assign (regardless of length!)
  std::cout << "My last name is " << name2 << '\n';   // Can be outputted easily
}
```
- If std::string doesn't have enough memory to store a string it will request additional memory at runtime using dynamic memory allocation (flexible but slow)
- '>>' operator used with cin splits on whitespace so it may act differently than expected, use std::getline(...) instead (std::ws input manipulator is useful, ignores whitespace before extraction)
```
#include <iostream>
#include <string> // For std::string and std::getline

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name); // read a full line of text into name

    std::cout << "Enter your favorite color: ";
    std::string color{};
    std::getline(std::cin >> std::ws, color); // read a full line of text into color

    std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';

    return 0;
}
```
- std::string length cane be gotten using variable name and '.length()' (doesn't include \0), can also use std::ssize(), may need to STATIC CAST
- Don't pass std::string to a function by value
- It is ok to return std::string if it is a local variable, a value returned by value from another function call/operator, or a temporary value (it supports move semantics which avoids the copy)
- "Evan"s -> suffix creates std::string instead (to access suffix use 'using namespace std::string_literals')
- For constexpr strings use std::string_view instead

## std::string_view
- Lives in the \<string_view\> header (read only access to an existing string without making a copy)
- Works with std::string, c-style string or even another std::string_view
- There is no implicit conversion from std::string_view to std::string
- Suffix can be used -> 'using namespace std::string_view_literals', "Evan"sv creates std::string_view
- std::string_view has full support for constexpr
- std::string_view is preferred over 'const std::string&' (passing a pointer)
- DO NOT initialize a std::string_view with a std::string literal (it will be left dangling)
- Modification of a std::string variable will invalidate any std::string_view instances watching that string
- Be careful about returning std::string_view from a function if it is pointing at a std::string inside of the function that will be destroyed (different than c-style literals as they will exist for the entire program)
- Can use remove_prefix() and remove_suffix() to modify a std::string_view's view (like closing the curtains)