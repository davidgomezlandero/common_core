# Common Core — Rank 0

## Table of Contents
1. [Introduction](#introduction)
2. [Libft](#libft)
   - [Overview](#overview)
   - [Learning Goals](#learning-goals)
   - [Project Structure](#project-structure)
   - [Function Categories](#function-categories)
   - [Bonus — Linked Lists](#bonus--linked-lists)
   - [Build](#build)
   - [Usage](#usage)
   - [Notes](#notes)

---

## Introduction

The **42 Common Core** is a project-based curriculum where each rank builds upon
the previous one. All foundational C skills developed here are reused across
subsequent ranks.

**Rank 0** contains a single mandatory project: **Libft**.  
It serves as the backbone library for many projects that follow, making it one of
the most important deliverables in the Common Core.

---

## Libft

### Overview
Libft is a custom static C library that reimplements a broad set of standard C
functions (`<string.h>`, `<ctype.h>`, `<stdlib.h>`) and adds additional utilities
not present in the standard library.

The goal is to build a reliable, well-tested, and reusable foundation that can be
linked into future 42 projects, avoiding reliance on the standard library where it
is restricted by the project norms.

> **Compiled with:** `cc -Wall -Wextra -Werror`  
> **Output:** `libft.a` (static library)

---

### Learning Goals
- Deep understanding of C memory model (stack vs heap, pointers, pointer arithmetic)
- Correct reimplementation of standard library behavior including edge cases
- Building and linking a static library using `ar`
- Designing a clean, documented public API via a header file
- Writing modular, norm-compliant C code

---

### Project Structure
```
libft/
├─ Makefile            # Build rules: all, bonus, clean, fclean, re
├─ libft.h             # Public header — full API declaration
├─ ft_*.c              # Mandatory function implementations
└─ ft_lst*_bonus.c     # Bonus: linked list implementations
```

---

### Function Categories

#### Character Classification & Conversion
| Function | Description |
|---|---|
| `ft_isalpha` | Checks if character is alphabetic |
| `ft_isdigit` | Checks if character is a digit |
| `ft_isalnum` | Checks if character is alphanumeric |
| `ft_isascii` | Checks if value is a valid ASCII character |
| `ft_isprint` | Checks if character is printable |
| `ft_toupper` | Converts character to uppercase |
| `ft_tolower` | Converts character to lowercase |

#### Memory Management
| Function | Description |
|---|---|
| `ft_memset` | Fills a memory area with a constant byte |
| `ft_bzero` | Sets a memory area to zero |
| `ft_memcpy` | Copies memory area (no overlap) |
| `ft_memmove` | Copies memory area (handles overlap) |
| `ft_memchr` | Scans memory for a byte |
| `ft_memcmp` | Compares two memory areas |
| `ft_calloc` | Allocates zero-initialised memory |

#### String Handling
| Function | Description |
|---|---|
| `ft_strlen` | Returns length of a string |
| `ft_strlcpy` | Safe string copy with size limit |
| `ft_strlcat` | Safe string concatenation with size limit |
| `ft_strchr` | Finds first occurrence of a character |
| `ft_strrchr` | Finds last occurrence of a character |
| `ft_strncmp` | Compares two strings up to n characters |
| `ft_strnstr` | Finds a substring within a bounded string |
| `ft_strdup` | Returns a heap-allocated copy of a string |
| `ft_substr` | Extracts a substring |
| `ft_strjoin` | Concatenates two strings into a new one |
| `ft_strtrim` | Trims a set of characters from both ends |
| `ft_split` | Splits a string by a delimiter character |
| `ft_strmapi` | Applies a function to each character (returns new string) |
| `ft_striteri` | Applies a function to each character (in place) |

#### Numeric Conversion
| Function | Description |
|---|---|
| `ft_atoi` | Converts a string to an integer |
| `ft_itoa` | Converts an integer to a string |

#### File Descriptor Output
| Function | Description |
|---|---|
| `ft_putchar_fd` | Writes a character to a file descriptor |
| `ft_putstr_fd` | Writes a string to a file descriptor |
| `ft_putendl_fd` | Writes a string followed by `\n` to a file descriptor |
| `ft_putnbr_fd` | Writes an integer to a file descriptor |

---

### Bonus — Linked Lists
The bonus part introduces a singly linked list using the `t_list` structure:

```c
typedef struct s_list
{
    void          *content;
    struct s_list *next;
} t_list;
```

| Function | Description |
|---|---|
| `ft_lstnew` | Creates a new list node |
| `ft_lstadd_front` | Adds a node at the beginning of the list |
| `ft_lstadd_back` | Adds a node at the end of the list |
| `ft_lstsize` | Returns the number of nodes |
| `ft_lstlast` | Returns the last node |
| `ft_lstdelone` | Deletes one node using a custom delete function |
| `ft_lstclear` | Deletes and frees all nodes |
| `ft_lstiter` | Applies a function to every node's content |
| `ft_lstmap` | Maps a function over the list, returning a new list |

---

### Build

Navigate to the `libft` directory and run:

```bash
# Build the mandatory part
make

# Build including bonus (linked list functions)
make bonus

# Remove object files
make clean

# Remove object files and the library
make fclean

# Full rebuild
make re
```

This generates `libft.a` as a static library ready to link.

---

### Usage

1. Include the header in your source file:

```c
#include "libft.h"
```

2. Compile your project linking against the library:

```bash
cc main.c -L./libft -lft -I./libft
```

> Replace paths as needed depending on your project's directory structure.

---

### Notes
- All functions are compiled with `-Wall -Wextra -Werror` — no compiler warnings are tolerated.
- Memory allocations must be verified; always check for `NULL` returns after `malloc`-based calls.
- It is strongly recommended to test with tools such as **valgrind** to detect memory leaks.
- Libft is reused and often extended in later 42 projects (ft_printf, GNL, minishell, etc.).

---

*Project completed as part of the 42 Common Core — davigome @ 42 Málaga*