#ifndef _RAYMATH_RANDOM_H_
#define _RAYMATH_RANDOM_H_
#include "types.h"

vector random_in_usphere();
vector random_in_uhemisphere(const vector& normal);

scalar random_scalar();

#endif
