# Semaphore Strict Counter

This project demonstrates how to use POSIX threads and a custom semaphore implementation in C to achieve strict alternation between two threads. The example prints numbers from 1 to 15 in strict odd-even order using semaphores for synchronization.

## Description

The program creates two threads:
- **Odd thread**: Prints odd numbers (1, 3, 5, ..., 15).
- **Even thread**: Prints even numbers (2, 4, 6, ..., 14).

Two custom semaphores are used to ensure that the threads strictly alternate their output. The odd thread prints a number, signals the even thread, then waits. The even thread waits for the signal, prints a number, then signals the odd thread. This guarantees the output order is always odd, even, odd, even, etc.

The custom semaphore is implemented using `pthread_mutex_t` and `pthread_cond_t` to provide basic counting semaphore functionality.

## File Structure

- `semaphore_strict_counter.c` — Main program demonstrating thread alternation and synchronization.
- `sema.h` — Header file declaring the custom semaphore API and macros.
- `sema.c` — Implementation of the custom semaphore using POSIX mutex and condition variable.

## How It Works

1. **Initialization**:  
   Two semaphores are initialized to 0. Two threads are created, one for odd numbers and one for even numbers.

2. **Odd Thread**:  
   - Prints an odd number.
   - Signals the even thread by posting to its semaphore.
   - Waits for its own semaphore before printing the next number.

3. **Even Thread**:  
   - Waits for the odd thread's signal.
   - Prints an even number.
   - Signals the odd thread by posting to its semaphore.

4. **Synchronization**:  
   The use of two semaphores ensures that only one thread prints at a time and that the order is strictly enforced.

5. **Cleanup**:  
   After both threads finish, the semaphores are destroyed and resources are released.

## How to Compile and Run

Open your terminal and run the following commands in the project directory:

```sh
gcc semaphore_strict_counter.c sema.c -o semaphore_strict_counter.exe -lpthread
./semaphore_strict_counter.exe
```

## Example Output

```
1
2
3
4
5
6
...
15
```

## Requirements

- GCC or compatible C compiler
- POSIX threads library (`-lpthread`)
- Unix-like environment (Linux, macOS)

## Educational Purpose

This code is intended for learning and demonstration of thread synchronization using semaphores in C.
