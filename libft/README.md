*This project has been created as part of the 42 curriculum by kaydan.*

# Libft

## Description
**Libft** is the first project of the 42 curriculum. The goal of this project is to recreate a set of standard C library (`libc`) functions as well as additional utility functions and linked list manipulation mechanisms.

By re-implementing these fundamental functions from scratch without relying on external libraries, this project deepens understanding of C programming, dynamic memory management (`malloc`/`free`), pointer arithmetic, and data structures. The resulting static library (`libft.a`) serves as a reusable foundation for future 42 projects.

---

## Library Functions

### 1. Libc Functions
Standard C functions reimplemented with identical behavior:

| Function | Description |
| :--- | :--- |
| `ft_isalpha` | Checks for an alphabetic character. |
| `ft_isdigit` | Checks for a digit (`0` through `9`). |
| `ft_isalnum` | Checks for an alphanumeric character. |
| `ft_isascii` | Checks whether `c` fits on the ASCII character set. |
| `ft_isprint` | Checks for any printable character. |
| `ft_strlen` | Calculates the length of a string. |
| `ft_memset` | Fills memory with a constant byte. |
| `ft_bzero` | Erases the data in `n` bytes of the memory starting at the location pointed to by `s` by writing zeros. |
| `ft_memcpy` | Copies memory area. |
| `ft_memmove` | Copies memory area with overlap protection. |
| `ft_strlcpy` | Size-bounded string copying. |
| `ft_strlcat` | Size-bounded string concatenation. |
| `ft_toupper` | Converts char to uppercase. |
| `ft_tolower` | Converts char to lowercase. |
| `ft_strchr` | Locates character in string (first occurrence). |
| `ft_strrchr` | Locates character in string (last occurrence). |
| `ft_strncmp` | Compares two strings up to `n` bytes. |
| `ft_memchr` | Scans memory for a character. |
| `ft_memcmp` | Compares memory areas. |
| `ft_strnstr` | Locates a substring in a string. |
| `ft_atoi` | Converts a string to an integer. |
| `ft_calloc` | Allocates memory and sets its bytes to zero. |
| `ft_strdup` | Duplicates a string using dynamic memory allocation. |

### 2. Additional Utility Functions
Functions that are either not present in `libc` or are present in a different form:

| Function | Description |
| :--- | :--- |
| `ft_substr` | Extracts a substring from a string. |
| `ft_strjoin` | Concatenates two strings into a new dynamically allocated string. |
| `ft_strtrim` | Trims specified characters from the beginning and end of a string. |
| `ft_split` | Splits a string into an array of substrings using a delimiter character. |
| `ft_itoa` | Converts an integer to a string representation. |
| `ft_strmapi` | Applies a function to each character of a string to create a new string. |
| `ft_striteri` | Applies a function to each character of a string in-place. |
| `ft_putchar_fd` | Outputs a character to a given file descriptor. |
| `ft_putstr_fd` | Outputs a string to a given file descriptor. |
| `ft_putendl_fd` | Outputs a string followed by a newline to a given file descriptor. |
| `ft_putnbr_fd` | Outputs an integer to a given file descriptor. |

### 3. Linked List Functions
Functions to manipulate singly linked lists (`t_list` structure):

| Function | Description |
| :--- | :--- |
| `ft_lstnew` | Creates a new list node. |
| `ft_lstadd_front` | Adds a node to the beginning of the list. |
| `ft_lstsize` | Counts the number of nodes in a list. |
| `ft_lstlast` | Returns the last node of a list. |
| `ft_lstadd_back` | Adds a node to the end of the list. |
| `ft_lstdelone` | Deletes and frees a single node using a deletion function. |
| `ft_lstclear` | Deletes and frees a list and all its nodes. |
| `ft_lstiter` | Iterates over a list and applies a function to each node's content. |
| `ft_lstmap` | Iterates over a list, applies a function to create a new mapped list. |

---

## Instructions

### Compilation

Clone the repository and compile the library using `make`:

```bash
git clone <repository_url>
cd libft
make

This will compile all source files (.c) into object files (.o) and generate the static library file libft.a.

Available Makefile Rules:

make or make all : Compiles the library libft.a.

make clean : Removes generated object (.o) files.

make fclean : Removes object files and the libft.a static library.

make re : Recompiles the entire project (fclean + all).

Using libft.a in Your Project
To use Libft in your C project, include libft.h in your code and link libft.a during compilation:

#include "libft.h"

int main(void)
{
    ft_putstr_fd("Hello, Libft!\n", 1);
    return (0);
}
Compile with cc:
cc main.c -L. -lft -o my_program

Resources
C Library - <string.h>
C Library - <stdlib.h>
Linux man pages (man malloc, man memcpy, man 3 printf, etc.) — Official manual pages for standard C library behavior and specifications.

AI Usage
Artificial Intelligence (LLMs) was utilized as an interactive tutor and debugging assistant throughout this project in the following ways:

Concept Clarification: Explaining complex concepts such as pointer arithmetic, integer overflow protection in ft_calloc, double pointers (char **) in ft_split, and linked list node linking mechanics.

Edge Case Analysis: Identifying potential memory leaks, buffer overflows, and null-pointer dereferences in memory management functions (ft_memcpy, ft_memmove, ft_lstmap).

Code Review & Refactoring: Reviewing functions to ensure strict compliance with the 42 Norminette coding style and optimization rules.

This README was prepared with the assistance of AI.
