# push_swap

## Table of Contents
1. [Overview](#overview)
2. [Usage](#usage)
3. [Allowed Operations](#allowed-operations)
4. [Algorithm](#algorithm)
5. [Project Structure](#project-structure)
6. [Implementation Details](#implementation-details)
   - [Input Parsing & Validation](#input-parsing--validation)
   - [Stack Representation](#stack-representation)
   - [Sort Strategy](#sort-strategy)
   - [Cost Calculation](#cost-calculation)
7. [Build](#build)
8. [Testing](#testing)

---

## Overview

push_swap receives a list of integers via command-line arguments and prints to
stdout the **minimum sequence of stack operations** that sorts them in ascending
order on stack A. A second auxiliary stack B is available but starts empty.

---

## Usage

```bash
make
./push_swap 3 1 2
./push_swap 5 4 3 2 1
./push_swap $(shuf -i 1-100 -n 100 | tr '\n' ' ')

# Count moves generated
./push_swap 3 2 1 | wc -l
```

---

## Allowed Operations

| Operation | Effect |
|-----------|--------|
| `sa` | Swap top 2 elements of A |
| `sb` | Swap top 2 elements of B |
| `ss` | `sa` + `sb` simultaneously |
| `pa` | Push top of B onto A |
| `pb` | Push top of A onto B |
| `ra` | Rotate A upward (top → bottom) |
| `rb` | Rotate B upward (top → bottom) |
| `rr` | `ra` + `rb` simultaneously |
| `rra` | Reverse rotate A (bottom → top) |
| `rrb` | Reverse rotate B (bottom → top) |
| `rrr` | `rra` + `rrb` simultaneously |

---

## Algorithm

### Small inputs (≤ 3 elements)
Hardcoded optimal sequences — at most 3 operations.

### 5 elements
Push 2 elements to B, sort the remaining 3 in A with the small-sort routine,
then push back from B in the correct order.

### Large inputs — Cost-based algorithm

For 100–500 numbers a greedy cost-based approach is used:

1. **Push all but 3 elements from A to B**, using chunk partitioning to group
   values into rough ranges, keeping future rotation costs predictable.
2. **Sort the 3 remaining elements in A** with the small-sort routine.
3. **Push back from B to A one at a time** — each iteration picks the element
   in B with the lowest total cost to be inserted into its correct position in A:
   - Cost = rotations needed in B + rotations needed in A.
   - When both stacks need rotating in the same direction, `rr` / `rrr`
     operations are used to count them as a single move.
4. **Final rotation of A** to bring the minimum value to the top.

This consistently achieves under **700 moves for 100 numbers** and under
**5500 moves for 500 numbers**.

---

## Project Structure

```
push_swap/
├── push_swap.h            # Prototypes, t_stack struct, includes
├── Makefile
├── libft/                 # Vendored Libft + ft_printf + get_next_line
│                          # includes ft_free_matrix and ft_cpy_int_list
└── sources/
    ├── push_swap.c        # main — input parsing, validation, sort dispatch
    ├── ft_operations.c    # All 11 stack operations
    ├── ft_sort.c          # Sort dispatcher, small sorts (size ≤ 5)
    ├── ft_sort_big.c      # Cost-based algorithm for large inputs
    ├── ft_cost.c          # Cost calculation per candidate move
    ├── ft_utils.c         # Stack helpers: size, min, max, is_sorted
    └── ft_frees.c         # Memory cleanup
```

> The vendored `libft/` includes two extra utilities added specifically for
> push_swap: `ft_free_matrix.c` and `ft_cpy_int_list.c`.

---

## Implementation Details

### Input Parsing & Validation

Arguments may arrive as individual tokens or as a single quoted string.
Every token is checked for:

- Valid integer representation (no letters, no multiple signs)
- Value within `INT_MIN` – `INT_MAX` range
- No duplicate values

On any error, `"Error\n"` is printed to stderr and the program exits cleanly,
freeing all allocations.

### Stack Representation

Each stack is implemented as a linked list. Nodes store the raw value and its
**compressed index** (rank among all input values), which lets the cost algorithm
reason about relative order without comparing raw integers.

### Sort Strategy

```
Input received
    │
    ├── already sorted?     →  exit (no output)
    │
    ├── size == 2           →  at most 1 sa
    ├── size == 3           →  small_sort_3  (≤ 3 ops)
    ├── size == 4 or 5      →  push 2 to B, small_sort_3, push back
    │
    └── size > 5            →  cost-based algorithm
            ├── chunk-push to B
            ├── small_sort_3 on remaining A
            └── greedy best-cost push back to A
```

### Cost Calculation

For each element currently in B, [`sources/ft_cost.c`](sources/ft_cost.c)
calculates how many operations it would take to:

1. Bring that element to the top of B.
2. Bring its correct insertion position to the top of A.

When both stacks need to rotate in the same direction, `rr` or `rrr` reduces
the combined cost. The element with the **lowest total cost** is chosen each
iteration.

---

## Build

```bash
make
make clean
make fclean
make re
```

---

## Testing

```bash
# Verify correctness with the official checker
ARG=$(shuf -i 1-100 -n 100 | tr '\n' ' ')
./push_swap $ARG | ./checker_linux $ARG   # should print OK

# Count moves — target < 700 for 100 numbers
./push_swap $ARG | wc -l

# Target < 5500 for 500 numbers
ARG=$(shuf -i 1-500 -n 500 | tr '\n' ' ')
./push_swap $ARG | wc -l
```