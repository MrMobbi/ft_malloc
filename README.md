# ft_malloc

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
