# Minishell

## Table of Contents
1. [Overview](#overview)
2. [Usage](#usage)
3. [Supported Features](#supported-features)
4. [How It Works](#how-it-works)
5. [Project Structure](#project-structure)
6. [Key Data Structures](#key-data-structures)
7. [Implementation Details](#implementation-details)
   - [Lexer](#lexer)
   - [Parser](#parser)
   - [Execution](#execution)
   - [Redirections](#redirections)
   - [Pipes](#pipes)
   - [Environment Variables](#environment-variables)
   - [Built-in Commands](#built-in-commands)
   - [Signal Handling](#signal-handling)
   - [Exit Status](#exit-status)
8. [Build](#build)

---

## Overview

Minishell is a functional Unix shell written in C that replicates the core
behaviour of **bash**. It reads commands from an interactive prompt (using
`readline`), parses them, and executes them — supporting pipes, redirections,
environment variables, signal handling, and a set of built-in commands.

### Authors

This project was built collaboratively by two developers, each owning a
well-defined half of the implementation:

| Developer | GitHub | Responsibility |
|-----------|--------|----------------|
| **davigome** | [davidgomezlandero](https://github.com/davidgomezlandero) | Parsing — lexer, token list, AST construction, quote handling, variable expansion |
| **Jorge Trujillo** | [Jorgetrujilloroman](https://github.com/Jorgetrujilloroman) | Execution — process management, pipes, redirections, built-ins, signal handling |

---

## Usage

```bash
make
./minishell
```

Minishell presents a prompt and accepts commands interactively, behaving like
a simplified bash:

```bash
minishell$ ls -la | grep .c
minishell$ echo "Hello $USER"
minishell$ cat < infile | wc -l > outfile
minishell$ export MY_VAR=42
minishell$ echo $MY_VAR
minishell$ cd ..
minishell$ exit
```

---

## Supported Features

| Feature | Supported |
|---------|-----------|
| Interactive prompt via `readline` | ✅ |
| Command history | ✅ |
| Absolute and relative paths | ✅ |
| `PATH` resolution | ✅ |
| Single quotes `'...'` (no expansion) | ✅ |
| Double quotes `"..."` (variable expansion) | ✅ |
| Environment variable expansion `$VAR` | ✅ |
| Exit status expansion `$?` | ✅ |
| Pipes `\|` | ✅ |
| Input redirection `<` | ✅ |
| Output redirection `>` | ✅ |
| Append redirection `>>` | ✅ |
| Here-doc `<<` | ✅ |
| `SIGINT` (Ctrl+C) | ✅ |
| `SIGQUIT` (Ctrl+\\) | ✅ |
| `EOF` (Ctrl+D) | ✅ |
| Built-in: `echo` | ✅ |
| Built-in: `cd` | ✅ |
| Built-in: `pwd` | ✅ |
| Built-in: `export` | ✅ |
| Built-in: `unset` | ✅ |
| Built-in: `env` | ✅ |
| Built-in: `exit` | ✅ |

---

## How It Works

```
readline(prompt)
    │
    ├── Lexer  →  token list  (words, pipes, redirections, quotes)
    │
    ├── Parser  →  command list / AST
    │       └── variable expansion, quote removal
    │
    └── Executor
            │
            ├── built-in?  →  execute directly in current process
            │
            └── external command?
                    ├── resolve path via PATH
                    ├── fork()
                    │     ├── child: set up redirections + execve
                    │     └── parent: waitpid
                    └── pipes: chain N children via pipe() + dup2()
```

---

## Project Structure

```
minishell/
├── minishell.h               # All prototypes, structs, includes
├── Makefile
├── libft/                    # Vendored Libft + ft_printf + get_next_line
└── sources/
    ├── minishell.c           # main, prompt loop, readline integration
    │
    │   — Parsing (Jorge Trujillo) —
    ├── ft_lexer.c            # Tokenise raw input into token list
    ├── ft_lexer_2.c          # Lexer helpers
    ├── ft_lexer_3.c          # Quote and word boundary handling
    ├── ft_parser.c           # Build command structs from token list
    ├── ft_parser_2.c         # Parser helpers
    ├── ft_expand.c           # $VAR and $? expansion
    ├── ft_expand_2.c         # Expansion edge cases
    ├── ft_quotes.c           # Quote state machine
    │
    │   — Execution (davigome) —
    ├── ft_exec.c             # Execution dispatcher
    ├── ft_exec_2.c           # External command execution
    ├── ft_pipe.c             # Multi-pipe orchestration
    ├── ft_redir.c            # Redirection setup (< > >> <<)
    ├── ft_here_doc.c         # Here-doc implementation
    ├── ft_signals.c          # Signal handlers (SIGINT, SIGQUIT)
    │
    │   — Built-ins (davigome) —
    ├── ft_echo.c             # echo [-n]
    ├── ft_cd.c               # cd [path]
    ├── ft_pwd.c              # pwd
    ├── ft_export.c           # export [name=value]
    ├── ft_unset.c            # unset [name]
    ├── ft_env.c              # env
    ├── ft_exit.c             # exit [status]
    │
    │   — Utilities —
    ├── ft_env_utils.c        # Environment list management
    ├── ft_frees.c            # Memory cleanup
    └── ft_errors.c           # Error messages
```

---

## Key Data Structures

```c
// One token produced by the lexer
typedef struct s_token
{
    char            *value;
    int             type;       // WORD, PIPE, REDIR_IN, REDIR_OUT, …
    struct s_token  *next;
}   t_token;

// One command node after parsing
typedef struct s_cmd
{
    char            **args;     // NULL-terminated argument array
    char            **redirs;   // redirection targets
    int             *redir_types;
    int             here_doc;
    struct s_cmd    *next;      // next command in the pipeline
}   t_cmd;

// Global shell state
typedef struct s_shell
{
    t_cmd           *cmds;      // parsed command list
    char            **envp;     // current environment
    int             exit_status;
    int             in_pipe;
}   t_shell;
```

---

## Implementation Details

### Lexer

The lexer in [`sources/ft_lexer.c`](sources/ft_lexer.c) iterates over the raw
input string character by character, producing a linked list of tokens. It
identifies:

- **Words** — plain arguments or command names.
- **Pipes** `|`
- **Redirections** `<`, `>`, `>>`, `<<`
- **Quoted strings** — single and double quoted segments are kept intact and
  flagged so the parser knows not to split them further.

### Parser

The parser in [`sources/ft_parser.c`](sources/ft_parser.c) walks the token list
and builds a linked list of `t_cmd` nodes — one per pipeline stage. It handles:

- Argument accumulation per command.
- Redirection target extraction.
- Here-doc marker detection.
- Variable expansion via [`sources/ft_expand.c`](sources/ft_expand.c).
- Quote removal once expansion is complete.

### Execution

[`sources/ft_exec.c`](sources/ft_exec.c) receives the parsed command list and:

1. Checks if the single command is a built-in → runs it in the current process.
2. If there is more than one command (pipeline), delegates to
   [`sources/ft_pipe.c`](sources/ft_pipe.c).
3. For a single external command, calls `fork()` → child sets up redirections
   with `dup2`, resolves the binary via `PATH`, and calls `execve`.
4. The parent calls `waitpid` and stores the exit status in `shell->exit_status`.

### Redirections

[`sources/ft_redir.c`](sources/ft_redir.c) applies all redirections for a
command before `execve`:

- `<` — `open(file, O_RDONLY)` → `dup2` onto stdin.
- `>` — `open(file, O_WRONLY|O_CREAT|O_TRUNC)` → `dup2` onto stdout.
- `>>` — `open(file, O_WRONLY|O_CREAT|O_APPEND)` → `dup2` onto stdout.
- `<<` — here-doc: reads from stdin until the delimiter is matched, writes to
  a temporary pipe, and `dup2`s the read end onto stdin.

### Pipes

[`sources/ft_pipe.c`](sources/ft_pipe.c) orchestrates multi-command pipelines:

1. For N commands, create N-1 `pipe()` pairs.
2. Fork one child per command.
3. Each child `dup2`s the appropriate read/write ends and closes all others.
4. The parent closes all pipe ends and waits for all children.

### Environment Variables

The environment is stored as a `char **envp` copy taken from `main`. Built-ins
that modify the environment (`export`, `unset`, `cd`) update this copy directly.
The helper functions in [`sources/ft_env_utils.c`](sources/ft_env_utils.c)
handle searching, adding, updating, and removing entries.

Variable expansion in double quotes and bare words resolves `$VAR` by scanning
the `envp` array.

### Built-in Commands

All built-ins are executed in the **current process** (no fork) when they appear
as the sole command in the input, so that changes to the environment and working
directory persist. Inside a pipeline they are forked like any other command.

| Command | Behaviour |
|---------|-----------|
| `echo [-n]` | Prints arguments; `-n` suppresses the trailing newline |
| `cd [path]` | Changes directory; updates `PWD` and `OLDPWD` in `envp` |
| `pwd` | Prints the current working directory |
| `export [name=value]` | Adds or updates an environment variable |
| `unset [name]` | Removes a variable from the environment |
| `env` | Prints all exported environment variables |
| `exit [status]` | Exits minishell with the given status code |

### Signal Handling

[`sources/ft_signals.c`](sources/ft_signals.c) installs signal handlers with
`sigaction`:

| Signal | Interactive mode | Child running |
|--------|-----------------|---------------|
| `SIGINT` (Ctrl+C) | New prompt on next line, `$?` = 130 | Forwarded to child |
| `SIGQUIT` (Ctrl+\\) | Ignored | Forwarded to child |
| `EOF` (Ctrl+D) | Exits minishell cleanly | — |

### Exit Status

Every command, built-in, and signal updates `shell->exit_status`. This value
is exposed through `$?` expansion and returned by `exit` when no argument is
provided. The exit status of the last foreground command is preserved correctly
across pipelines.

---

## Build

```bash
make
make clean
make fclean
make re
```

> `readline` must be installed on the system:
> ```bash
> sudo apt-get install libreadline-dev
> ```