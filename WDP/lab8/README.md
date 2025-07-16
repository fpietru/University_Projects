# Multi-Jug Water Pouring Solver

This project implements a **generalized water jug problem solver** for *n* jugs of arbitrary capacities. The algorithm finds the **minimum number of steps** required to reach a desired configuration of water levels using breadth-first search (BFS).

## Problem Overview

Given:
- `x[i]`: Capacity of the *i*-th jug
- `y[i]`: Desired final water level in the *i*-th jug

Operations allowed per step:
1. **Fill** a jug to its maximum capacity
2. **Empty** a jug completely
3. **Pour** water from one jug into another (until source is empty or destination is full)

The goal is to reach the exact configuration `y` from the initial state where all jugs are empty.

## Constraints & Observations

- A solution exists **only if** all target levels `y[i]` are divisible by the greatest common divisor of the capacities `x`.
- If a solution exists, the program outputs the **minimum number of steps** to reach it.
- Otherwise, it outputs `-1`.

## Implementation Details

- The algorithm performs a **BFS** on all possible water states.
- States are represented as `vector<int>` and stored in a `unordered_map` with a **custom hash function**.
- The hash function uses a combination of bitwise operations to reduce collision risk for vector keys.

## Sample Input
Input:
```bash
3
8 4
5 2
3 1
```

Output:
```bash
7
```