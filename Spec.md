# Section 1 - Introduction

## 1.1 Purpose

___
The MerC programming language, pronounced in the same way as
the English word "mercy", is a programming language intended
to address concerns over type safety, compile-time checks,
and provide additional structures and services to the programmer
to aid in development of safer programs, suitable for use
in operating systems kernels, device drivers, and for other
places where stronger safety guarantees may be desired.

## 1.2 Scope

___
This collection of documents is intended to
aid MerC developers as a reference for types, provided
data structures, and additional information about the language
at a deep level. Specifically, this specification defines the
MerC language of which all compatible compilers must implement.

This specifcation does not specify how a program must be transformed
into native code, or that the language must be implemented by
compiling to native code. Likewise, this specification does not
specify how a program is invoked, the size of a program, or
strictly define a set of minimal requirements for a program to run.

## 1.3 Terminology

___
This collection of documents which defines the language is
collectively grouped as "the specification".

The terms "must" and "shall" will be used to note that a conforming
implementation is required to implement a feature or idea.

The terms "should" and "might" will be used to note that a conforming
implementation is recommended to implement a feature or idea.

The terms "could" and "may" will be used to note that a conforming
implementation may optionally implement a feature or idea. Specifically,
MerC developers intending for maximum portability should avoid
using features listed as such, as an implementation has the pontential
to not implement such ideas or features.

Terms defined outside of section 1 in the specification shall be denoted by the 
use of an *italic* type for each appearance.

Importantly, some terms may differ in this specification than common definitions
for the same term. For example, the term "byte" has a slightly different
meaning than that of ISO 9899.

## 1.4 Important Definitions

___

#### argument
An argument is an expression in a list, separated by the comma character,
of which may be used in a function call expression, macro expression, or other
expression in which a grouping of parameters is required.

#### behavior
A method as to which some expression, calculation, or other execution appears
to outside observers, i.e, a caller to a function.

#### bit
A bit is some data storage which is capable of holding one of two possible
values.

#### byte
A byte is a grouping of 8 bits to form some data storage capable of holding
one of exactly 256 possible values.

#### character
A character is a representation of a valid character in the intended execution 
environment of the machine upon which code may execute. It may align
with the `char` data type if a character is represented with exactly
1 byte, otherwise it may align with the `wchar` datatype, if it
should be represented with more than 1 character.

#### compiler
A program which takes MerC source code, and transforms it in some meaningful way
into a method which can be executed under an intended execution environment. For
example, a compiler can be an actual compiler, where it transforms a copy of
the MerC source code into native machine instructions. A compiler can also be
an interpretter, which takes MerC source code line by line and executes it,
or compiles to a bytecode format which is then executed.

#### function
A function is an expression which may take 0 or more arguments, and may process
some number of arguments to produce some value, or no value if it's return
type is void.

#### intended execution environment
The intended execution environment is the environment for which MerC code
is intended to be run by some method, such as execution on a processor on
a specific operating system. An intended execution environment additionally
may define a native speaking language for which the encodings for characters
may be chosen.

#### parameter
A parameter is some expression belonging to the definition of a function,
of which the value is corresponding to it is used during execution of
a function.

#### value
A value is the contents of a particular object at a given time, such
as the contents placed inside a storage cell which is interpretted
as a character.

# Section 2 - Types

## 2.1 Integer types
A compliant MerC implementation must define all integer types using the 
two's complement format. Should a number exceed it's stored width, the
compiler must truncate the most significant bits, and interpret the remaining
value in the storage container as the new value of the integer. For example,
a compliant implementation will implement the addition of the integers -128 and
-1 as a value equal to 127 in an 8-bit signed integer container, but also evaluate as
-129 in a 16-bit or greater signed integer container. Likewise, with the same
integer container sizes, the value of 127 + 2 must be equal to -127.

A conforming implementation must implement the following types:
#### long
A 64-bit integer, with values ranging from -(2<sup>63</sup>) to (2<sup>63</sup> - 1)

#### int
A 32-bit integer, with values ranging from -(2<sup>31</sup>) to (2<sup>31</sup> - 1)

#### short
A 16-bit integer, with values ranging from -(2<sup>15</sup>) to (2<sup>15</sup> - 1)

