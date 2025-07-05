# Moore Automata

## Task Description

The task involves implementing a dynamically loaded library in C that simulates Moore automata. A Moore automaton is a type of deterministic finite automaton used in synchronous digital circuits. A Moore automaton is represented as an ordered sextuple `⟨X, Y, Q, t, y, q⟩`, where:

- `X` is the set of input signal values,
- `Y` is the set of output signal values,
- `Q` is the set of internal state values,
- `t: X × Q → Q` is the transition function,
- `y: Q → Y` is the output function,
- `q ∈ Q` is the initial state.

We consider only binary automata with `n` single-bit input signals, `m` single-bit output signals, and an `s`-bit state. Formally, `X = {0,1}^n`, `Y = {0,1}^m`, `Q = {0,1}^s`.

At each step of the automaton's operation, the transition function `t` computes the new state based on the input signals and the current state. The output function `y` computes the output signals based on the current state.

## Bit Representation

Bit sequences (inputs, outputs, state) are stored in arrays of `uint64_t`, where each element contains 64 bits starting from the least significant bit. If the sequence length is not a multiple of 64, the most significant bits of the last element are unused.

## Interface

The interface is defined in the header file `ma.h`. Further usage examples are provided in `ma_example.c`. defined in the provided `ma.h` file. Additional details about the library's operation can be inferred from the provided example usage file `ma_example.c`, which is an integral part of the specification.

Bit sequences and signal values are stored in an array of `uint64_t` elements. Each array element stores 64 consecutive bits, starting from the least significant position. If the sequence length is not a multiple of 64, the higher bits of the last array element remain unused.

The structural type `moore_t` represents an automaton. This type must be defined (implemented) as part of this task.

```c
typedef struct moore moore_t;
```

The automaton's state and its input/output signals are bit sequences.

The `transition_function_t` type represents the automaton's transition function. This function computes the new state based on the input signals and the current state.
```c
typedef void (*transition_function_t)(uint64_t *next_state, uint64_t const *input, uint64_t const *state, size_t n, size_t s);
```
Function parameters:
- `next_state` - pointer to the bit sequence where the new state is stored;
- `input` - pointer to the bit sequence containing input signal values;
- `state` - pointer to the bit sequence containing the current automaton state;
- `n` - number of input signals;
- `s` - number of bits in the internal state.

The `output_function_t` type represents the automaton's output function. This function computes the output signals based on the current state.
```c
typedef void (*output_function_t)(uint64_t *output, uint64_t const *state, size_t m, size_t s);
```
Function parameters:
- `output` - pointer to the bit sequence where the function result is stored;
- `state` - pointer to the bit sequence containing the automaton state;
- `m` - number of output signals;
- `s` - number of bits in the internal state.

## Function Descriptions
### ma_create_full
Creates a new automaton.
```c
moore_t *ma_create_full(size_t n, size_t m, size_t s, transition_function_t t, output_function_t y, uint64_t const *q);
```

Parameters:
- `n` - number of input signals;
- `m` - number of output signals;
- `s` - number of bits in the internal state;
- `t` - transition function;
- `y` - output function;
- `q` - pointer to the bit sequence representing the initial state.

Return value:
- Pointer to the automaton structure;
- `NULL` - if `m` or `s` is zero, or any of the pointers `t`, `y`, or `q` is `NULL`, or if memory allocation fails. Sets `errno` to `EINVAL` or `ENOMEM`.

### ma_create_simple
Creates a new automaton where the number of outputs equals the number of state bits, the output function is the identity function, and the initial state is zero. Initializes unused state bits to zero.
```c
moore_t *ma_create_simple(size_t n, size_t s, transition_function_t t);
```
Parameters:
- `n` - number of input signals;
- `s` - number of bits in the internal state and number of output signals;
- `t` - transition function.

Return value:
- Pointer to the automaton structure;
- `NULL` - if `s` is zero, `t` is `NULL`, or memory allocation fails. Sets `errno` to `EINVAL` or `ENOMEM`.

### ma_delete
Deletes the specified automaton and frees all associated memory. Does nothing if called with a `NULL` pointer. The pointer becomes invalid after this call.
```c
void ma_delete(moore_t *a);
```
Parameter:
- `a` - pointer to the automaton structure.

