/*
  Author: Franciszek Pietrusiak
*/
#include "ma.h"
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 64
#define BLOCK(x) (x / WORD_SIZE)
#define MOD(x) (x % WORD_SIZE)

struct moore {
  size_t n, m, s;
  size_t inputSize, stateSize, outptSize;
  moore_t **connectedTo;
  size_t *portId;
  uint64_t *input, *state, *outpt;
  transition_function_t t;
  output_function_t y;

} typedef moore_t;


moore_t *ma_create_full(size_t n, size_t m, size_t s, transition_function_t t,
  output_function_t y, uint64_t const *q) {
  if (m == 0 || s == 0 || !t || !y || !q) {
    errno = EINVAL;
    return NULL;
  }
  moore_t *a = malloc(sizeof(moore_t));
  if (!a) {
    errno = ENOMEM;
    return NULL;
  }
  a->n = n;
  a->m = m;
  a->s = s;
  a->inputSize = BLOCK(n) + 1;
  a->outptSize = BLOCK(m) + 1;
  a->stateSize = BLOCK(s) + 1;
  a->t = t;
  a->y = y;
  a->input = calloc(a->inputSize, sizeof(uint64_t));
  a->outpt = calloc(a->outptSize, sizeof(uint64_t));
  a->state = calloc(a->stateSize, sizeof(uint64_t));
  a->connectedTo = malloc(n * sizeof(moore_t*));
  a->portId = malloc(n * sizeof(size_t)); 
  if (!a->input || !a->state || !a->outpt || !a->connectedTo || !a->portId) {
    errno = ENOMEM;
    return NULL;
  }
  for (size_t i=0; i<a->stateSize; i++) {
    a->state[i] = q[i];
  }
  y(a->outpt, a->state, a->m, a->s); // nie jestem pewien czy nie lepiej użyć ma_step
  for (size_t i=0; i<a->n; i++) {
    a->connectedTo[i] = NULL;
  }
  return a;
}

static void identity(uint64_t *output, uint64_t const *state, size_t m, size_t s) {
  for (size_t i=0; i<m; i++) {
    output[i] = state[i];
  }
}

moore_t * ma_create_simple(size_t n, size_t s, transition_function_t t) {
  uint64_t *q = calloc(BLOCK(s), sizeof(uint64_t));
  moore_t *a = ma_create_full(n, s, s, t, identity, q);
}

void ma_delete(moore_t *a) {
  if (!a) return;
  free(a->input);
  free(a->state);
  free(a->outpt);
  free(a->portId);
  for (size_t i=0; i<a->n; i++) {
    free(a->connectedTo[i]);
  }
  free(a->connectedTo);
  free(a);
  a = NULL;
}

static int getBit(uint64_t x, size_t pos) {
  assert(pos < 64);
  return ((x & (1ULL << pos)) > 0);
}

static void setOne(uint64_t *tab, size_t pos) {
  tab[BLOCK(pos)] |= (uint64_t)(1ULL << MOD(pos));
}

static void setZero(uint64_t *tab, size_t pos) {
  if (getBit(tab[BLOCK(pos)], MOD(pos))) {
    tab[BLOCK(pos)] ^= (1ULL << MOD(pos));
  }
}

int ma_set_input(moore_t *a, uint64_t const *input) {
  if (!a || !a->n || !input) {
    errno = EINVAL;
    return -1;
  }
  for (size_t i=0; i<a->n; i++) {
    if (!a->connectedTo[i]) {
      (getBit(*input, i) ? setOne(a->input, i) : setZero(a->input, i));
    }
  }
  return 0;
}

int ma_set_state(moore_t *a, uint64_t const *state) {
  if (!a || !state) {
    errno = EINVAL;
    return -1;
  }
  for (size_t i=0; i<a->stateSize; i++) {
    a->state[i] = state[i];
  }
  return 0;
}

uint64_t const * ma_get_output(moore_t const *a) {
  if (!a) {
    errno = EINVAL;
    return NULL;
  }
  return a->outpt;
}