#### byte
A 8-bit integer, with values ranging from -(2<sup>7</sup>) to (2<sup>7</sup> - 1)

#### ulong
A 64-bit unsigned integer, with values ranging from 0 to (2<sup>64</sup> - 1)

#### uint
A 32-bit unsigned integer, with values ranging from 0 to (2<sup>32</sup> - 1)

#### ushort
A 16-bit unsigned integer, with values ranging from 0 to (2<sup>16</sup> - 1)
This type is also aliased to be 'wchar'.

#### ubyte
A 8-bit unsigned integer, with values ranging from 0 to (2<sup>8</sup> - 1)
This type is aliased to also be 'char'.


An implementation may also provide several other types:
#### word
An unsigned integer of the same size as the size of a word on the intended
execution environment. For example, on any x86-descendant, the size of
a word is 16 bits, whereas on Aarch64 a word is 32 bits.

#### dword
An unsigned integer of the same size as 2 times the size of a word on the 
intended execution environment. For example, on any x86-descendant, the size of
a dword is 32 bits, whereas on Aarch64 a dword is 64 bits.

#### verylong
A 128-bit integer, with values ranging from -(2<sup>127</sup>) to (2<sup>127</sup> - 1)

#### uverylong
A 128-bit unsigned integer, with values ranging from 0 to (2<sup>128</sup> - 1)


## 2.2 Floating point types
Under MerC, a conforming implementation should represent all floating
point numbers in a means compliant and compatible with IEEE 754. Deviations 
from this must be made explicit by each compiler, such as an extension to the 
language, a compiler option, or some other means to enable different behavior.

A conforming implementation must implement the following types:
#### double
A number which can represent any number with exactly 64 bits of precision.
Any number which cannot be represented with that number of bits of precision
are truncated, such that the value is treated as equal to another value
which is the result of interpretting the first 64 bits of the number alone
as a value.

#### float
A number which can represent any number with exactly 32 bits of precision.
Any number which cannot be represented with that number of bits of precision
are truncated, such that the value is treated as equal to another value
which is the result of interpretting the first 32 bits of the number alone
as a value.

An implementation may also provide several other types:

#### real
A compiler-specific value for any floating point type of at least 32 bits
of precision.

#### dreal
A compiler-specific value for any floating point type which is double
the size of a `real`.

#### complex
A compiler-specific representation of a complex number.

## 2.3 Strings
A string is an object of arbitrary length, which can contain characters
for the intended execution environment. The length of the string
can be computed in linear time by searching through it sequentially until
the byte '0x00' appears. No string may contain that value anywhere but at the
end of it.

Strings act similar to other native types. A string can be added to another
string, in which the contents of the first string, except the special 0 chatacter
are copied into a new string, with the contents to the second string, except for it's
special 0 character, are added to the end. Finally, the terminating 0 character is added
to them.

Importantly, strings are allocated as heap objects, and strictly heap objects.
In a freestanding environment, strings should be substituted for another
type until a heap is initialized, such as a `char` or `wchar` array.


A conforming implementation must implement the following types:

#### string
A heap allocated grouping of characters, which is allocated linearly such
that the first letter is the first letter of the string, and the second
to last letter is the last letter of the literal string of characters.
The representation must have it's last value be equal to the value of 0.
In addition, the length of the string must be stored along with the value,
of a size of no less than 32 bits. Each character must be possible to
cast to che `char` type.

#### wstring
A heap allocated grouping of wide characters, which is allocated linearly such
that the first letter is the first letter of the string, and the second
to last letter is the last letter of the literal string of characters.
The representation must have it's last value be equal to the value of 0.
In addition, the length of the string must be stored along with the value,
of a size of no less than 32 bits. Each character must be possible to
cast to che `wchar` type.

## 2.4 Structs

## 2.5 Unions

## 2.6 Enums

## 2.7 Templates and Generics

## 2.8 Namespaces

# Section 3 - Operators

## 3.1 Unary operators
A conforming implementation must implement
the following unary operators:

#### * : Dereference
Takes the expression, and then gets the value which it points to,
regardless of the current data in the variable. The result will be
one level of indirection less than the variable applied to. For
example, if dereferencing a pointer to a pointer to an integer,
then the result will be a pointer to an integer.

