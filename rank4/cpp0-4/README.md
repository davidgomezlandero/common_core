# C++ Modules — CPP00 to CPP04

## Table of Contents
1. [Overview](#overview)
2. [CPP00 — Namespaces, Classes, I/O](#cpp00)
3. [CPP01 — Memory, References, File Streams](#cpp01)
4. [CPP02 — Operator Overloading, Orthodox Canonical Form](#cpp02)
5. [CPP03 — Inheritance](#cpp03)
6. [CPP04 — Polymorphism, Abstract Classes](#cpp04)
7. [Build](#build)

---

## Overview

The C++ modules are a progressive series of exercises that introduce C++ from
scratch. Each module focuses on a single core concept and contains numbered
exercises that must be implemented cleanly, following the C++98 standard and
the **Orthodox Canonical Form** wherever applicable.

### Orthodox Canonical Form

Every class that manages resources must implement:

```cpp
class Example
{
    public:
        Example();                                // Default constructor
        Example(const Example &other);            // Copy constructor
        Example &operator=(const Example &other); // Copy assignment operator
        ~Example();                               // Destructor
};
```

---

## CPP00

**Core concept:** Namespaces, classes, member functions, access specifiers,
initialisation lists, `const` correctness, I/O streams.

### ex00 — Megaphone

A simple program that converts all input arguments to uppercase using
`std::toupper`. Introduces basic I/O with `std::cout` and argument handling
in C++.

```bash
./megaphone "shhh... I think the students are asleep..."
SHHH... I THINK THE STUDENTS ARE ASLEEP...
```

If no arguments are provided, it prints `* LOUD AND UNBEARABLE FEEDBACK NOISE *`.

### ex01 — My Awesome PhoneBook

A phonebook application built with two classes: `PhoneBook` and `Contact`.

- `PhoneBook` stores up to **8 contacts**. When full, the oldest entry is
  replaced by the newest.
- `Contact` stores: first name, last name, nickname, phone number, darkest secret.
- The program runs a loop accepting three commands:
  - `ADD` — prompts for all fields and saves the contact.
  - `SEARCH` — displays a formatted 4-column table (index, first name, last
    name, nickname). Fields longer than 10 characters are truncated with a
    trailing `.`. Then prompts for an index to display that contact's full
    details.
  - `EXIT` — terminates the program.
- Empty fields are not accepted during `ADD`.

---

## CPP01

**Core concept:** Heap vs stack allocation (`new` / `delete`), references vs
pointers, pointers to member functions, file streams (`std::ifstream` /
`std::ofstream`).

### ex00 — BraiiiiiiinnnzzzZ

`Zombie` class with a `name` and an `announce()` method.  
Two allocation strategies are demonstrated:

- `newZombie(name)` — allocates on the heap, returns the pointer (caller must
  `delete`).
- `randomChump(name)` — allocates on the stack, announces itself, and is
  destroyed automatically when the function returns.

### ex01 — Moar brainz!

`zombieHorde(int N, std::string name)` allocates an array of N `Zombie`
objects with a **single `new[]` call**, sets each zombie's name, and returns
the pointer. The caller frees with a single `delete[]`. Demonstrates array
heap allocation and why all destructors fire correctly even with a single
delete call.

### ex02 — HI THIS IS BRAIN

Declares a `std::string`, a raw pointer to it, and a reference to it.
Prints the memory address and value of all three. Illustrates that a reference
and the original variable share the same address, while a pointer holds that
address as a value.

### ex03 — Unnecessary violence

Two human classes that each attack with a `Weapon`:

- `HumanA` holds a `Weapon &` — always has a weapon, assigned at construction.
- `HumanB` holds a `Weapon *` — may have no weapon; can be assigned after
  construction.

Both call `attack()` which prints the weapon's current type. If the weapon's
type changes after assignment, the attack output reflects the new type —
demonstrating the semantics of references vs pointers.

### ex04 — Sed is for losers

Opens a file passed as argument, reads its entire content, replaces every
occurrence of string `s1` with string `s2`, and writes the result to a new
file named `<filename>.replace`. Uses only `std::ifstream` and `std::ofstream`
— `std::string::replace` is not used.

### ex05 — Harl 2.0

`Harl` class with four complaint methods: `DEBUG`, `INFO`, `WARNING`, `ERROR`.
An array of **pointers to member functions** is used to dispatch the correct
method by name — no `if/else` chain.

### ex06 — Harl filter

Extends ex05. A `switch` statement selects a level and prints that level's
output plus all levels above it. Unknown levels print
`[ Probably complaining about insignificant problems ]`.

---

## CPP02

**Core concept:** Ad-hoc polymorphism, operator overloading, Orthodox Canonical
Form, fixed-point numbers.

### ex00 — My First Class in Orthodox Canonical Form

`Fixed` class representing a fixed-point number stored as a raw `int` with
**8 fractional bits**.

Implements the full Orthodox Canonical Form. Provides `getRawBits()` and
`setRawBits()`. Every constructor, copy, assignment, and destructor call is
logged to stdout.

### ex01 — Towards a more useful fixed-point number class

Extends `Fixed` with:

- Constructor from `int` — shifts left by 8 to convert to fixed-point.
- Constructor from `float` — uses `roundf` to get the nearest representable
  value.
- `toFloat()` — converts back to `float`.
- `toInt()` — truncates to integer.
- `operator<<` overload — prints the float representation to an output stream.

### ex02 — Now we're talking

Full operator overloading added to `Fixed`:

- **Comparison:** `>`, `<`, `>=`, `<=`, `==`, `!=`
- **Arithmetic:** `+`, `-`, `*`, `/`
- **Increment/Decrement:** pre and post `++`, `--`
- **Static utilities:** `min(a, b)` and `max(a, b)` — both with `const` and
  non-`const` overloads.

---

## CPP03

**Core concept:** Inheritance, constructor/destructor chaining, access
specifiers in inheritance, method overriding without `virtual`.

### ex00 — ClapTrap

Base class `ClapTrap`:

- Attributes: `name`, `hit_points` (10), `energy_points` (10),
  `attack_damage` (0).
- Methods: `attack(target)`, `takeDamage(amount)`, `beRepaired(amount)`.
- Each action checks for sufficient HP/EP and logs a descriptive message.
- Constructor and destructor log their calls.

### ex01 — Serena, my love!

`ScavTrap` inherits publicly from `ClapTrap`.

- Default stats: 100 HP, 50 EP, 20 attack damage.
- Overrides `attack()` with its own message format.
- Adds `guardGate()` method.
- Constructor chain (`ClapTrap` → `ScavTrap`) and destructor chain in reverse
  are both visible in the logs.

### ex02 — Repetita iuvant

`FragTrap` inherits publicly from `ClapTrap`.

- Default stats: 100 HP, 100 EP, 30 attack damage.
- Adds `highFivesGuys()` method.
- Constructor and destructor chaining logged.

### ex03 — Now it's weird!

`DiamondTrap` inherits from both `ScavTrap` and `FragTrap` — the classic
**diamond problem**. Both `ScavTrap` and `FragTrap` use **virtual inheritance**
from `ClapTrap` to ensure only one `ClapTrap` subobject exists.

`DiamondTrap` has its own `name` attribute which shadows `ClapTrap::name`.
`whoAmI()` prints both `DiamondTrap::name` and `ClapTrap::name` to make the
distinction explicit.

---

## CPP04

**Core concept:** Subtype polymorphism, `virtual` functions, pure virtual
functions, abstract classes, interfaces (pure abstract classes).

### ex00 — Polymorphism

`Animal` base class with a `virtual void makeSound() const`.
`Dog` and `Cat` override it with their own sounds.

`WrongAnimal` and `WrongCat` mirror the hierarchy **without** `virtual` —
demonstrating that calling through a base pointer invokes the base method,
not the derived one. This contrast shows exactly why `virtual` is necessary
for polymorphism.

### ex01 — I don't want to set the world on fire

`Brain` class holding an array of 100 `std::string` ideas.

`Dog` and `Cat` each own a `Brain *` allocated on the heap in their
constructor and deleted in their destructor. The copy constructor and copy
assignment operator of both classes perform a **deep copy** of the `Brain` —
copying the content, not just the pointer — verified by modifying one copy and
checking the other is unaffected.

### ex02 — Abstract class

`Animal` is made **abstract** by declaring `makeSound()` as a pure virtual
function:

```cpp
virtual void makeSound() const = 0;
```

`Animal` can no longer be instantiated directly. Only `Dog` and `Cat` can,
since they provide a concrete implementation.

### ex03 — Interface & recap

A full interface-based design:

- `AMateria` — abstract base class for spells, with pure virtual `clone()` and
  `use()`.
- `Ice` and `Cure` — concrete materia types; `use()` prints a specific message,
  `clone()` returns a heap-allocated copy.
- `ICharacter` — pure abstract interface: `equip(AMateria*)`, `unequip(int)`,
  `use(int, ICharacter&)`.
- `Character` — implements `ICharacter` with up to 4 materia slots. `unequip`
  removes the pointer without deleting the materia.
- `IMateriaSource` — pure abstract interface for a materia factory.
- `MateriaSource` — learns up to 4 materia types and creates copies by name
  via `createMateria(std::string)`.

---

## Build

Each exercise has its own `Makefile`:

```bash
cd CPP00/ex00 && make && ./megaphone hello
cd CPP01/ex04 && make && ./replace input.txt old new
cd CPP04/ex03 && make && ./materia
```

All modules compile with:

```
c++ -Wall -Wextra -Werror -std=c++98
```