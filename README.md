# Custom `malloc` Implementation

## Table of Contents
1. [Introduction](#1-introduction)
2. [Understanding Memory Allocation](#2-understanding-memory-allocation)
   - 2.1 [Static Memory Allocation](#21-static-memory-allocation)
   - 2.2 [Dynamic Memory Allocation](#22-dynamic-memory-allocation)
   - 2.3 [Mmap Allocution](#23-mmap-allocution)
3. [Design of Your malloc Implementation](#3-design-of-your-malloc-implementation)
    - 3.1 [Use of Mmap](#31-use-of-mmap)
    - 3.2 [Heap Structure](#32-heap-structure)
    - 3.3 [Structure Management](#33-structure-management)
    - 3.4 [Metadata Management](#34-metadata-management)
   		- 3.4.1 [Metadata and how to navigate through the heap](#341-metadata-and-how-to-navigate-through-the-heap)
    - 3.5 [Free List Management](#35-free-list-management)
4. [Code Walkthrough](#code-walkthrough)
5. [Testing Your `malloc`](#testing-your-malloc)
6. [How to Use](#how-to-use)

---

## 1 Introduction
This project is a custom implementation of the malloc function in C, developed entirely independently of the standard C library. 
The primary objective was to recreate the memory allocation functionality by utilizing the mmap system call, enabling efficient management of dynamic memory.

In this implementation, I have designed three distinct heap regions to cater to different memory allocation needs: **TINY**, **SMALL**, and **BIG**. 
Each heap serves specific size requirements, optimizing memory usage and performance for various scenarios. 
This structured approach allows for more granular control over memory management, enhancing the efficiency of dynamic memory allocation in C.

The subject can be found here : [malloc.pdf](https://github.com/MrMobbi/ft_malloc/blob/main/doc/malloc.pdf)

This README explains the thought process behind the design, key features of the implementation, and how to use and test it.

## 2 Understanding Memory Allocation

Memory allocation in C refers to the process of reserving or assigning memory to variables, data structures, or arrays during the execution of a program. 
This can be divided into two main categories: **static memory allocation** and **dynamic memory allocation**. 
Understanding memory allocation is crucial because memory management is a fundamental part of how C programs work.

### 2.1 Static Memory Allocation

Static memory allocation occurs before program execution. Memory for global variables, static variables, and constants (e.g., literals) is allocated statically. 
The size and location of this memory are determined at compile-time, and it does not change during the program’s lifetime.

**Characteristics:**
- **Fixed size:** Once allocated, the memory cannot grow or shrink.
- **Automatically freed:** The memory is freed when the program terminates or when the scope of the variable ends.
- **Usage:** Static or global variables, arrays declared with fixed sizes, etc.

### 2.2 Dynamic Memory Allocation

Dynamic memory allocation allows memory to be allocated at runtime (while the program is running) rather than at compile-time. 
This is essential for creating flexible data structures like linked lists, trees, and graphs, where memory requirements can change dynamically.

Key Functions:
```c
void* malloc(size_t size);
```
- Returns a pointer to the allocated memory, or NULL if it fails.
- Memory is not initialized (contains garbage values).
```c
void* calloc(size_t num_elements, size_t element_size);
```
- Allocates memory for an array of elements, and initializes them to zero.
```c
void* realloc(void *ptr, size_t new_size);
```
- Resizes previously allocated memory.
```c
void free(void *ptr);
```
- Frees dynamically allocated memory, returning it to the system for reuse.

**Characteristics:**

- **Flexible:** You can allocate memory of any size during runtime.
- **Manual management:** You are responsible for allocating and freeing memory.

### 2.3 Mmap Allocution
The mmap function in C is a system call that maps files or devices into memory, allowing programs to access these files through memory pointers. 
This provides a more efficient way to handle file I/O compared to traditional methods, 
as it allows direct reading and writing to memory addresses without needing intermediate buffers. Here’s a brief explanation of how mmap works:

**Key Features of mmap:**

**Memory Mapping:** mmap creates a mapping between a file or a device and a portion of the process's virtual memory. 
This means that the file content can be accessed like an array in memory.

**Parameters:** The function takes several parameters:
- **`addr`:** Specifies where the mapping starts. If NULL, the kernel chooses the address.
- **`len`:** The number of bytes to be mapped.
- **`prot`:** Memory protection flags (e.g., PROT_READ, PROT_WRITE).
- **`flags`:** Controls the type of mapping (e.g., MAP_PRIVATE, MAP_SHARED).
- **`fildes`:** The file descriptor of the file to be mapped.
- **`off`:** The offset in the file where mapping begins.

**Performance:** Using mmap can improve performance by reducing the overhead associated with system calls for reading and writing files. 
It allows applications to operate on files as if they are directly manipulating memory.

**Shared vs. Private Mappings:** Depending on the flags used, changes made to the memory-mapped region can be shared among processes (MAP_SHARED) 
or kept private to the process (MAP_PRIVATE), which is particularly useful for forked processes.

**File-backed vs. Anonymous Mapping:** mmap can create mappings that are backed by files (file-backed mapping) or 
anonymous mappings that are not associated with any file and can be used for dynamic memory allocation.

**Usage in Custom Memory Allocation:** In custom implementations of memory allocation, like **malloc**, 
mmap can be used to request large blocks of memory directly from the operating system.
    
## 3 Design of Your `malloc` Implementation
The core design of this custom malloc revolves around a global variable that manages all heap segments. 
These segments are categorized into three distinct heaps: `TINY`, `SMALL`, and `BIG`. 
Each heap is tailored to handle memory allocation requests of different sizes, optimizing memory usage and reducing overhead.

**Heap Segmentation**

The heap is divided into three segments based on allocation size:

- `TINY`: For very small allocations.
- `SMALL`: For moderate-sized allocations.
- `BIG`: For large allocations that require their own dedicated space.

Each heap segment is structured using the `t_heap structure`, which holds metadata about the segment's size and usage. 
The decision to use three separate heaps allows the allocator to efficiently manage memory, reducing fragmentation and improving performance.

**Page Size and Alignment**

The size of each heap segment is a multiple of the system’s page size, retrieved using the getpagesize() function, 
which typically returns `4096 bytes` (or `0x1000` bytes in hexadecimal). 
Aligning heap allocations to the page size ensures that memory is efficiently allocated and managed, 
minimizing wasted space and ensuring compatibility with the system's memory management policies.

**Metadata and Heap Structure**

The first `24 bytes` of each heap segment are reserved for storing metadata that describes the heap itself. 
This metadata includes information about the total size of the heap, the amount of memory currently in use, 
and pointers to subsequent heap segments (in case more memory is needed). 
This allows the allocator to efficiently track memory usage and manage additional heap segments if required.

**Chunk Structure**

**Alignment to 16 Bytes (0x10):**
Memory chunks are aligned to a **16-byte boundary** (0x10 in hexadecimal). 
This ensures that all pointers returned by `malloc` are aligned to 16 bytes, which is optimal for performance and required by many modern architectures. 
This alignment also ensures that the memory addresses provided are compatible with hardware and reduce issues like memory fragmentation.

**Metadata at the Start (First 8 Bytes):**

The first **8 bytes** (at offset 0x08 to 0x0a) of the chunk are reserved for metadata. 
This metadata contains crucial information about the chunk, such as its size and status (via flags). 
This information is stored in a compact format to make efficient use of the available space.
Out of these **8 bytes**, `61 bits` are used to represent the size of the memory chunk, allowing the allocator to track the exact size of each allocation.
The remaining `3 bits` are used for flags (E_FREE, E_IN_USE, etc.) that describe the current status of the chunk (whether it’s free, in use, part of a big allocation, etc.).

**Metadata (Offset 0x08 - 0x0F):**

The metadata for each chunk is stored in the first few bytes of the chunk, starting from offset **0x08**:
- The first `61 bits` (of the 8 bytes) store the size of the chunk.
- The remaining `3 bits` are used for flags that indicate the chunk’s status, such as whether it is free, in use, part of a big allocation, or undergoing resizing.

This layout allows you to efficiently track the chunk's status and size while keeping the metadata compact and aligned with the memory allocation strategy.

**Pointer Returned by malloc (Offset 0x10):**

When memory is allocated with `malloc`, the pointer returned points to offset `0x10`, which is the start of the usable memory for the program. 
This memory is `16 byte` aligned to comply with system requirements and improve access speed.
The first `16 bytes` of each chunk (from 0x00 to 0x0F) are reserved for metadata and alignment, while the memory available to the user starts at `0x10`.

### 3.1 Use of Mmap
```c
void* mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t off);
```
**Parameters:**

__`void *addr`:__ This parameter specifies the address where the mapping will begin.
If NULL is passed, the system will choose a random available address. It can also be specified explicitly, such as 0xFEED02A.

**`size_t len`:** This defines the length of the mapping in bytes. A standard memory page size is typically 4096 bytes (4 KB).

**`int prot`:** This parameter specifies the memory protection of the mapped region. There are four protection options:
- **PROT_READ:** The data can be read.
- **PROT_WRITE:** The data can be written.
- **PROT_EXEC:** The data can be executed.
- **PROT_NONE:** The data cannot be accessed.

For our custom malloc implementation, we want the allocated memory to be both readable and writable, 
so we use the combination of PROT_READ | PROT_WRITE. Using PROT_NONE is useful for preventing access to certain memory regions. 
For example, placing a PROT_NONE page before the start of the heap can help mitigate the impact of potential overflows, 
causing a segmentation fault if memory is accessed incorrectly.

**`int flags`:** This parameter controls the behavior of the mapped memory. The three primary flags are:
- MAP_SHARED: Changes made to the mapping are shared across all processes.
- MAP_PRIVATE: Changes made to the mapping are private to the process.
- MAP_FIXED: The mapping is done at the exact address specified by addr.

In the context of our malloc implementation, we will use MAP_PRIVATE. 
This ensures that if a process forks, the data remains private and will be copied, preventing shared access. 
If MAP_SHARED were used, both processes would have access to the same data, which could lead to unintended modifications.

**`int fildes`:** Is set to NULL, no file is used.

**`off_f`:** Is set to NULL, no offset used for the heap.

### 3.2 Heap structure
The heap is divided into three distinct segments to optimize the number of calls to the mmap function. 
This separation into three different mappings is in accordance with the project specifications, 
which outline the requirements for efficient memory management.

<p align="center">
  <img src="https://raw.githubusercontent.com/MrMobbi/ft_malloc/refs/heads/main/doc/2024-10-07-12%3A26%3A20-screenshot.png" alt="Logo" width: 300px; height: 100px;" > 
</p>

**Tiny :** 
The tiny heap contain at least 100 allocution of 72 bytes 
 - Page Size(N) = 8192 / 0x2000 bytes
 - Max allocution(n) = 72 bytes + 8 bytes for metadata 

**Small :**
- Page size(M) = 409600 / 0x64000 bytes
- Max allocation(m) = 4072 bytes + 8 bytes for metada

**Big :**
- Allocation start = over 4072

### 3.3 Structure Management

```c
// this struct is 24 bytes long
typedef struct s_malloc_data
{
	t_heap	*tiny;
	t_heap	*small;
	t_heap	*big;
}		t_malloc_data;
```
The **t_malloc_data** structure serves as a central management entity for the custom memory allocator. 
It holds pointers to three different heap segments—TINY, SMALL, and BIG—each designated for handling specific sizes of memory allocations. 
This organization helps optimize memory usage by categorizing allocation requests based on their size requirements. 
The total size of this structure is `24 bytes`, allowing for efficient memory management while providing quick access to the various heap segments.
```c
// this struct is 24 bytes long
typedef struct s_heap
{
	size_t	size;
	size_t	size_used;
	struct s_heap	*next;
}		t_heap;
```
The **t_heap** structure represents an individual heap segment within the allocator. 
It contains a `size field` indicating the total allocated size of the heap and a `size_used field` to track the amount of memory that has been allocated from that segment. 
Additionally, it includes a pointer to the next heap segment, enabling the implementation of a linked list structure for efficient traversal and management of heap segments. 
The size of this structure is also `24 bytes`.

When a new chunk is requested and the total of `size_used` plus the requested chunk size exceeds the current `heap size`, 
a new heap is created and linked to the existing list of heaps.

### 3.4 Metadata Management

#### 3.4.1 Metadata and how to navigate through the heap

**Heap Metadata:**

Every heap starts at address `0x00`, and the metadata for each heap occupies the first **24 bytes**. 
This means that the heap’s metadata is stored in memory from `0x00` to `0x17`.

This metadata typically includes information such as the total size of the heap, the amount of used memory, 
and a pointer to the next heap in the list. These **24 bytes** give enough space to store key data about the heap’s structure.

**First Chunk Start (at 0x18):**

The first memory chunk in the heap begins at offset `0x18`, right after the heap’s metadata. 
Each chunk also has its own metadata that occupies the first **8 bytes** of the chunk. This metadata is stored from `0x18` to `0x1F`, 
and it includes information like the chunk’s size and its status flags (whether it’s free or in use).

**Data Allocation:**

After the chunk’s metadata, the actual memory for data starts. If the program requests a memory allocation of **22 bytes**, 
the data will occupy memory from `0x20` to `0x35` (hexadecimal).
Alignment Considerations: Since chunks must be aligned to **8 byte** boundaries, any leftover space in the current chunk 
(if the requested memory doesn’t perfectly fit the alignment) will be "lost" or left unused. For instance, in this case, 
the last **2 bytes** (from `0x36` to `0x37`) will be padding to ensure that the next chunk starts at a properly aligned memory address.

**Next Chunk Start:**

The next chunk must start at the next **8-byte** aligned address. In this case, it would begin at address `0x38` 
(since the memory is aligned on **8 byte** boundaries). This ensures that each chunk starts at an aligned memory address, 
which is important for performance optimization on modern hardware.

#### 3.4.2 Flags explaination
```c
enum e_flag_metadata
{
	E_FREE	= 0,
	E_IN_USE = 1,
	E_RESIZE = 2,
	E_BIG = 4,
	E_GET_FLAGS = 7,
};
```
**Explanation of Flags:**

**E_FREE = 0:**

This flag indicates that the chunk of memory is currently free and available for allocation. 
Chunks marked with this flag are part of the heap but can be reused when a new malloc request is made.
        
Value: 0 means the chunk has no active use and is considered unused.

**E_IN_USE = 1:**

This flag marks the chunk as allocated and in use. When a chunk is being actively used by the program after a malloc call, 
this flag is set. It helps identify which memory blocks are already allocated and should not be overwritten.

Value: 1 means the chunk is actively being used by the program.

**E_RESIZE = 2:**

This flag is used to indicate that the chunk is undergoing resize operations, typically during a call to realloc. 
When memory is being resized, this flag helps manage the state of the chunk during the operation.

Value: 2 denotes that the chunk is in a transitional state due to resizing.

**E_BIG = 4:**

This flag is set for chunks allocated in the BIG heap. The BIG heap is used for very large allocations, 
usually more than a certain threshold (likely exceeding the size of TINY and SMALL allocations). 
This flag helps distinguish large allocations that require special handling or memory mapping.

Value: 4 specifies that the chunk is part of the BIG heap, distinguishing it from TINY and SMALL heaps.

**E_GET_FLAGS = 7:**

This flag is used as a mask to retrieve the current state of a chunk by performing bitwise operations. 
The value 7 (binary 111) ensures that all relevant flags (E_FREE, E_IN_USE, E_RESIZE, E_BIG) are checked at once to extract the exact state of the chunk.

Value: 7 is a bitmask used for operations where all flag values need to be read or compared.

**How the Flags Work Together:**

Each chunk in the heap will have its state tracked by one or more of these flags. For example:

- If a chunk is free, it will have the `E_FREE` flag set.
- If a chunk is in use, it will be marked with `E_IN_USE`.
- If a chunk is undergoing a resize operation, `E_RESIZE` will be set, indicating that the chunk is being resized.
- Large memory allocations use the `E_BIG` flag to mark that they are part of the **BIG** heap.

The `E_GET_FLAGS` mask is useful in cases where you need to check the current state of a chunk, allowing you to perform bitwise checks on the flags.

### 3.5 Free List Management
Describe the technique you use to track free blocks of memory (e.g., a free list, binning strategy, etc.).

## Code Walkthrough
This section breaks down the core functions and data structures in the code:

```c
- `malloc(size_t size)`: Requests a block of memory from the heap.
- `free(void *ptr)`: Returns a previously allocated block of memory.
- `realloc(void *ptr, size_t new_size)`: Resizes a previously allocated block of memory.
```
```





