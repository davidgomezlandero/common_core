# C++ Modules — CPP05 to CPP09

## Table of Contents
1. [Overview](#overview)
2. [CPP05 — Exceptions](#cpp05)
3. [CPP06 — Type Casting](#cpp06)
4. [CPP07 — Templates](#cpp07)
5. [CPP08 — STL Containers & Iterators](#cpp08)
6. [CPP09 — STL in Practice](#cpp09)
7. [Build](#build)

---

## Overview

CPP05 through CPP09 build on the foundations of CPP00–CPP04. The focus shifts
from class design and polymorphism toward C++ mechanisms that make code generic,
safe, and efficient: exception handling, type casting, templates, and the
Standard Template Library.

All modules continue to enforce **C++98** and the **Orthodox Canonical Form**
where applicable.

### Orthodox Canonical Form reminder

```cpp
class Example
{
    public:
        Example();
        Example(const Example &other);
        Example &operator=(const Example &other);
        ~Example();
};
```

---

## CPP05

**Core concept:** Exception handling — `try`, `catch`, `throw`, custom
exception classes inheriting from `std::exception`.

### ex00 — Mommy, when I grow up, I want to be a bureaucrat!

`Bureaucrat` class with:
- A `const std::string _name` (set at construction, never changes).
- An `int _grade` clamped between **1** (highest) and **150** (lowest).
- `incrementGrade()` and `decrementGrade()` that throw if the grade would go
  out of range.
- Two nested exception classes: `GradeTooHighException` and
  `GradeTooLowException`, both inheriting from `std::exception` and
  overriding `what()`.
- `operator<<` overload that prints name and grade.

```cpp
try {
    Bureaucrat b("Alice", 1);
    b.incrementGrade(); // throws GradeTooHighException
} catch (std::exception &e) {
    std::cout << e.what() << std::endl;
}
```

### ex01 — Form up, maggots!

`Form` class (later renamed `AForm` in ex02) with:
- `const std::string _name`.
- `bool _signed` (starts `false`).
- `const int _gradeToSign` and `const int _gradeToExecute`.
- `beSigned(Bureaucrat &b)` — throws `GradeTooLowException` if the
  bureaucrat's grade is insufficient.
- `Bureaucrat::signForm()` calls `beSigned()` and prints a success or failure
  message.

### ex02 — No, you need form 28B, not 28C!

`AForm` becomes an **abstract class** with a pure virtual `execute()`.
Three concrete forms are implemented:

| Form | Sign grade | Execute grade | Action |
|------|-----------|---------------|--------|
| `ShrubberyCreationForm` | 145 | 137 | Creates `<target>_shrubbery` file with ASCII trees |
| `RobotomyRequestForm` | 72 | 45 | 50% chance of successful robotomy (uses `std::rand`) |
| `PresidentialPardonForm` | 25 | 5 | Prints that the target has been pardoned |

`execute()` checks that the form is signed and the bureaucrat's grade is
sufficient before acting — throws `FormNotSignedException` or
`GradeTooLowException` otherwise.

`Bureaucrat::executeForm()` calls `execute()` and prints a success or
failure message.

### ex03 — At least this beats coffee-making

`Intern` class (no name, no grade) with a single method:

```cpp
AForm *makeForm(std::string formName, std::string target);
```

Uses an array of form names and an array of function pointers to instantiate
the correct form without any `if/else` chain. Returns `NULL` and prints an
error if the form name is unknown.

---

## CPP06

**Core concept:** C++ type casts — `static_cast`, `dynamic_cast`,
`reinterpret_cast`, `const_cast`, and serialisation.

### ex00 — Conversion of scalar types

`ScalarConverter` class with a single `static void convert(std::string)`.

Takes a string representation of a C++ literal and prints the value as
`char`, `int`, `float`, and `double`. Handles:
- Detection of the literal type (char literal `'a'`, int, float `1.0f`,
  double `1.0`).
- Special values: `nan`, `nanf`, `+inf`, `-inf`, `+inff`, `-inff`.
- Overflow and non-displayable character cases printed explicitly.

```
./convert 42
char:   '*'
int:    42
float:  42.0f
double: 42.0
```

### ex01 — Serialisation

`Uintptr_t` round-trip serialisation:

- `serialize(Data*)` — converts a pointer to `uintptr_t` using
  `reinterpret_cast`.
- `deserialize(uintptr_t)` — converts back to `Data*`.

The main verifies that the pointer recovered from deserialisation is
identical to the original.

### ex02 — Identify real type

`Base` class with a virtual destructor. `A`, `B`, `C` inherit from it.
`generate()` returns a random one of the three as `Base*`.

- `identify(Base *p)` — uses `dynamic_cast` with the null-check pattern to
  print the actual derived type.
- `identify(Base &r)` — uses `dynamic_cast` with `try/catch` on the reference
  form to print the actual derived type.

---

## CPP07

**Core concept:** Function templates and class templates.

### ex00 — Start with a few functions

Three function templates working on any type that supports `<` and `=`:

```cpp
template <typename T> void swap(T &a, T &b);
template <typename T> T   min(T const &a, T const &b);
template <typename T> T   max(T const &a, T const &b);
```

### ex01 — Iter

```cpp
template <typename T, typename F>
void iter(T *array, size_t len, F func);
```

Applies `func` to each element of `array`. Works with any type and any
callable (function pointer or function template instantiation).

### ex02 — Array

`Array<T>` class template — a fixed-size array with:
- Default constructor (size 0), constructor from `unsigned int n`.
- `operator[]` with bounds checking — throws `std::exception` if index is
  out of range.
- `size()` returning the number of elements.
- Copy constructor and copy assignment operator that perform **deep copies** —
  modifying the copy does not affect the original.

---

## CPP08

**Core concept:** STL containers (`std::vector`, `std::list`, `std::map`,
`std::stack`), iterators, and STL algorithms.

### ex00 — Easy find

```cpp
template <typename T>
typename T::iterator easyfind(T &container, int value);
```

Searches any iterable container for an integer value using `std::find`.
Returns the iterator to the found element or throws `std::exception` if
not found.

### ex01 — Span

`Span` class storing up to `N` integers:

- `addNumber(int)` — adds one number; throws if already full.
- `addNumber(iterator begin, iterator end)` — adds a range with a single
  call; throws if the range would overflow capacity.
- `shortestSpan()` — sorts a copy and finds the minimum adjacent difference.
  Throws if fewer than 2 numbers are stored.
- `longestSpan()` — returns `max - min` using `std::max_element` and
  `std::min_element`. Throws if fewer than 2 numbers are stored.

### ex02 — Mutated abomination

`MutantStack<T>` publicly inherits from `std::stack<T>` and exposes the
underlying container's iterators:

```cpp
typedef typename std::stack<T>::container_type::iterator iterator;
iterator begin();
iterator end();
```

This allows a `MutantStack` to be iterated with a range-based loop or any
STL algorithm, behaving identically to `std::stack` in all other respects.

---

## CPP09

**Core concept:** STL containers chosen for efficiency — solving real
algorithm problems with the right data structure.

### ex00 — Bitcoin Exchange

`BitcoinExchange` reads a CSV database of BTC/USD rates (`data.csv`) and an
input file of `date | amount` pairs, then prints the value of each amount in
USD on that date.

- Database loaded into `std::map<std::string, float>` — `lower_bound` is
  used to find the closest earlier date when an exact match is not found.
- Input validation: date format `YYYY-MM-DD`, amount between 0 and 1000.
- All error cases print a descriptive message to stderr and continue
  processing.

```
./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-08 => 14 = 7
Error: not a positive number.
Error: too large a number.
```

### ex01 — Reverse Polish Notation

`RPN` class that evaluates a Reverse Polish Notation expression passed as
a single command-line argument.

- Uses `std::stack<int>` to process tokens left to right.
- Operators `+`, `-`, `*`, `/` pop two operands, compute, push result.
- Division by zero and insufficient operands throw `std::exception`.
- At the end exactly one value must remain on the stack — otherwise throws.

```
./RPN "8 9 + 9 - 2 *"
16
```

### ex02 — PmergeMe

`PmergeMe` sorts a sequence of positive integers using the
**Ford-Johnson merge-insert sort algorithm**, implemented twice with two
different containers:

- `std::vector<int>` implementation.
- `std::deque<int>` implementation.

For each container the program prints:
1. The unsorted sequence.
2. The sorted sequence.
3. The time taken to sort (using `std::clock`).

```
./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After:  3 4 5 7 9
Time to process a range of 5 elements with std::vector : 0.00031 us
Time to process a range of 5 elements with std::deque  : 0.00042 us
```

The algorithm works by:
1. Pairing elements and sorting each pair.
2. Recursively sorting the larger elements of each pair.
3. Inserting the smaller elements using the **Jacobsthal sequence** to
   determine the optimal insertion order, minimising comparisons.

---

## Build

Each exercise has its own `Makefile`:

```bash
cd CPP05/ex00 && make && ./bureaucrat
cd CPP06/ex00 && make && ./convert 42
cd CPP07/ex02 && make && ./array
cd CPP08/ex01 && make && ./span
cd CPP09/ex00 && make && ./btc input.txt
cd CPP09/ex01 && make && ./RPN "3 4 + 2 *"
cd CPP09/ex02 && make && ./PmergeMe 3 5 9 7 4
```

All modules compile with:

```
c++ -Wall -Wextra -Werror -std=c++98
```