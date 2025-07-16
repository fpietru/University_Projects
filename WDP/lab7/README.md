# Persistent Segment Tree for Range Querying

This project provides an efficient implementation of a *persistent segment tree* data structure that supports querying the **last index** `j ≤ i` such that `seq[j] ∈ [lo, hi]`, as well as dynamic updates via `pushBack`.

## Features

- **Persistent Segment Tree**: Maintains versions of the tree for each prefix of the input sequence.
- **Efficient Queries**: Supports fast range queries over previous values with `prevInRange(i, lo, hi)`.
- **Dynamic Extension**: New values can be added to the sequence at any time using `pushBack(value)`.
- **Memory Cleanup**: Cleanly releases memory with `done()`.

## API

```cpp
void init(const std::vector<int> &seq);
int prevInRange(int i, int lo, int hi);
void pushBack(int value);
void done();
```

 - `init(seq)` - Initializes the data structure using the given sequence.
 - `prevInRange(i, lo, hi)` - Returns the largest j ≤ i such that seq[j] ∈ [lo, hi], or -1 if no such j exists.
 - `pushBack(value)` - Adds a new value to the sequence.
 - `done()` - Frees memory used by the data structure.

 ## Usage Example
 ```cpp
init({3, 7, 2, 5});
int res = prevInRange(3, 4, 6); // returns 3 (seq[3] == 5)
pushBack(4);
res = prevInRange(4, 1, 3); // returns 2 (seq[2] == 2)
done();
 ```

 ## Implementation Notes
 - Each version of the segment tree corresponds to a prefix of the input sequence.
 - All values are translated by `-INT_MIN` to handle negative integers safely within the tree.
 - The implementation relies on C++ `shared_ptr` for safe and efficient memory management.