### ma_connect
Connects the next num input signals of automaton `a_in` to the output signals of automaton `a_out`, starting from input in and output out, respectively. Disconnects inputs from other outputs if previously connected.
```c
int ma_connect(moore_t *a_in, size_t in, moore_t *a_out, size_t out, size_t num);
```
Parameters:
- `a_in` - pointer to the automaton structure;
- `in` - input number of a_in;
- `a_out` - pointer to the automaton structure;
- `out` - output number of a_out;
- `num` - number of signals to connect.

Return value:
- `0` - if successful;
- `-1` - if any pointer is `NULL`, `num` is zero, or the specified input/output range is invalid. Sets `errno` to `EINVAL` or `ENOMEM`.

### ma_disconnect
Disconnects the next `num` input signals of automaton `a_in` from output signals, starting from input `in`. Unconnected inputs remain unconnected.
```c
int ma_disconnect(moore_t *a_in, size_t in, size_t num);
```
Parameters:
- `a_in` - pointer to the automaton structure;
- `in` - input number of `a_in`;
- `num` - number of signals to disconnect.

Return value:
- `0` - if successful;
- `-1` - if `a_in` is `NULL`, `num` is zero, or the input range is invalid. Sets `errno` to `EINVAL`.

### ma_set_input
Sets the values of unconnected input signals, ignoring bits in input corresponding to connected inputs.
```c
int ma_set_input(moore_t *a, uint64_t const *input);
```
Parameters:
- `a` - pointer to the automaton structure;
- `input` - pointer to a sequence of `n` bits, where `n` is the number of inputs.

Return value:
- `0` - if successful;
- `-1` - if the automaton has no inputs or any pointer is `NULL`. Sets `errno` to `EINVAL`.

### ma_set_state
Sets the automaton's state.
```c
int ma_set_state(moore_t *a, uint64_t const *state);
```
Parameters:
- `a` - pointer to the automaton structure;
- `state` - pointer to the bit sequence representing the new state.

Return value:
- `0` - if successful;
- `-1` - if any pointer is `NULL`. Sets `errno` to `EINVAL`.

### ma_get_output
Returns a pointer to the bit sequence containing the automaton's output signal values. The pointer remains valid until `ma_delete` is called on the automaton.
```c
uint64_t const *ma_get_output(moore_t const *a);
```
Parameter:
- `a` - pointer to the automaton structure.

Return value:
- Pointer to the output bit sequence;
- `NULL` - if `a` is `NULL`. Sets `errno` to `EINVAL`.

### ma_step
Performs one computation step for the given automata. All automata operate in parallel and synchronously, meaning the new state and output values depend only on the values before the call.
```c
int ma_step(moore_t *at[], size_t num);
```
Parameter:
- `at` - array of pointers to automaton structures;
- `num` - size of the array at, number of automata.

Return value:
- `0` - if successful;
- `-1` - if `at` is `NULL`, any pointer in `at` is `NULL`, `num` is zero, or memory allocation fails. Sets `errno` to `EINVAL` or `ENOMEM`.

## Functional Requirements
The input state of an automaton is set using `ma_set_input` or by connecting it to another automaton's output. Until set, the input state is undefined. Disconnecting an input sets its state to undefined.

Ensure proper disconnection when deleting or connecting automata to avoid dangling connections.

The library must provide a weak guarantee of memory allocation failure resilience (no memory leaks, data structures remain consistent).

## Compilation

Use gcc with the following flags for library files:
- Compilation: `-Wall -Wextra -Wno-implicit-fallthrough -std=gnu17 -fPIC -O2`
- Linking: `-shared -Wl,--wrap=malloc -Wl,--wrap=calloc -Wl,--wrap=realloc -Wl,--wrap=reallocarray -Wl,--wrap=free -Wl,--wrap=strdup -Wl,--wrap=strndup`

The `-Wl,--wrap=` flags intercept calls to `malloc`, `calloc`, etc., redirecting them to `__wrap_malloc`, `__wrap_calloc`, etc., implemented in `memory_tests.c`.