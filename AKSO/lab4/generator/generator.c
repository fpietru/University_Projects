#include "generator.h"

static unsigned state = 1;

unsigned multiplier = 21937U;
unsigned summand;

static void make_step(void) {
  state = state * multiplier + summand;
}

void set_state(unsigned new_state) {
  state = new_state;
}

unsigned generate_random_uint(void) {
  make_step();

  return state;
}
