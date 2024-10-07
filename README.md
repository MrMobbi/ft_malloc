# Custom `malloc` Implementation

## Table of Contents
1. [Introduction](#introduction)
2. [Understanding Memory Allocation](#understanding-memory-allocation)
3. [Design of Your `malloc` Implementation](#design-of-your-malloc-implementation)
    - [Metadata Management](#metadata-management)
    - [Free List Management](#free-list-management)
4. [Code Walkthrough](#code-walkthrough)
5. [Performance Considerations](#performance-considerations)
6. [Testing Your `malloc`](#testing-your-malloc)
7. [How to Use](#how-to-use)
8. [License](#license)

---

## Introduction
This project is a custom implementation of the `malloc` function in C, designed to manage memory allocation without relying on the standard library version. This README explains the thought process behind the design, key features of the implementation, and how to use and test it.

## Understanding Memory Allocation
In C, dynamic memory allocation allows programs to request memory at runtime using functions like `malloc`, `calloc`, `realloc`, and `free`. This section explains the basics of how memory is managed in a typical system, why `malloc` is necessary, and common strategies for handling memory allocation and deallocation.

## Design of Your `malloc` Implementation
The design of this custom `malloc` function follows a straightforward approach to memory management.

### Metadata Management
Explain how you manage metadata for each allocated block (e.g., block size, flags, pointers to next/previous blocks).

### Free List Management
Describe the technique you use to track free blocks of memory (e.g., a free list, binning strategy, etc.).

## Code Walkthrough
This section breaks down the core functions and data structures in the code:

- `malloc(size_t size)`: Requests a block of memory from the heap.
- `free(void *ptr)`: Returns a previously allocated block of memory.
- `realloc(void *ptr, size_t new_size)`: Resizes a previously allocated block of memory.

Explain each of the key functions step-by-step, showing code snippets as necessary.

```c
// Example code block
void *malloc(size_t size) {
    // Code logic here
}




## ft_malloc

void    *mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t off);

void *addr: 
The address where the map will begin, If NULL is specified it will take a random memory address, it can also be specified like this "FEED02A".

size_t len:
It's the len of the Pages what where are going to create. A standard page is 4096 bytes.

int prot:
this is the protection of the memory what we want. it exist 4 different protection :
PROT_READ   = Data can be read.
PROT_WRITE  = Data can be written.
PROT_EXEC   = Data can be executed.
PROT_NONE   = Data can be accessed.

For malloc we want our data to be read and writable so the protection will be PROT_READ | PROT_WRITE

the PROT_NONE is usefull because if data will be accessed and is none the programe will seg fault. it is use to have a page of NONE before the start of the heap like this if there is an oferflow somewhere the heap will not be accessible.

int flags:
This parameter is about the handling of the mapped data. There is 3 different flags:

MAP_SHARED  = changes are shared.
MAP_PRIVATE = changes are private.
MAP_FIXED   = Interpret addr exactly.

For malloc we will use MAP_PRIVATE because in case of a fork the data will remain private for each process and so it will be copied. if the flags was MAP_SHARED both process will have the same data.
