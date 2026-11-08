*This project has been created as part of the 42 curriculum by kaydan.*

# ft_printf

## Description
**ft_printf** is a custom re-implementation of the standard C library `printf()` function from `<stdio.h>`. The objective of this project is to build a static library (`libftprintf.a`) from scratch while learning how to manage variadic functions in C using the `<stdarg.h>` macros (`va_start`, `va_arg`, `va_copy`, `va_end`) and handling formatted output directly via the `write()` system call without implementing the internal buffer management of the original `printf()`.

### Supported Conversions
| Specifier | Description | Edge Case Behavior |
| :--- | :--- | :--- |
| `%c` | Prints a single character (`int` promoted). | Handles null bytes (`\0`) accurately and increments count by 1. |
| `%s` | Prints a null-terminated string (`char *`). | Prints `(null)` and returns `6` if the passed pointer is `NULL`. |
| `%p` | Prints a `void *` pointer address in base 16 with a `0x` prefix. | Prints `(nil)` and returns `5` if the pointer is `NULL` (`0`). |
| `%d` | Prints a signed decimal (base 10) integer (`int`). | Explicitly handles `INT_MIN` (`-2147483648`) without signed overflow. |
| `%i` | Prints a signed integer in base 10 (`int`). | Identical in output behavior to `%d`. |
| `%u` | Prints an unsigned decimal (base 10) integer (`unsigned int`). | Supports values up to `UINT_MAX` (`4294967295`). |
| `%x` | Prints an unsigned integer in lowercase hexadecimal (`0-9`, `a-f`). | Correctly prints `0` when the input is `0`. |
| `%X` | Prints an unsigned integer in uppercase hexadecimal (`0-9`, `A-F`). | Correctly prints `0` when the input is `0`. |
| `%%` | Prints a literal percent sign (`%`). | Safely terminates if a single trailing `%` is at the end of the format string. |

### Project Structure
* `ft_printf.h` — Header file containing function prototypes and required standard library includes (`<stdarg.h>`, `<unistd.h>`).
* `ft_printf.c` — Core `ft_printf()` function and format specifier dispatcher (`ft_check_format`).
* `ft_printf_utils.c` — Helper functions for character, string, signed/unsigned decimal, and hexadecimal printing (`ft_print_char`, `ft_print_str`, `ft_print_nbr`, `ft_print_unbr`, `ft_print_hex`).
* `ft_printf_ptr.c` — Helper functions dedicated to `unsigned long` memory address formatting (`ft_print_ptr`, `ft_print_hex2`).
* `Makefile` — Automated build script compiling the static library `libftprintf.a` with `-Wall -Wextra -Werror`.

---

## Instructions

### 1. Compilation
Clone the repository and run `make` in the root directory to compile the source files into `libftprintf.a`:
```bash
make
```

Available `Makefile` targets:
* `make` or `make all` — Compiles all `.c` files into `.o` object files and archives them into `libftprintf.a` using `ar rcs`.
* `make clean` — Removes all generated `.o` object files.
* `make fclean` — Removes all `.o` object files and the `libftprintf.a` library.
* `make re` — Cleans the build directory and recompiles the entire library from scratch.

### 2. Installation & Usage in Your Code
To use `ft_printf` in another C project, include `"ft_printf.h"` in your source file and link `libftprintf.a` during compilation:

```c
#include "ft_printf.h"

int main(void)
{
    int count;
    int num = 42;

    count = ft_printf("Hello %s! Number: %d, Hex: %x, Ptr: %p, Percent: %%\n",
                      "42 Istanbul", num, num, &num);
    ft_printf("Total printed characters: %d\n", count);
    return (0);
}
```

Compile and run the program:
```bash
cc -Wall -Wextra -Werror main.c libftprintf.a -o test_printf
./test_printf
```

---

## Algorithm and Data Structure Justification

