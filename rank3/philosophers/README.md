# Philosophers

## Table of Contents
1. [Overview](#overview)
2. [Usage](#usage)
3. [Rules of the Simulation](#rules-of-the-simulation)
4. [How It Works](#how-it-works)
5. [Project Structure](#project-structure)
6. [Key Data Structures](#key-data-structures)
7. [Implementation Details](#implementation-details)
   - [Argument Validation](#argument-validation)
   - [Initialisation](#initialisation)
   - [Thread Lifecycle](#thread-lifecycle)
   - [Mutex Strategy](#mutex-strategy)
   - [Time Management](#time-time-management)
   - [Death Detection](#death-detection)
   - [Output](#output)
8. [Build](#build)

---

## Overview

Philosophers simulates the classic **Dining Philosophers** problem using POSIX
threads. A configurable number of philosophers sit at a round table. Each
philosopher alternates between **thinking**, **eating**, and **sleeping**. To eat,
a philosopher must pick up both the fork to their left and the fork to their right.

The simulation ends when a philosopher dies of starvation, or — if the optional
fifth argument is provided — when every philosopher has eaten at least that many
times.

---

## Usage

```bash
make
./philosophers num_philosophers time_to_die time_to_eat time_to_sleep
./philosophers num_philosophers time_to_die time_to_eat time_to_sleep num_meals

# Examples
./philosophers 5 800 200 200
./philosophers 5 800 200 200 7
./philosophers 1 800 200 200     # single philosopher — must die
```

| Argument | Description |
|----------|-------------|
| `num_philosophers` | Number of philosophers (and forks) |
| `time_to_die` | Milliseconds before a philosopher dies if they have not started eating |
| `time_to_eat` | Milliseconds it takes to eat (holding both forks) |
| `time_to_sleep` | Milliseconds spent sleeping |
| `num_meals` *(optional)* | Stop when every philosopher has eaten this many times |

---

## Rules of the Simulation

- Each philosopher is both a thread and has a unique name (1 to N).
- There is one fork per philosopher, placed between each pair of neighbours.
- A philosopher must hold **both** adjacent forks simultaneously to eat.
- Forks are never shared — only one philosopher can hold a fork at a time.
- When a philosopher starts eating, their death timer resets.
- Philosophers do not communicate with each other.
- A death must be reported within **10 ms** of it occurring.
- The simulation stops as soon as one philosopher dies or the meal target is reached.

---

## How It Works

```
main
 │
 ├── ft_check(argv)               ← validate all arguments
 │
 ├── ft_init(args, argv, argc)    ← allocate philosophers, init mutexes
 │
 ├── ft_start(args)               ← create one thread per philosopher
 │       │                           + one monitor thread (dead watcher)
 │       │
 │       ├── [thread: philosopher N]
 │       │       └── loop: think → take forks → eat → release forks → sleep
 │       │
 │       └── [thread: dead monitor]
 │               └── loop: check last_eat timestamp for each philosopher
 │
 └── ft_join(args)                ← join all threads, free resources
```

---

## Project Structure

```
philosophers/
├── philosophers.h             # All prototypes, structs, includes
├── Makefile
└── sources/
    ├── philosophers.c         # ft_printf (log output), ft_init, main
    ├── ft_check.c             # Argument validation
    ├── ft_philo.c             # Philosopher thread function, fork logic
    ├── ft_dead.c              # Monitor thread — death detection
    ├── ft_start.c             # Thread creation and joining
    └── utils.c                # ft_strlen, ft_atoi, ft_time
```

> Note: the project implements its own `ft_atoi`, `ft_strlen`, and `ft_time`
> directly in `utils.c` — no external Libft is used.

---

## Key Data Structures

Defined in [`philosophers.h`](philosophers.h):

```c
typedef struct s_philo
{
    pthread_t       thread;
    pthread_mutex_t *fork_left;
    pthread_mutex_t *fork_right;
    long long       last_eat;
    int             lunchs;
    int             name;
}   t_philo;

typedef struct s_table
{
    t_philo         **philosophers;
    int             flag;           // global stop flag (death or meal target)
    long long       time_eat;
    long long       time_sleep;
    long long       time_die;
    long long       time_start;     // simulation start timestamp
    int             numphilo;
    pthread_t       dead;           // monitor thread handle
    int             init;           // number of philosophers that reached meal target
    pthread_mutex_t mutex_flag;     // protects flag
    pthread_mutex_t mutex_init;     // protects init counter
    pthread_mutex_t mutex_start;    // used to synchronise thread start
    pthread_mutex_t mutex_printf;   // ensures log lines are not interleaved
    pthread_mutex_t id_philo;       // protects philosopher id assignment
}   t_table;

typedef struct s_args
{
    t_table         *table;
    int             idphilo;        // this philosopher's index
    int             eats;           // optional meal target (0 if not set)
}   t_args;
```

- `t_philo` holds the per-philosopher state: its thread, its two fork pointers,
  its last-eat timestamp, and its meal count.
- `t_table` holds global simulation state and all mutex handles.
- `t_args` is passed to each thread function — it bundles the shared table
  pointer with the philosopher-specific id and meal target.

---

## Implementation Details

### Argument Validation

[`sources/ft_check.c`](sources/ft_check.c) validates that all arguments are
positive integers and that the number of philosophers is at least 1. Invalid
input prints an error and exits before any allocation.

### Initialisation

`ft_init` in [`sources/philosophers.c`](sources/philosophers.c):

1. Allocates the `t_philo **philosophers` array (NULL-terminated).
2. Allocates one `pthread_mutex_t` per philosopher (representing forks).
3. Initialises all mutexes: per-fork mutexes, `mutex_flag`, `mutex_init`,
   `mutex_start`, `mutex_printf`, and `id_philo`.
4. Sets initial values: `last_eat = time_start`, `lunchs = 0`.

Each philosopher's `fork_left` and `fork_right` are assigned so that philosopher
`i` holds fork `i` and fork `(i+1) % numphilo`, creating the circular table
arrangement.

### Thread Lifecycle

`ft_start` in [`sources/ft_start.c`](sources/ft_start.c) creates one thread per
philosopher using `pthread_create`, each running the philosopher routine defined
in [`sources/ft_philo.c`](sources/ft_philo.c).

A separate monitor thread is created that runs the death-detection loop in
[`sources/ft_dead.c`](sources/ft_dead.c).

The philosopher routine loops:

```
1. Think  (log "is thinking")
2. Lock fork_right
3. Log "has taken a fork"
4. Lock fork_left
5. Log "has taken a fork"
6. Log "is eating" → update last_eat → sleep time_to_eat
7. Unlock both forks
8. Log "is sleeping" → sleep time_to_sleep
9. Check stop flag → continue or exit
```

For the **single philosopher** edge case (no second fork available), the
philosopher picks up one fork, waits `time_to_die`, and then dies — the
monitor detects this correctly.

### Mutex Strategy

Each fork is a `pthread_mutex_t`. Before eating, a philosopher locks **both**
their adjacent fork mutexes. The order in which forks are picked up is
consistent across all philosophers to reduce the risk of deadlock:

- Even-numbered philosophers take the right fork first.
- Odd-numbered philosophers take the left fork first.

All accesses to shared fields (`flag`, `init`, `last_eat`) are protected by
their respective mutexes.

`mutex_printf` is locked during every `printf` call to prevent log lines from
being interleaved across threads.

### Time Management

`ft_time` in [`sources/utils.c`](sources/utils.c) returns the number of
milliseconds elapsed since the simulation started using `gettimeofday`:

```c
long long   ft_time(t_args *args)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - args->table->time_start);
}
```

`time_start` is recorded once during `ft_init` and subtracted from every
subsequent timestamp so all log output is relative to simulation start.

### Death Detection

The monitor thread in [`sources/ft_dead.c`](sources/ft_dead.c) loops over all
philosophers continuously. For each philosopher it checks:

```
current_time - last_eat > time_to_die  →  philosopher has died
```

When a death is detected:
1. `mutex_flag` is locked.
2. `table->flag` is set to 1 (stop signal).
3. The death message is printed.
4. `mutex_flag` is unlocked.
5. The monitor thread exits.

All philosopher threads check `table->flag` at the start of each cycle and
exit cleanly when it is set.

If the optional `num_meals` argument was provided, the monitor also checks
`table->init` — which is incremented each time a philosopher reaches the
meal target — and sets the stop flag when `init == numphilo`.

### Output

The custom `ft_printf` in [`sources/philosophers.c`](sources/philosophers.c)
wraps `printf` with `mutex_printf` to guarantee atomic log lines:

```
timestamp_ms  philosopher_name  action
```

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

---

## Build

```bash
make
make clean
make fclean
make re
```