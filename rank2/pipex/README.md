# pipex

## Table of Contents
1. [Overview](#overview)
2. [Usage](#usage)
3. [How It Works](#how-it-works)
4. [Project Structure](#project-structure)
5. [Key Data Structure](#key-data-structure)
6. [Implementation Details](#implementation-details)
   - [Pipe Allocation](#pipe-allocation)
   - [Path Resolution](#path-resolution)
   - [Child Processes](#child-processes)
   - [File Handling](#file-handling)
   - [Error Handling & Cleanup](#error-handling--cleanup)
7. [Build](#build)

---

## Overview

pipex reproduces the shell pipe behaviour between two commands:

```bash
# Shell equivalent:
< infile cmd1 | cmd2 > outfile

# pipex:
./pipex infile "cmd1 args" "cmd2 args" outfile
```

It creates a pipe between two child processes, redirecting the output of `cmd1`
into the input of `cmd2`, reading from `infile` and writing the final output to
`outfile`.

---

## Usage

```bash
make
./pipex infile "ls -la" "grep .c" outfile
./pipex infile "cat" "wc -l" outfile
```

---

## How It Works

```
infile ──▶ [child 0: cmd1] ──pipe──▶ [child 1: cmd2] ──▶ outfile
            stdin  = infile             stdout = outfile
            stdout = pipe[write]        stdin  = pipe[read]
```

The program:

1. Allocates `argc - 3` pipe pairs via `ft_allocate_pipes`.
2. Opens `infile` and `outfile`.
3. Forks the first child — reads from `infile`, writes to the pipe.
4. The parent waits for the first child, then executes the second command
   reading from the pipe and writing to `outfile`.

---

## Project Structure

```
pipex/
├── pipex.h                    # Prototypes, includes, t_pipex struct
├── Makefile
├── libft/                     # Vendored Libft + ft_printf + get_next_line
└── sources/
    ├── pipex.c                # ft_init, ft_allocate_pipes, ft_file, main
    ├── ft_check.c             # Argument validation, command parsing
    ├── ft_check_2.c           # ft_init_pipex, ft_get_path
    └── ft_frees.c             # ft_free, ft_free_matrix
```

> Note: there is no `ft_child.c` — child process logic lives directly inside
> [`sources/pipex.c`](sources/pipex.c).

---

## Key Data Structure

Defined in [`pipex.h`](pipex.h):

```c
typedef struct s_pipex
{
    char    **here;       // here_doc limiter array (initialised to NULL)
    int     **pipes;      // array of pipe fd pairs  [num_pipes][2]
    char    **path;       // resolved binary paths per command
    int     num_pipes;    // argc - 3
}   t_pipex;
```

All state is centralised in a single `t_pipex` pointer. The struct is
zero-initialised via `ft_init_pipex` before any allocation takes place.

---

## Implementation Details

### Pipe Allocation

`ft_allocate_pipes` in [`sources/pipex.c`](sources/pipex.c) creates
`num_pipes = argc - 3` pipe pairs:

```c
void ft_allocate_pipes(int argc, t_pipex *pipex)
{
    int i;

    i = -1;
    pipex->num_pipes = argc - 3;
    pipex->pipes = malloc(pipex->num_pipes * sizeof(int *));
    while (++i < pipex->num_pipes)
        pipex->pipes[i] = malloc(2 * sizeof(int));
}
```

Each `pipes[i]` is a `[read_end, write_end]` pair. The actual `pipe()` call
is made later inside `ft_file` just before forking.

### Path Resolution

`ft_get_path` in [`sources/ft_check_2.c`](sources/ft_check_2.c) scans `envp`
for the `PATH=` entry, splits it by `:`, and probes each directory with
`access()` until the binary is found. The result is stored in `pipex->path`.

If the command is not found `pipex->path` remains `NULL`, which is handled
gracefully before calling `execvp`.

### Child Processes

`ft_child_proccess` in [`sources/pipex.c`](sources/pipex.c) is called inside
the forked child:

```
1. dup2(fd_in,            STDIN_FILENO)   ← read from infile
2. dup2(pipes[0][WRITE],  STDOUT_FILENO)  ← write to pipe
3. Close pipe ends
4. execvp(command[0], command)
```

The parent process handles the second command directly (no second fork):

```
1. wait(NULL)                             ← wait for child
2. dup2(pipes[0][READ],   STDIN_FILENO)   ← read from pipe
3. dup2(fd_out,           STDOUT_FILENO)  ← write to outfile
4. execvp(command[0], command)
```

### File Handling

`ft_file` in [`sources/pipex.c`](sources/pipex.c) opens:
- `infile` with `O_RDONLY`
- `outfile` with `O_WRONLY | O_CREAT | O_TRUNC` with permissions `0777`

The pipe is created with `pipe(pipex->pipes[0])` inside this same function,
immediately before the `fork()`.

### Error Handling & Cleanup

- [`sources/ft_frees.c`](sources/ft_frees.c) provides `ft_free` which iterates
  `pipex->path`, frees `pipex->here`, `pipex->path`, `pipex->pipes`, and
  `pipex` itself.
- `ft_free_matrix` is the generic 2D array free reused throughout the project
  for `ft_split` results.

---

## Build

```bash
make
make clean
make fclean
make re
```