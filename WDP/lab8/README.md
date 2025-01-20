# n Jug Water Pouring Problem
## Problem Description

You are given `n` jugs, numbered from 1 to `n`, with capacities `x1, x2, ..., xn`. Initially, all jugs are empty. You can perform the following operations:

1. **Fill a jug completely** with water from the tap.
2. **Empty a jug** completely into the sink.
3. **Pour water from one jug to another**:
   - If all the water fits, pour the entire amount.
   - If not, pour only enough to fill the second jug completely.

Your goal is to achieve a state where each jug contains a specific amount of water `y1, y2, ..., yn`.

Write a program that, given the values of `x1, x2, ..., xn` and `y1, y2, ..., yn`, determines the minimum number of operations needed to achieve the described state. If achieving the state is impossible, the program should return `-1`.

### Input Format
The input is read from standard input in the following format:

```
n
x1 y1
x2 y2
...
xn yn
```

Where:
- `n` is the number of jugs.
- For each jug `i`, `xi` is its capacity, and `yi` is the target amount of water.

### Assumptions
- `0 \leq n`.
- `0 \leq yi \leq xi` for `i = 1, 2, ..., n`.
- All input values are integers.
- The values of `n`, `x1 + x2 + ... + xn`, and `y1 + y2 + ... + yn` fit within the `int` type.

### Output
The program should output the minimal number of operations needed, or `-1` if the target state is not achievable.