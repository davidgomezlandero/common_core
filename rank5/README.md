# Common Core — Rank 5

## Table of Contents
1. [Introduction](#introduction)
2. [C++ Modules — CPP05 to CPP09](#c-modules--cpp05-to-cpp09)
3. [ft_irc](#ft_irc)
4. [Inception](#inception)
5. [Dependencies](#dependencies-between-projects)

---

## Introduction

**Rank 5** introduces three challenges across two very different domains —
advanced C++ and system/network programming.

- **C++ Modules (CPP05–CPP09)** — the continuation of the C++ module series,
  covering exceptions, templates, STL containers, and type casting.
- **ft_irc** — a fully functional IRC server written in C++98 that handles
  multiple simultaneous clients over TCP using non-blocking I/O with `poll()`.
- **Inception** — a Docker-based infrastructure project where a complete
  WordPress stack (Nginx + WordPress + MariaDB) is built from scratch using
  custom Dockerfiles and orchestrated with `docker-compose`.

ft_irc is a collaborative project. The C++ modules and Inception are solo.

---

## C++ Modules — CPP05 to CPP09

Five more modules build on top of the CPP00–CPP04 foundation:

| Module | Core Concept |
|--------|-------------|
| CPP05 | Exceptions — `try`, `catch`, `throw`, custom exception classes |
| CPP06 | C++ type casting — `static_cast`, `dynamic_cast`, `reinterpret_cast`, `const_cast` |
| CPP07 | Templates — function templates, class templates, `typename` |
| CPP08 | STL containers and iterators — `vector`, `list`, `map`, `stack`, algorithms |
| CPP09 | STL in practice — `stack`, `map`, complex algorithm problems |

Each module continues to enforce the **C++98 standard** and the
**Orthodox Canonical Form** wherever applicable.

### CPP05 — Exceptions

Introduces C++ exception handling. Every exercise uses custom exception
classes that inherit from `std::exception` and override `what()`.

- `Bureaucrat` class with a `grade` (1–150). Constructors and `incrementGrade()`
  / `decrementGrade()` throw `GradeTooHighException` or `GradeTooLowException`
  when the grade is out of range.
- `Form` (later `AForm`) — abstract base class for forms that can be signed
  and executed by a `Bureaucrat` of sufficient grade. Throws
  `GradeTooLowException` if the bureaucrat's grade is insufficient.
- Concrete forms: `ShrubberyCreationForm`, `RobotomyRequestForm`,
  `PresidentialPardonForm` — each with different sign/execute grade requirements
  and specific `execute()` actions.
- `Intern` class that creates forms by name using an array of function pointers
  — no `if/else` chain.

### CPP06 — Type Casting

Covers all four C++ casts and the detection of the actual type of an object
at runtime.

- Series of exercises converting between scalar types (`char`, `int`, `float`,
  `double`) with proper overflow and special value handling
  (`-inf`, `+inf`, `nan`).
- `Base` class with virtual destructor. `A`, `B`, `C` inherit from it.
  `identify(Base*)` and `identify(Base&)` detect the actual derived type
  using `dynamic_cast` — pointer version uses the null-check pattern,
  reference version uses `try/catch`.

### CPP07 — Templates

Introduces function and class templates.

- `swap`, `min`, `max` as function templates working on any comparable type.
- `Array<T>` class template — a fixed-size array with bounds-checked
  `operator[]` (throws `std::exception` on out-of-bounds), copy constructor,
  and copy assignment operator that perform deep copies.
- `iter` function template that applies a function to every element of an
  array.

### CPP08 — STL Containers & Iterators

First contact with the STL. All exercises use standard containers and
iterators, no raw arrays.

- `easyfind` function template — searches a container for a value and returns
  an iterator, throws if not found.
- `Span` class — stores up to N integers. `addNumber()`, `shortestSpan()`,
  and `longestSpan()` computed with STL algorithms. Supports adding a range
  with iterators.
- `MutantStack<T>` — extends `std::stack` to expose iterators by inheriting
  from it and using the underlying `std::deque`.

### CPP09 — STL in Practice

Two algorithm-heavy exercises that must use STL containers chosen for
efficiency.

- `RPN` (Reverse Polish Notation) calculator using `std::stack` — evaluates
  an expression like `8 9 + 9 - 2 *` correctly, throws on invalid input.
- `PmergeMe` — sorts a sequence of positive integers using the
  **Ford-Johnson merge-insert sort algorithm**, implemented twice: once with
  `std::vector` and once with `std::deque`. Prints the unsorted input, both
  sorted outputs, and the time taken for each container.

---

## ft_irc

### Overview

ft_irc is an IRC server that handles multiple simultaneous clients over TCP/IP.
It implements the IRC protocol subset required by the subject: client
registration, channels, messaging, operators, and a set of standard IRC
commands. Clients can connect with any RFC-compliant IRC client (tested with
`irssi` and `nc`).

The server uses a single `poll()` loop to manage all file descriptors without
blocking — no threads, no `fork()`.

### Authors

| Developer | GitHub | Responsibility |
|-----------|--------|----------------|
| **davigome** | [davidgomezlandero](https://github.com/davidgomezlandero) | Server core, `poll()` loop, client lifecycle, channel management, MODE, KICK, INVITE, TOPIC |
| **Jeferson Sopan** | [@JefersonSopanR](https://github.com/JefersonSopanR) | PASS, NICK, USER, JOIN, PART, PRIVMSG, QUIT, PING, numeric replies, `fillmessage` |

### Learning Goals

- Implement a TCP server with `socket`, `bind`, `listen`, `accept`
- Manage multiple clients simultaneously with `poll()`
- Parse and implement the IRC protocol (RFC 1459)
- Design a clean C++98 class architecture for a network server
- Handle partial sends and receives on non-blocking sockets
- Implement channel modes, user modes, and operator privileges

---

## Inception

### Overview

Inception is a system administration project. The goal is to build a complete
multi-service infrastructure inside Docker containers, where each service runs
in its own container built from a custom Dockerfile based on the penultimate
stable Debian release.

The infrastructure serves a WordPress site over HTTPS via Nginx, backed by
a MariaDB database. All configuration is injected via environment variables
from a `.env` file — no hardcoded credentials anywhere.

### Learning Goals

- Write custom Dockerfiles from scratch (no pre-built images)
- Orchestrate multiple containers with `docker-compose`
- Configure Nginx as an HTTPS-only reverse proxy with TLS 1.2/1.3
- Set up MariaDB with a database and user created at container startup
- Install and configure WordPress with WP-CLI
- Manage inter-container networking and named volumes
- Use environment variables for all sensitive configuration

---

## Dependencies Between Projects

```
C++ Modules (CPP05–CPP09) — self-contained, no external dependencies

ft_irc — C++98 only, no external libraries, no libft

Inception
    └── Docker + docker-compose
            ├── Nginx     (custom Dockerfile, Debian)
            ├── WordPress (custom Dockerfile, Debian + WP-CLI)
            └── MariaDB   (custom Dockerfile, Debian)
```