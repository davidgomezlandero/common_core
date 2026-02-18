# get_next_line

## Table of Contents
1. [Overview](#overview)
2. [Function Signature](#function-signature)
3. [How It Works](#how-it-works)
4. [Static Buffer Strategy](#static-buffer-strategy)
5. [Edge Cases](#edge-cases)
6. [Bonus — Multiple File Descriptors](#bonus--multiple-file-descriptors)
7. [Project Structure](#project-structure)
8. [Build & Test](#build--test)
9. [Key Constraints](#key-constraints)
10. [Notes](#notes)

---

## Overview

`get_next_line` is a function that reads from a file descriptor and returns one
complete line per call. A "line" is defined as a sequence of characters ending
with `\n`, or the remaining content of the file if no trailing newline exists.

The challenge lies in the fact that `read()` does not align with line boundaries —
it fills a buffer of a fixed size regardless of where newlines fall. The function
must therefore maintain **state between calls** using a static variable that holds
any leftover data from the previous read.

---

## Function Signature

```c
char *get_next_line(int fd);
```

| Parameter | Description |
|-----------|-------------|
| `fd` | File descriptor to read from (file, stdin, pipe…) |

**Returns:** A heap-allocated string containing the next line (including `\n` if
present), or `NULL` on EOF or error.

> The caller is responsible for `free()`-ing the returned string.

---

## How It Works

The function operates in three conceptual phases on every call:

### Phase 1 — Read until a newline is found

```
static char *leftover  ←  data remaining from the previous call
```

`read()` is called repeatedly with a buffer of `BUFFER_SIZE` bytes. Each chunk is
appended to `leftover` using `ft_strjoin`. Reading stops as soon as a `\n`
character is found in the accumulated string, or when `read()` returns 0 (EOF).

```
leftover before call:  "Hello, "
read() returns:        "World\nNext"
leftover after join:   "Hello, World\nNext"
                                 ↑ stop here
```

### Phase 2 — Extract the line

Everything up to and including the first `\n` (or the entire string if no `\n`)
is extracted as the return value.

```
line to return:  "Hello, World\n"
```

### Phase 3 — Update leftover

The remainder after the newline is saved back into the static variable for the
next call.

```
new leftover:  "Next"
```

If `leftover` becomes empty or NULL, the static variable is reset to NULL so that
subsequent calls trigger fresh reads.

---

## Static Buffer Strategy

```c
static char *leftover;   /* one per fd in the bonus version */
```

- The static variable **persists between calls** — it is not re-initialised on
  each invocation.
- It accumulates data that was read past the last returned newline.
- At EOF, after the last line is returned, it must be set to `NULL` to avoid
  returning stale data on a subsequent call.

### Memory lifecycle

```
1. Initial call  →  leftover = NULL
2. After read    →  leftover = strjoin(leftover, buffer)    [old freed]
3. Line found    →  leftover = remainder after \n           [old freed]
4. EOF reached   →  leftover = NULL                         [old freed]
```

Every intermediate allocation is freed before replacing `leftover`. Leaking the
old value is the most common bug in this project.

---

## Edge Cases

| Scenario | Expected behaviour |
|----------|-------------------|
| `BUFFER_SIZE = 1` | Works correctly — maximises `read()` calls |
| `BUFFER_SIZE = 10000` | Works correctly — may read past multiple newlines |
| File with no trailing `\n` | Last line returned without `\n`, next call returns `NULL` |
| Empty file | First call returns `NULL` |
| `fd = -1` or invalid | Returns `NULL` without crashing |
| Single `\n` on a line | Returns `"\n"` |
| Very long lines | Accumulates correctly across multiple reads |
| `read()` returns -1 | Returns `NULL`, frees `leftover` |

---

## Bonus — Multiple File Descriptors

The mandatory version uses a **single** static variable, which means interleaving
calls on different file descriptors produces incorrect results.

The bonus version replaces the single `char *` with a **static array** indexed by
file descriptor:

```c
static char *leftover[OPEN_MAX];
```

This allows each `fd` to maintain its own independent leftover buffer:

```c
// Interleaved reads — bonus version handles this correctly
line1 = get_next_line(fd1);   // reads from file 1
line2 = get_next_line(fd2);   // reads from file 2
line3 = get_next_line(fd1);   // continues from file 1 — no data loss
```

---

## Project Structure

```
get_next_line/
├── get_next_line.c            # Mandatory: single fd
├── get_next_line_utils.c      # Helper functions (strjoin, strchr, …)
├── get_next_line.h            # Header — prototype + BUFFER_SIZE guard
├── get_next_line_bonus.c      # Bonus: multiple fds (array of leftover)
└── get_next_line_utils_bonus.c
```

---

## Build & Test

Compile with a custom buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

Typical test pattern:

```c
int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

Test with extreme buffer sizes:

```bash
# Minimum buffer
cc -D BUFFER_SIZE=1  … && ./a.out

# Large buffer
cc -D BUFFER_SIZE=9999 … && ./a.out
```

---

## Key Constraints

- Only **one static variable** per file (mandatory part).
- No use of `lseek()`.
- The returned string must be heap-allocated — the caller frees it.
- The function must behave correctly for both files and `stdin` (fd 0).
- `BUFFER_SIZE` is defined at compile time; the code must not assume a fixed value.

---

## Notes

- The most critical helper is the string-joining function. It must correctly
  handle a `NULL` left-hand argument (first call) and free the old left-hand
  string after joining.
- Setting `leftover` to `NULL` after freeing it on EOF prevents double-free
  bugs on the next call.
- When integrated into later projects, `get_next_line` is added to the project's
  `libft/` directory and compiled as part of the static library.