The result is undefined for a non-pointer type.

#### - : Unary Negative
Takes the expression immediately after it, and inverts it's sign.
Only valid for integer types.

A compiler may exchange this as syntactic sugar from the form
{- ANY} to {0 - ANY}.

#### ++ : Increment
May be placed before or after an expression.
In the case of before the expression, the expression is
first incremented, and then processed as otherwise normal.
When this expression is processed, if it is on a variable type (as
opposed to a literal), the variable is also updated along with the
incrementation, and before the next expression using that expression.

In the case of after the expression, the expression is processed as otherwise 
normal. If it is on a variable type (as opposed to a literal), the variable is 
then updated with the incrementation.

An incrementation is defined as taking the current value, and adding 1 to it.

#### -- : Decrement
May be placed before or after an expression.
In the case of before the expression, the expression is
first decremented, and then processed as otherwise normal.
When this expression is processed, if it is on a variable type (as
opposed to a literal), the variable is also updated along with the
incrementation, and before the next expression using that expression.

In the case of after the expression, the expression is processed as otherwise 
normal. If it is on a variable type (as opposed to a literal), the variable is 
then updated with the decrementation.

A decrementation is defined as taking the current value, and subtracting 1 from 
it.

#### ! : Not
When applied to an integer argument, the result may either be 1, or be 0.
If the argument is 0, then the result of not is 1. Otherwise, not results
in 0. Not does not assign to a variable, and to be saved, must be saved
through variable assignment.

#### ! : & Address of operator
When applied to an argument, the & operator returns the address of the argument.
The resulting type is a pointer type, which is only valid for the scope of
the declaration.

If the variable is allocated on the stack, such as a temporary variable
used in a function, the result of the Address of operator is undefined
after the variable is out of scope or otherwise deallocated.


#### sizeof(x) : Size of operator
When applied to an argument, the sizeof operator returns the number of bytes
required to represent the type. sizeof must be invoked in the same manner
as a function.

The resulting type is an unsigned integer type, but may be any actual
bit length exceeding the number of bytes possible for the given machine
at a theoretical limit: 64-bits for a 64-bit virtual memory system,
or 24-bits for a 24-bit memory system without virtual memory support.
If the bit count does not match an available type, the resulting
integer must be of the closest length which fits the size as closely
as possible without losing information.

#### null?(x) : Null? check
When applied to an argument, the null? operator returns 1 if
the value was either 0 or a pointer to 0. Otherwise, it returns 0.
The resulting integer is always an unsigned 8 bit integer, which
can be resized using integer promotion to any size needed.

## 3.2 Binary operators
A conforming implementation must implement
the following binary operators:

#### & : Binary and

#### | : Binary or

#### ^ : Binary xor

#### ~ : Binary not

#### << : Binary left shift

#### >> : Binary right shift

#### >>> : Unsigned binary right shift


## 3.3 Relational operators
A conforming implementation must implement
the following relational operators:

#### == : Boolean equals

#### != : Boolean not equals

#### > : Greater than

#### < : Less than

#### >= : Greater than or equals

#### <= : Less than or equals


## 3.4 Arithmetic operators
A conforming implementation must implement
the following arithmetic operators:

#### + : Addition

#### - : Subtraction

#### * : Multiplication

#### / : Division

#### % : Modulus


## 3.5 String operators
A conforming implementation must implement
the following string operators:

#### + : Append

#### strlen(x) : Length

#### uppercase(x) : To Uppercase

#### lowercase(x) : To Lowercase


## 3.6 Logical operators
A conforming implementation must implement
the following logical operators:

#### && : Boolean and

#### || : Boolean or

#### ! : Boolean not

## 3.6 Assignment operators
A conforming implementation must implement
the following assignment operators:

#### = : Assignment

#### += : Add and then assign

#### -= : Subtract and then assign

#### *= : Multiply and then assign

#### /= : Divide and then assign

#### %= : Modulus and then assign

#### <<= : Left shift and then assign

#### >>= : Right shift and then assign

#### >>>= : Unsigned right shift and then assign

#### &= : Bitwise and and then assign

#### |= : Bitwise or and then assign

#### ^= : Bitwise xor and then assign

