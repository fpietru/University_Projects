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

// Representation of one-way connection between automatons
typedef struct connection {
  moore_t *to;
  size_t portTo;
  size_t portFrom;
} connection_t;

// Node in linked list containing connection
typedef struct node {
  connection_t connection;
  struct node *next;
} node_t;

typedef struct moore {
  size_t n, m, s;
  size_t inputSize, stateSize, outptSize;
  connection_t *inputConnections;
  node_t *outputConnections;
  uint64_t *input, *state, *outpt;
  transition_function_t t;
  output_function_t y;
} moore_t;

// Change connection
static void change_connection(connection_t *c, moore_t *to, size_t portTo, size_t portFrom) {
  assert(c != NULL);
  c->to = to;
  c->portTo = portTo;
  c->portFrom = portFrom;
}

// Create new node
node_t *new_node() {
  node_t *u = malloc(sizeof(node_t));
  if (!u) {
    errno = ENOMEM;
    return NULL;
  }
  u->connection.to = NULL;
  u->connection.portTo = 0;
  u->connection.portFrom = 0;
  u->next = NULL;
  return u;
}

// Add a new node to the front of the linked-list
static void push(node_t **head, moore_t *to, size_t portTo, size_t portFrom) {
  node_t *nNode = new_node();
  if (nNode == NULL) return;
  nNode->connection.to = to;
  nNode->connection.portTo = portTo;
  nNode->connection.portFrom = portFrom;
  nNode->next = *head;
  *head = nNode;
}

// Remove a node from the list by port value from specific automaton
static void remove_by_port(node_t **head, const moore_t *who, const size_t port) {
  if (*head == NULL) return;
  node_t *curr = *head, *prev = NULL;
  while (curr != NULL) {
    assert(curr->connection.to);
    if (curr->connection.to == who && curr->connection.portTo == port) {
      node_t *next = curr->next;
      free(curr);
      curr = NULL;
      if (prev == NULL) {
        *head = next;
      } else {
        prev->next = next;
        return;
      }
    }
    prev = curr;
    if (curr != NULL)
      curr = curr->next;
  }
}

// Tell all automatons that take input from this automaton to remove their connection to this automaton
static void disconnect_from_other(node_t *head) {
  node_t *curr = head;
  while (curr != NULL) {
    node_t *next = curr->next;
    moore_t *other = curr->connection.to;
    size_t portTo = curr->connection.portTo;
    if (other != NULL) {
      other->inputConnections[portTo].to = NULL;
    }
    curr = next;
  }
}

// Debug function to show all nodes in a linked list
static void show_list(node_t *head) {
  node_t *curr = head;
  while (curr != NULL) {
    node_t *next = curr->next;
    printf("to: ");
    if (curr->connection.to != NULL) {
      printf("%p\n", curr->connection.to);
    } else printf("NULL");
    printf("port from = %lu, port to = %lu\n", curr->connection.portFrom, curr->connection.portTo);
    curr = next;
  }
}

// Free memory for entire linked list
static void free_list(node_t **head) {
  node_t *curr = *head;
  while (curr != NULL) {
    node_t *next = curr->next;
    free(curr);
    curr = NULL;
    curr = next;
  }
  *head = NULL;
}


