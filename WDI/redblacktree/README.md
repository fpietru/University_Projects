# Red-Black Tree CLI Playground

This is a simple command-line C program for experimenting with a [Red-Black Tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree) data structure.
It allows you to insert, delete, and search for keys in a Red-Black Tree, displaying the tree structure after each operation.
Implementation of Red-Black Tree is based on [Introduction to Algorithms (4th ed.)](https://mitpress.mit.edu/9780262046305/introduction-to-algorithms/)

## Features

- Insert a node by key
- Delete a node by key
- Search for a node by key
- Tree is printed after every operation in the format: `[key color]`

## Files

- `main.c` – CLI interface for interacting with the tree.
- `rb_tree.c` – Red-Black Tree implementation
- `rb_tree.h` – Header file with structure definitions and function declarations.

## Compilation

Use `gcc` to compile:

```bash
gcc -o main rb_tree.c main.c
```

## Usage

```bash
./main
```

Then enter operations as two integers:

```bash
[operation] [key]
```
 - 1 [key] - Insert node with key
 - 2 [key] - Delete node with key
 - 3 [key] - Search for node with key


Example input:
```bash
1 10
1 5
3 10
2 5
```

## Output Format
After each operation, the current structure of the tree is printed with indentation indicating depth:
```
-> [5 0]
    -> [10 1]
```
Here, 0 = BLACK, 1 = RED.
