# Basic Argument Parser

This is a small C argument parser designed to detect single-letter command-line style flags.

It supports arguments such as:

```sh
command -a -b -C
```

or combined flags such as:

```sh
command -abc -XYZ
```

The parser stores which flags were found using a bitmap, allowing quick lookup later with `is_arg()`.

---

## How It Works

The parser uses a bitmap to track whether a letter argument has been seen.

Lowercase letters are stored in indexes `0–25`:

```text
'a' -> 0
'b' -> 1
...
'z' -> 25
```

Uppercase letters are stored in indexes `26–51`:

```text
'A' -> 26
'B' -> 27
...
'Z' -> 51
```

The bitmap allocates 7 bytes, which gives 56 total bits. This is enough to store all 52 uppercase and lowercase English letters.

---

## Usage

Example:

```c
#include <stdio.h>
#include "argument_parser.h"

int main(void) {
    char input[] = "ls -a -l -R";

    get_args(input);

    if (is_arg('a')) {
        printf("Argument -a was found\n");
    }

    if (is_arg('l')) {
        printf("Argument -l was found\n");
    }

    if (is_arg('R')) {
        printf("Argument -R was found\n");
    }

    if (!is_arg('z')) {
        printf("Argument -z was not found\n");
    }

    return 0;
}
```

Output:

```text
Argument -a was found
Argument -l was found
Argument -R was found
Argument -z was not found
```

---

## Supported Input Format

This parser expects a command-style string where the first token is the command and later tokens are arguments.

Examples:

```text
ls -a -l
```

```text
grep -i -n
```

```text
program -abc
```

The first token is skipped because it is assumed to be the command name.

For example:

```text
ls -al
```

will mark both `a` and `l` as active arguments.

---

## Functions

### `get_args`

```c
void get_args(char *line);
```

Parses a command-line string and stores all detected letter flags in the bitmap.

Example:

```c
char line[] = "ls -a -l";
get_args(line);
```

After calling this, `is_arg('a')` and `is_arg('l')` will return true.

---

### `is_arg`

```c
int is_arg(char arg);
```

Checks whether a given letter argument was found.

Returns:

```text
1 if the argument was found
0 if the argument was not found
```

Example:

```c
if (is_arg('a')) {
    printf("-a was passed\n");
}
```

---

## Implementation Details

The parser uses this bitmap layout:

```text
Index 0-25   : lowercase letters a-z
Index 26-51  : uppercase letters A-Z
Index 52-55  : unused
```

The bitmap is allocated lazily. This means memory is only allocated when `bitmap_set()` or `bitmap_get()` is first called.

```c
bitmap = calloc(7, sizeof(uint8_t));
```

Since `calloc` is used, all bits start cleared.

---

## Notes and Limitations

This is a very simple parser. It only detects whether a letter flag exists.

It does not currently support:

```text
--long-options
arguments with values, such as -o file.txt
quoted strings
escaped spaces
multiple parses with automatic reset
non-letter flags
```

Also, the bitmap is global and persistent, so once an argument is set, it stays set until the program exits or the bitmap is manually cleared.

For example:

```c
get_args("ls -a");
get_args("ls -b");
```

After both calls, both `a` and `b` will be marked as active.

---

## Example

```c
char input[] = "test -aBz";

get_args(input);

printf("%d\n", is_arg('a')); // 1
printf("%d\n", is_arg('B')); // 1
printf("%d\n", is_arg('z')); // 1
printf("%d\n", is_arg('x')); // 0
```

---

## Purpose

This parser is useful for small shell-like programs, operating system projects, or custom libc environments where a lightweight argument parser is needed without relying on larger parsing libraries.