moore_t *ma_create_full(size_t n, size_t m, size_t s, transition_function_t t,
                        output_function_t y, uint64_t const *q) {
  if (m == 0 || s == 0 || !t || !y || !q) {
    errno = EINVAL;
    return NULL;
  }
  if (n > SIZE_MAX / sizeof(connection_t) ||
    BLOCK(s) + 1 > SIZE_MAX / sizeof(uint64_t) ||
    BLOCK(n) + 1 > SIZE_MAX / sizeof(uint64_t) ||
    BLOCK(m) + 1 > SIZE_MAX / sizeof(uint64_t)) {
    errno = ENOMEM;
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
  a->stateSize = BLOCK(s) + 1;
  a->state = calloc(a->stateSize, sizeof(uint64_t));
  a->inputSize = BLOCK(n) + 1;
  a->input = calloc(a->inputSize, sizeof(uint64_t));
  a->outptSize = BLOCK(m) + 1;
  a->outpt = calloc(a->outptSize, sizeof(uint64_t));
  a->t = t;
  a->y = y;
  a->inputConnections = malloc(n * sizeof(connection_t));
  a->outputConnections = NULL;

  if (!a->input || !a->state || !a->outpt || !a->inputConnections) {
    free(a->input);
    a->input = NULL;
    free(a->state);
    a->state = NULL;
    free(a->outpt);
    a->outpt = NULL;
    free(a->inputConnections);
    a->inputConnections = NULL;
    free(a);
    a = NULL;
    errno = ENOMEM;
    return NULL;
  }
  memcpy(a->state, q, a->stateSize * sizeof(uint64_t));
  y(a->outpt, a->state, a->m, a->s);

  // initialize inputConnections
  for (size_t i = 0; i < a->n; i++) {
    a->inputConnections[i].to = NULL;
    a->inputConnections[i].portTo = 0;
    a->inputConnections[i].portFrom = i;
  }

  return a;
}

// Identity function for simple automaton
static void identity(uint64_t *output, uint64_t const *state, size_t m, size_t s) {
  assert(m == s);
  size_t outptSize = BLOCK(m) + 1;
  memcpy(output, state, outptSize * sizeof(uint64_t));
}

moore_t *ma_create_simple(size_t n, size_t s, transition_function_t t) {
  if (!s || !t) {
    errno = EINVAL;
    return NULL;
  }
  uint64_t *q = calloc(BLOCK(s) + 1, sizeof(uint64_t));
  if (!q) {
    errno = ENOMEM;
    return NULL;
  }
  moore_t *a = ma_create_full(n, s, s, t, identity, q);
  if (!a) {
    free(q);
    q = NULL;
    errno = ENOMEM;
    return NULL;
  }
  free(q);
  q = NULL;
  return a;
}

void ma_delete(moore_t *a) {
  if (a == NULL) return;

  // Free Inputs
  ma_disconnect(a, 0, a->n);
  free(a->inputConnections);
  a->inputConnections = NULL;

  assert(a->input);
  assert(a->state);
  assert(a->outpt);

  free(a->input);
  a->input = NULL;
  free(a->state);
  a->state = NULL;
  free(a->outpt);
  a->outpt = NULL;

  // Free Outputs
  disconnect_from_other(a->outputConnections);
  free_list(&a->outputConnections);

  free(a);
  a = NULL;
}

int ma_connect(moore_t *a_in, size_t in, moore_t *a_out, size_t out, size_t num) {
  if (!a_in || !a_out || num == 0 || num > a_in->n || num > a_out->m ||
    in >= a_in->n || out >= a_out->m ||  (in + num > a_in->n) || (out + num > a_out->m)) {
    errno = EINVAL;
    return -1;
  }
  int res = 0;
  for (size_t i = in, j = out; i <= in + num - 1; i++, j++) {
    if (a_in->inputConnections[i].to != NULL) {
       if (ma_disconnect(a_in, i, 1) != 0) {
         res = -1;
       }
    }
    change_connection(&a_in->inputConnections[i], a_out, j, i);
    push(&a_out->outputConnections, a_in, i, j);
  }
  return res;
}

int ma_disconnect(moore_t *a_in, size_t in, size_t num) {
  if (!a_in || num == 0 || in >= a_in->n || num > a_in->n || (in + num > a_in->n)) {
    errno = EINVAL;
    return -1;
  }

  for (size_t i = in; i <= in + num - 1; i++) {
    moore_t *a_out = a_in->inputConnections[i].to;
    if (a_out != NULL) {
      a_in->inputConnections[i].to = NULL;
      remove_by_port(&a_out->outputConnections, a_in, i);
    }
  }
  return 0;
}

// Extract bit value at position pos from array x of 64-bit long words
static int get_bit(const uint64_t *x, size_t size, size_t pos) {
  assert(BLOCK(pos) < size);
  return ((x[BLOCK(pos)] & (1ULL << MOD(pos))) > 0);
}

// Set one at position pos in the array tab of 64-bit long words
static void set_one(uint64_t *tab, size_t size, size_t pos) {
  assert(BLOCK(pos) < size);
  tab[BLOCK(pos)] |= (uint64_t) (1ULL << MOD(pos));
}

// Set zero at position pos in the array tab of 64-bit long words
static void set_zero(uint64_t *tab, size_t size, size_t pos) {
  assert(BLOCK(pos) < size);
  if (get_bit(tab, size, pos)) {
    tab[BLOCK(pos)] ^= (1ULL << MOD(pos));
  }
}

int ma_set_input(moore_t *a, uint64_t const *input) {
  if (!a || !a->n || !input) {
    errno = EINVAL;
    return -1;
  }
  for (size_t i = 0; i < a->n; i++) {
    if (a->inputConnections[i].to == NULL) {
      int bitVal = get_bit(input, a->n, i);
      if (bitVal) {
        set_one(a->input, a->n, i);
      } else {
        set_zero(a->input, a->n, i);
      }
    }
  }
  return 0;
}

int ma_set_state(moore_t *a, uint64_t const *state) {
  if (!a || !state) {
    errno = EINVAL;
    return -1;
  }
  for (size_t i = 0; i < a->stateSize; i++) {
    a->state[i] = state[i];
  }
  a->y(a->outpt, a->state, a->outptSize, a->stateSize);
  return 0;
}

uint64_t const *ma_get_output(moore_t const *a) {
  if (!a) {
    errno = EINVAL;
    return NULL;
  }
  return a->outpt;
}

static void update_inputs(moore_t *a) {
  for (size_t i = 0; i < a->n; i++) {
    moore_t *b = a->inputConnections[i].to;
    if (b != NULL) {
      size_t port = a->inputConnections[i].portTo;
      int sigval = get_bit(b->outpt, b->m, port);
      if (sigval) {
        set_one(a->input, a->n, i);
      } else {
        set_zero(a->input, a->n, i);
      }
    }
  }
}

int ma_step(moore_t *at[], size_t num) {
  if (!at || num == 0) {
    errno = EINVAL;
    return -1;
  }
  for (size_t i = 0; i < num; i++) {
    if (!at[i]) {
      errno = EINVAL;
      return -1;
    }
  }
  for (size_t i = 0; i < num; i++) {
    update_inputs(at[i]);
  }
  for (size_t i = 0; i < num; i++) {
    uint64_t *next_state = malloc(at[i]->stateSize * sizeof(uint64_t));
    if (!next_state) {
      errno = ENOMEM;
      return -1;
    }

    at[i]->t(next_state, at[i]->input, at[i]->state, at[i]->n, at[i]->s);
    memcpy(at[i]->state, next_state, at[i]->stateSize * sizeof(uint64_t));

    free(next_state);
    next_state = NULL;
    at[i]->y(at[i]->outpt, at[i]->state, at[i]->m, at[i]->s);
  }

  return 0;
}

// Debug function to print useful info about automaton a
void ma_show(moore_t *a) {
  printf(" ====== Info o %p =======\n", a);
  printf("n = %lu, m = %lu, s = %lu\n", a->n, a->m, a->s);

  assert(a->inputConnections);
  for (size_t i = 0; i < a->n; i++) {
    printf("%lu ", i);
    if (a->inputConnections[i].to != NULL) {
      printf("jest %p\n", a->inputConnections[i].to);
    } else printf("nie jest\n");
  }

  assert(a->input);
  printf("input:\n");
  for (size_t i = 0; i < a->n; i++) {
    printf("%d", get_bit(a->input, a->n, i));
  }

  assert(a->state);
  printf("\nstate:\n");
  for (size_t i = 0; i < a->s; i++) {
    printf("%d", get_bit(a->state, a->s, i));
  }

  assert(a->outpt);
  printf("\noutput:\n");
  for (size_t i = 0; i < a->m; i++) {
    printf("%d", get_bit(a->outpt, a->m, i));
  }
  printf("\n");

  printf("output list:\n");
  show_list(a->outputConnections);
  printf("==================\n");
}
