# Common Core — Rank 1

## Table of Contents
1. [Introduction](#introduction)
2. [Born2beRoot](#born2beroot)
   - [Overview](#overview-born2beroot)
   - [Learning Goals](#learning-goals-born2beroot)
3. [ft_printf](#ft_printf)
   - [Overview](#overview-ft_printf)
   - [Learning Goals](#learning-goals-ft_printf)
4. [get_next_line](#get_next_line)
   - [Overview](#overview-get_next_line)
   - [Learning Goals](#learning-goals-get_next_line)

---

## Introduction

**Rank 1** builds directly on top of the Libft foundation developed in Rank 0.
It introduces three projects that span system administration, low-level I/O, and
variadic function design.

By the end of this rank, you will have a working virtual machine running a hardened
Linux server, a custom implementation of `printf`, and a utility capable of reading
any file or stream one line at a time — all of which will be reused in later ranks.

---

## Born2beRoot

### Overview (Born2beRoot)

Born2beRoot is a **system administration** project. The goal is to set up a minimal
virtual machine running **Debian** (or Rocky Linux) and configure it according to a
strict set of security and operational rules.

There is no C code involved — the deliverable is a running VM and the ability to
explain every configuration choice during the evaluation.

> **Key configurations:** LVM partitioning · SSH on port 4242 · UFW firewall ·
> sudo policy · password policy · cron monitoring script

### Learning Goals (Born2beRoot)

- Understand virtualisation and hypervisors (VirtualBox / UTM)
- Partition disks with LVM and understand encrypted volumes
- Manage Linux users, groups, and `sudo` privileges
- Configure and harden SSH (disable root login, custom port)
- Set firewall rules with UFW
- Write shell scripts and schedule them with `cron`
- Understand the difference between Debian and Rocky/CentOS ecosystems

---

## ft_printf

### Overview (ft_printf)

ft_printf is a **partial reimplementation** of the C standard library `printf`
function. Only a defined subset of conversion specifiers must be supported:

| Specifier | Description |
|-----------|-------------|
| `%c` | Single character |
| `%s` | String |
| `%p` | Pointer address (hex) |
| `%d` / `%i` | Signed decimal integer |
| `%u` | Unsigned decimal integer |
| `%x` / `%X` | Hexadecimal (lower / upper) |
| `%%` | Literal percent sign |

The function must handle a variable number of arguments using `<stdarg.h>` and
produce output identical to the real `printf` for all supported conversions.

> **Output:** `libftprintf.a` (static library, no buffer management required)

### Learning Goals (ft_printf)

- Master variadic functions (`va_list`, `va_arg`, `va_start`, `va_end`)
- Understand how format strings are parsed
- Practice dispatching logic through function pointers or switch statements
- Reinforce low-level character output (`write`)
- Build a reusable library that extends Libft

---

## get_next_line

### Overview (get_next_line)

get_next_line implements a single function — `get_next_line(int fd)` — that reads
from a file descriptor and returns **one line at a time**, including the trailing
`\n` when present. Repeated calls advance through the file until `NULL` is returned
at EOF.

The function must work correctly with **any buffer size** defined at compile time
via `-D BUFFER_SIZE=n` and must handle multiple file descriptors simultaneously
(bonus).

> **Key constraint:** Only one static variable is allowed per file.

### Learning Goals (get_next_line)

- Understand static variables and their lifetime across function calls
- Practice dynamic memory management with partial reads
- Handle edge cases: empty files, lines without `\n`, very large or tiny buffers
- Manage multiple open file descriptors independently (bonus)
- Read and reason about low-level I/O with `read()`

---

## Dependencies Between Projects

```
Rank 0 — Libft
    │
    ├──▶ ft_printf   (extends Libft with variadic output)
    │
    └──▶ get_next_line  (standalone I/O utility)
             │
             Both are merged into future Libft copies ──▶ Rank 2+
```

From Rank 2 onwards, `ft_printf` and `get_next_line` are typically vendored
directly into each project's `libft/` directory.