# Common Core — Rank 4

## Table of Contents
1. [Introduction](#introduction)
2. [C++ Modules](#c-modules)
3. [cub3D](#cub3d)
4. [NetPractice](#netpractice)
5. [Dependencies](#dependencies-between-projects)

---

## Introduction

**Rank 4** introduces three completely different challenges:

- **C++ Modules (CPP00–CPP04)** — a progressive series of exercises that
  teach the fundamentals of C++ and Object-Oriented Programming, starting
  from namespaces and classes all the way through polymorphism and abstract
  classes.
- **cub3D** — a first-person 3D renderer built in C using the **MLX42**
  graphical library, implementing the raycasting technique popularised by
  Wolfenstein 3D.
- **NetPractice** — a networking exercise where a series of broken network
  diagrams must be fixed by applying TCP/IP addressing and subnetting concepts.

The C++ modules are individual and self-contained. cub3D is a collaborative
project developed with the same partner as Minishell
([Jorgetrujilloroman](https://github.com/Jorgetrujilloroman)).
NetPractice is a solo exercise with no code involved — only configuration.

---

## C++ Modules

Five modules are covered at this rank, each introducing a new layer of C++:

| Module | Core Concept |
|--------|-------------|
| CPP00 | Namespaces, classes, member functions, I/O streams |
| CPP01 | Memory allocation, references, pointers to members, file streams |
| CPP02 | Ad-hoc polymorphism, operator overloading, Orthodox Canonical Form |
| CPP03 | Inheritance |
| CPP04 | Subtype polymorphism, abstract classes, interfaces |

---

## cub3D

cub3D is a first-person 3D maze renderer. A map is loaded from a `.cub` file,
validated, and rendered in real time using the **raycasting** technique.

The project was developed collaboratively:

| Developer | GitHub | Responsibility |
|-----------|--------|----------------|
| **davigome** | [davidgomezlandero](https://github.com/davidgomezlandero) | Parsing — `.cub` file reading, texture/color extraction, map validation, flood-fill path check |
| **Jorge Trujillo** | [Jorgetrujilloroman](https://github.com/Jorgetrujilloroman) | Raycasting — DDA algorithm, wall rendering, textured walls, player movement, minimap |

---

## NetPractice

NetPractice is a browser-based exercise consisting of 10 progressive levels,
each presenting a broken network diagram that must be fixed by correctly
configuring IP addresses, subnet masks, and routes. There is no code — the
deliverable is a correct network configuration for each level.

---

## Dependencies Between Projects

```
C++ Modules — self-contained, no external dependencies

cub3D
    ├──▶ libft/   (vendored Libft + ft_printf + get_next_line)
    └──▶ MLX42/   (git submodule — OpenGL graphical library)

NetPractice — no code, no dependencies
```