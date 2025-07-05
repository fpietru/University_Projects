# nsqrt: Square Root for big integers in Assembly

## Function Description
Given non-negative `2n`-bit integer `X` function computes non-negative `n`-bit integer `Q` such that `Q^2 <= X < (Q+1)^2`.

`nsqrt` is an assembly function callable from `C` with the following signature:

```c
void nsqrt(uint64_t *Q, uint64_t *X, unsigned n)
```

Pamameters:
- `Q` - pointer to memory where the result will be stored;
- `X` - pointer to binary representation of `X`. It can be modified during computation and used as a scratch memory;
- `n` - bit-length of result `Q`. Guaranteed to be divisible by 64 and is in range `[64, 256000]`.

The integers `Q` and `X` are represented in little-endian order, using binary representation, with 64 bits per `uint64_t` word.

## Compilation
```bash
nasm -f elf64 -w+all -w+error -o nsqrt.o nsqrt.asm
```