# Section 4 - Conditionals

## 4.1 Single argument expressions

#### if Expression
A conforming implementation must provide the `if` keyword,
which takes as a parameter another expression which must evaluate as an integer
type, followed by a block of code to execute if the expression given as an
argument is not zero.

For example, 
```c
if (1 - 1)
{
	printf("{1}\n", "Hello, world!");
}
```
would not let the printf statement execute, but
```c
if (1 - 100)
{
	if (1 + 2)
	{
		printf("{1}\n", "Hello, world!");
	}
}
```
would have the print statement execute.

#### while Expression
A conforming implementation must provide the `while` keyword,
which takes as a parameter another expression which must evaluate as an integer
type, followed by a block of code to execute while the expression given as an
argument is not zero.

For example,
```c
long x = 12;
while (x - 10 > 0)
{
	printf("{}", "Hello, world!\n");
	x--;
}
```
will have the print statement execute twice.


## 4.2 Multi-argument expressions

#### for Expression
A conformimg implementation must provide the `for` keyword,
which takes in three statements within parenthesis, and then
executes based on the status of the values declared in it.

In a loose sense, the for expression should match the form
`for (ANY;ANY;ANY) {ANY}`, where 'ANY' is any valid expression.

The first "ANY" corresponds to the initialization of a variable, such as
an index or a counter.

The second "ANY" corresponds to an expression which must evalutate as an integer
type, and the second "ANY" will be an expression which is evaluted on every
next instance of code block executed from the last ANY block: when it is equal
to zero, then the loop exits. The third ANY is the code executed at the end of
every iteration of the loop.

For example,

```c
for (int Index = 0; Index < 4; ++Index)
{
	printf("{}\n", "Hello, world!");
}
```

The print statement will execute exactly 4 times.

#### Range-based for Expression
A conforming implementation must also provide the range-based for loop extension.
This expression takes in two statements separated by a colon, of which the entirety
is surrounded by a matching pair of parenthesis. Following the convention for
the other usage of the for keyword, the range-based for shall follow the form
`for (ANY:ANY){ANY}`.

The left-side ANY in the parenthesis holds the value of an instance of the type
held in by the range item on the right side: if the right side is an array of
integers, then the left side will be a single integer within the set.

The right side item in the pair in the parenthesis contains an expression which
denotes some range it has ownership of. This can be an array, struct, string, or
other type which implements the methods `begin`, `at`,  and `end`, with `begin`
and `end` returning an iterator struct which holds onto the current location
within the holding item, and with `at` returning the specific item at that 
location.

A conforming implementation may reinterpret the range-based for expression
in terms of the normal for expression, such that the code `for (x : y){z;}`
is equivalent to `for (tmp = y.begin(); tmp != y.end(); tmp++){x = tmp.at(); z;}`,
where `tmp` is a compiler-generated temporary variable name not in use.

## 4.3 Identifiers
An identifier is a string bound to a particular variable, constant, or function.
An identifier can be identified as any character from \[a-zA-Z\], followed by
any combination of alphanumeric characters, and the characters \[!@$._?~\].

An identifier may not be redeclared as a different type within the same scope:
two definitions of an `int i` and a `long i` should be rejected by the compiler.
Likewise, redefinition of an identifier with identical types should be rejected
by the compiler. 


## 5.1 Function syntax

#### definition
A function must be declared by first defining it's return type,
followed by the name of the function, and then in parenthesis,
a list of variables which the function accepts, if any at all.

For example, all of these are valid function definitions.
```c
void doSomething()
```
```c
bool ParseFunc(struct OtherVal)
```

These definitions are, however, not.

```c
doSomething
```
```c
bool ParseFunc(struct OtherVal
```

#### prototypes
A function must be defined through a `prototype`, where the
parameters and the return type are defined before the function
body itself is defined.

Using the same examples from before,
```c
void doSomething();
```
```c
bool ParseFunc(struct OtherVal);
```

must appear before the definition of the body of a function.
These definitions may also be reproduced in other files which do
not include them, such as to allow them to share a common definition
which at link-time will be resolved, so that the compilation result
from both files use the same function.


#### function body

#### return statement

#### goto statement

#### where contract

#### try/catch

#### constant expressions

#### Lambdas