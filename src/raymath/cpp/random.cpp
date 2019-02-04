#include "random.h"
#include <cstdlib>
#include "types.h"

vector random_in_usphere() {
    vector vec;
    do {
        vec = 2 * vector(drand48(), drand48(), drand48()) - vector(1, 1, 1);
    } while (vec.squaredNorm() >= 1.0);
    return vec;
}
