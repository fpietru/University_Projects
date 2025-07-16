# String Expression Evaluator

This C++ program provides a simple framework for representing and evaluating symbolic string expressions composed of constants, variables, and various unary and binary string operators. It uses object-oriented principles and smart pointers (`std::shared_ptr`) for safe memory management.

## Features

- **Constants (`Stala`)**: Represent fixed string values.
- **Variables (`Zmienna`)**: Named values (`a`–`z`) that can be initialized at runtime.
- **Unary Operators**:
  - `Upper`: Converts text to uppercase (`^expr`)
  - `Lower`: Converts text to lowercase (`_expr`)
  - `Licz`: Returns the length of the evaluated string (`#expr`)
- **Binary Operators**:
  - `Scal`: Concatenates two expressions (`(a&b)`)
  - `Mask`: Filters characters from the first string based on `'*'` positions in the second (`(a*b)`)
  - `Przeplot`: Interleaves characters from two expressions (`(a@b)`)

## Compilation & Testing

The code has been tested with [Valgrind](https://valgrind.org/) to ensure no memory leaks.

### Compile

```bash
g++ -std=c++17 -Wall -Wextra -O2 wyrazenia_tekstowe.cpp -o program
```

### Run

```bash
./program
```