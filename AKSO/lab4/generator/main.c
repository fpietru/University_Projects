#include "input-output.h"
#include "generator.h"

int main() {
  int count = read_int();

  multiplier = 3;
  summand = 1;
  set_state(2);

  for (int i = 0; i < count; ++i)
    print_uint(generate_random_uint());
}
