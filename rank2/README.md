# Common Core — Rank 2

## Table of Contents
1. [Introduction](#introduction)
2. [pipex](#pipex)
3. [push_swap](#push_swap)
4. [so_long](#so_long)
5. [Dependencies](#dependencies-between-projects)

---

## Introduction

**Rank 2** is where the Common Core shifts from isolated utility functions to
complete programs with real Unix concepts at their core.

Three projects are tackled:

- **pipex** — reproduces the shell pipe operator using Unix process and I/O primitives.
- **push_swap** — sorts a stack of integers using a constrained set of operations.
- **so_long** — a small 2D tile-based game built with the MLX42 graphical library.

All three projects vendor a copy of **Libft** (with `ft_printf` and `get_next_line`
integrated) as their internal static library, compiled from each project's own
`libft/` directory.

---

## pipex

### Overview

pipex reproduces the behaviour of the shell pipe:

```bash
< infile cmd1 | cmd2 > outfile
# is equivalent to:
./pipex infile "cmd1" "cmd2" outfile
```

The program forks two child processes, sets up an anonymous pipe between them,
and redirects stdin/stdout using `dup2`. A `t_pipex` struct centralises all
state — pipe file descriptors and command paths.

### Learning Goals

- Understand `fork()`, `execvp()`, `pipe()`, `dup2()`, and `wait()`
- Manage file descriptors correctly across parent and child
- Parse `PATH` from `envp` to locate command binaries
- Coordinate parent and child processes

---

## push_swap

### Overview

push_swap receives a list of integers and prints the minimum sequence of stack
operations needed to sort them in ascending order on stack A, using an auxiliary
stack B.

The implementation handles small inputs with hardcoded optimal sequences and
large inputs with a cost-based algorithm, consistently staying within the move
limits required for full evaluation score.

### Learning Goals

- Design an efficient sorting algorithm under strict operation constraints
- Parse and validate integer input robustly (duplicates, overflow, bad input)
- Work with stack data structures implemented as linked lists
- Analyse and optimise operation counts

---

## so_long

### Overview

so_long is a 2D tile-based game where the player must collect all collectibles on
a map loaded from a `.ber` file and reach the exit. Rendering is handled by
**MLX42** (OpenGL + GLFW), included as a git submodule.

The map is fully validated before the window opens: shape, border integrity,
character counts, and path reachability via flood-fill.

The project includes a **bonus version** with additional features compiled into a
separate binary.

### Learning Goals

- Use MLX42 to render textures and handle keyboard events
- Parse and validate a 2D map from a `.ber` file
- Implement movement, collectible, and exit logic
- Manage the MLX42 event loop and clean up all resources on exit

---

## Dependencies Between Projects

```
Rank 0 — Libft
Rank 1 — ft_printf · get_next_line
    │
    └── vendored into each project's libft/
            ├──▶ pipex/libft/
            ├──▶ push_swap/libft/
            └──▶ so_long/libft/

so_long also depends on:
    └──▶ MLX42  (git submodule — OpenGL graphical library)
```