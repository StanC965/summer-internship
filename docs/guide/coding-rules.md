# Coding discipline

The following rules are taken from the Guide sheet of the internship workbook.

## Core rules

1. Add relevant comments for important lines and decisions.
2. Commit each exercise separately to GitHub.
3. Add a file header comment with the exercise ID using the internship numbering scheme.
4. Push only compilable and runnable code, including all project files.
5. Do not use magic numbers; use named constants or macros.
6. Use `#include "..."` for your own modules, not angle brackets.
7. Name functions and variables with a module prefix.

## Naming example

- Module prefix: `tc0`
- Functions: `tc0_init()`, `tc0_set_value()`
- Variables: `tc0_counter`, `tc0_temp`
