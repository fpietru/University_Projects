#ifndef MA_H
#define MA_H

#include <stddef.h>
#include <stdint.h>

typedef struct moore moore_t;
typedef void (*transition_function_t)(uint64_t *next_state, uint64_t const *input,
                                      uint64_t const *state, size_t n, size_t s);
typedef void (*output_function_t)(uint64_t *output, uint64_t const *state,
                                  size_t m, size_t s);

moore_t * ma_create_full(size_t n, size_t m, size_t s, transition_function_t t,
                         output_function_t y, uint64_t const *q);
moore_t * ma_create_simple(size_t n, size_t m, transition_function_t t);
void ma_delete(moore_t *a);
int ma_connect(moore_t *a_in, size_t in, moore_t *a_out, size_t out, size_t num);
int ma_disconnect(moore_t *a_in, size_t in, size_t num);
int ma_set_input(moore_t *a, uint64_t const *input);
int ma_set_state(moore_t *a, uint64_t const *state);
uint64_t const * ma_get_output(moore_t const *a);
int ma_step(moore_t *at[], size_t num);

#endif
