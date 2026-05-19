#include <stdio.h>
#include <stdlib.h>
#include "htbl.h"


unsigned long long int hash_fn(board bd, unsigned int depth) {
  return
    101 * bd.white_envoy +
    107 * bd.white_queen +
    113 * bd.white_bishop +
    127 * bd.white_knight +
    137 * bd.white_sentry +
    149 * bd.black_envoy +
    157 * bd.black_queen +
    163 * bd.black_bishop +
    167 * bd.black_knight +
    173 * bd.black_sentry +
    179 * bd.whose_turn +
    191 * depth;
}


// implement htbl.h functions here
