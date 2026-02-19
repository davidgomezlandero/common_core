# Common Core — Rank 3

## Table of Contents
1. [Introduction](#introduction)
2. [Minishell](#minishell)
3. [Philosophers](#philosophers)
4. [Dependencies](#dependencies-between-projects)

---

## Introduction

**Rank 3** introduces two of the most complex projects in the Common Core.

- **Minishell** — a fully functional Unix shell built from scratch in C, handling
  parsing, execution, pipes, redirections, and built-in commands.
- **Philosophers** — a concurrency simulation of the classic Dining Philosophers
  problem using POSIX threads and mutexes.

Both projects demand a deep understanding of Unix process management and, in the
case of Philosophers, concurrent programming.

---

## Minishell

### Overview

Minishell is a functional Unix shell that replicates the core behaviour of
**bash**. It reads user input from a prompt, parses it into commands, and
executes them — supporting pipes, redirections, environment variables, signals,
and a set of built-in commands implemented from scratch.

The project is split between two developers: one focused on **parsing** and one
on **execution**.

### Learning Goals

- Understand how a shell works end-to-end: lexing, parsing, execution
- Manage processes with `fork`, `execve`, `waitpid`
- Handle pipes and redirections with `pipe`, `dup2`
- Implement signal handling (`SIGINT`, `SIGQUIT`)
- Manage an environment variable table in memory
- Implement built-in commands without calling external binaries

---

## Philosophers

### Overview

Philosophers simulates the classic **Dining Philosophers** problem. A given
number of philosophers sit at a round table, each needing two forks to eat.
The program must prevent deadlock and starvation while correctly detecting
when a philosopher has died.

Each philosopher runs in its own **POSIX thread**. Forks are represented as
**mutexes**. A dedicated monitor thread watches for deaths and the optional
meal-count stopping condition.

### Learning Goals

- Create and manage POSIX threads with `pthread_create` and `pthread_join`
- Protect shared data with `pthread_mutex_t`
- Avoid data races and deadlocks
- Implement precise time management with `gettimeofday`
- Reason about concurrent execution and synchronisation

---

## Dependencies Between Projects

```
Rank 0 — Libft
Rank 1 — ft_printf · get_next_line
    │
    └── Minishell vendors its own libft/
            └──▶ minishell/libft/

Philosophers has no libft — only the C standard library and pthreads.
```