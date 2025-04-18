//Randomowe testy, co mi wpadlo do glowy.
//Nie wklejamy do ma_example, tylko kompilujemy z biblioteką i odpalamy.
//Pozdrawiam.

#include "ma.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include <errno.h>

#define PASS 0
#define FAIL -1
#define FAIL_PTR NULL

void t_one(uint64_t *next_state, uint64_t const *input,
           uint64_t const *old_state, size_t n, size_t s) {
    next_state[0] = old_state[0] + input[0];
    next_state[1] = old_state[1] + input[1];
}

void t_two(uint64_t *next_state, uint64_t const *input,
    uint64_t const *old_state, size_t n, size_t s) {
        next_state[0] = old_state[0] + input[0];
    }

void y_one(uint64_t *output, uint64_t const *state, size_t m, size_t s) {
    output[0] = state[0] + 1;
    output[1] = state[1] + 1;
}

int main() {
    //więcej niz 64 bity
    uint64_t *q1 = malloc(sizeof(uint64_t) * 2);
    q1[0] = 10;
    q1[1] = 20;
    moore_t *machine1 = ma_create_full(128, 128, 128, t_one, y_one,q1);
    const uint64_t *out1 = ma_get_output(machine1);
    assert(out1[0] == 11);
    assert(out1[1] == 21);

    uint64_t *q2 = malloc(sizeof(uint64_t) * 2);
    q2[0] = 5;
    q2[1] = 15;
    ma_set_state(machine1, q2);
    assert(out1[0] == 6);
    assert(out1[1] == 16);

    ma_set_input(machine1, q1);
    ma_step(&machine1, 1);
    assert(out1[0] == 16);
    assert(out1[1] == 36);

    uint64_t *zero = malloc(sizeof(uint64_t) * 2);
    zero[0] = 0;
    zero[1] = 1;
    ma_set_state(machine1, q1);
    ma_set_input(machine1, zero);

    moore_t *machine2 = ma_create_full(128, 128, 128, t_one, y_one,q2);
    ma_set_input(machine2, zero);
    const uint64_t *out2 = ma_get_output(machine2);

    ma_connect(machine2, 0, machine1, 0, 128);

    ma_step(&machine2, 1);
    assert(out2[0] == 17);
    assert(out2[1] == 37);

    free(q1);
    free(q2);
    free(zero);
    ma_delete(machine1);
    ma_delete(machine2);


    moore_t * machine3 = ma_create_simple(100, 100, t_one);

    uint64_t * q3 = malloc(sizeof(uint64_t) * 2);
    q3[0] = 6;
    q3[1] = 4;

    ma_set_input(machine3, q3);
    ma_step(&machine3, 1);
    const uint64_t * out3 = ma_get_output(machine3);
    assert(out3[0] == 6);
    assert(out3[1] == 4);

    ma_delete(machine3);
    free(q3);


    moore_t * machine4 = ma_create_simple(64, 64, t_two);
    moore_t * machine5 = ma_create_simple(64, 64, t_two);

    uint64_t jeden = 1;

    ma_set_state(machine4, &jeden);
    //Zakresy
    assert(ma_connect(machine5, 0, machine4, 0, 65) == FAIL);
    assert(errno == EINVAL);
    errno = 0;
    assert(ma_connect(machine5, 1, machine4, 0, 64) == FAIL);
    assert(errno == EINVAL);
    assert(ma_connect(machine5, 0, machine4, 1, 64) == FAIL);
    assert(errno == EINVAL);
    errno = 0;
    assert(ma_connect(machine5, 0, machine4, 0, 64) == PASS);
    assert(errno == 0);
    assert(ma_connect(machine5, 0, machine4, 1, 64) == FAIL);
    assert(errno == EINVAL);
    errno = 0;

    const uint64_t * out5 = ma_get_output(machine5);

    uint64_t in = (uint64_t)1 << 32;
    ma_set_input(machine5, &in);

    //Odłączanie przez usunięcie
    ma_step(&machine5, 1);
    assert(out5[0] == 1);
    ma_delete(machine4);
    ma_set_input(machine5, &in);
    ma_step(&machine5, 1);
    assert(out5[0] == in + 1);

    //Wpięcie sam w siebie
    assert(ma_connect(machine5, 0, machine5, 1, 40) == PASS);
    ma_set_state(machine5, &in);
    ma_step(&machine5, 1);
    assert(out5[0] == (uint64_t)3 << 31);

    //Synchroniczne ma_step
    moore_t * machine6 = ma_create_simple(64, 64, t_two);
    assert(ma_connect(machine6, 0, machine5, 0, 64) == PASS);
    moore_t * at[] = {machine5, machine6};
    const uint64_t * out6 = ma_get_output(machine6);
    ma_step(at, 2);
    assert(out5[0] == ((uint64_t)1 << 30) + ((uint64_t)1 << 33));
    assert(out6[0] == (uint64_t)3 << 31);
    ma_delete(machine5);

    return 0;
}