### 1. Variadic Data Structure (`va_list`)
Because `ft_printf()` accepts a variable number of arguments of different types at runtime, a fixed parameter list cannot be used. The project utilizes the standard `va_list` data structure from `<stdarg.h>`:
* `va_start(args, format)` initializes the argument pointer right after the last fixed parameter (`format`).
* A pointer to `va_list` (`&args`) is passed to the `ft_check_format()` dispatcher so that each `va_arg(*args, type)` call advances the same underlying argument state across helper calls.
* `va_end(args)` cleans up the variadic list before returning.

### 2. Single-Pass Stream Parsing (Zero Heap Allocation)
Instead of allocating dynamic memory (`malloc`) or constructing intermediate strings on the heap, the algorithm parses the `format` string in a single linear pass ($O(n)$ time complexity where $n$ is the length of the output, and $O(1)$ auxiliary heap space):
* Regular characters are written immediately to standard output (`fd = 1`) via `write(1, format, 1)`.
* When a `%` character is encountered, the pointer advances (`*(++format)`) and delegates conversion handling to `ft_check_format()`.
* Avoiding dynamic memory allocation completely eliminates the risk of memory leaks or heap fragmentation.

### 3. Call-Stack Recursion for Base Conversion (`%d`, `%i`, `%u`, `%x`, `%X`, `%p`)
When converting an integer to base 10 or base 16 using modulo (`%`) and division (`/`), digits are naturally extracted from least significant (rightmost) to most significant (leftmost). Rather than allocating a temporary character array to reverse the digits, **recursion** is used to leverage the program's call stack as a Last-In, First-Out (LIFO) data structure:
1. The function recursively calls itself with `n / base` (`n / 10` or `n / 16`) until the most significant digit is reached (`n < base`).
2. As the recursive calls unwind, each frame prints its remainder (`n % base`) in the exact left-to-right order required.
3. Because a 32-bit `int` has at most 10 decimal digits and a 64-bit `unsigned long` pointer has at most 16 hexadecimal digits, the maximum recursion depth is bounded by 16 frames, making stack overflow impossible.

### 4. Direct ASCII Arithmetic vs. Lookup Strings
To convert numeric remainders (`0`–`15`) into characters without storing a lookup string (`"0123456789abcdef"`) in memory, direct ASCII arithmetic is applied:
* For remainders `0` through `9`: `rem + '0'` maps directly to ASCII characters `'0'`–`'9'`.
* For remainders `10` through `15`: `rem - 10 + 'a'` (for `%x` and `%p`) or `rem - 10 + 'A'` (for `%X`) maps directly to `'a'`–`'f'` or `'A'`–`'F'`.

### 5. Defensive Error Propagation
Every single `write()` call is validated against a `-1` return value. If standard output is closed or a write error occurs mid-execution, the `-1` status is immediately propagated back through the recursive frames and the main loop, halting further writes and returning `-1` just like the standard `printf()`.

---

## Resources

### Classic References
* **Linux Programmer's Manual:**
  * `man 3 printf` — Specification of format strings, conversion specifiers, and return values.
  * `man 3 stdarg` — Documentation for `va_start`, `va_arg`, `va_copy`, and `va_end`.
  * `man 2 write` — System call documentation and error return behavior.
* **GNU C Library (glibc) Manual:** [Variadic Functions](https://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html)
* **CPPReference C Documentation:** [Formatted Output (`printf`)](https://en.cppreference.com/w/c/io/fprintf)

### AI Usage Disclosure
In accordance with the 42 AI Guidelines:
* **Code Review & Edge-Case Verification:** AI was used to review the manually written implementation for edge cases, specifically verifying `write()` error propagation (`-1` return handling), variable initialization (`temp = 0` for empty format strings `""`), and platform-specific `NULL` pointer behavior (`(nil)` on Linux).
* **Norminette & Documentation Formatting:** AI assisted in verifying compliance with 42 Norminette constraints (line limits and header inclusions) and structuring this `README.md` file to fulfill all mandatory sections of the project subject.
* **Core Implementation:** All source code, variadic logic, and recursive conversion functions were written, debugged, and tested by the student.