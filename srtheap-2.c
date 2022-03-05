#include <stdlib.h>
#include <string.h>
#include "srt.h"

void done(char *array, size_t nelem, size_t size, size_t up, int (*compar)(const void *, const void *));

void srtheap(void *base, size_t nelem, size_t size, int (*compar)(const void *, const void *)) {
    char *array;
    size_t i;


    array = malloc((size + 1) * nelem);
    memcpy(array + size, base, nelem * size);

    for (i = nelem / 2; i >= 1; i--) {
        done(array, nelem, size, i, compar);
    }


    for (i = nelem; i > 1; i--) {

        swap(array + size, array + i * size, size);
        done(array, i - 1, size, 1, compar);
    }

    memcpy(base, array + size, nelem * size);
    free(array);

}


void done(char *array, size_t nelem, size_t size, size_t up, int (*compar)(const void *, const void *)) {
    size_t down;
    while ((down = 2 * up) <= nelem) {
        if (down + 1 <= nelem && compar(array + down * size, array + (down + 1) * size) < 0) {
            down = down + 1;
        }
        if (compar(array + up * size, array + down * size) < 0) {
            swap(array + up * size, array + down * size, size);
            up = down;
        } else {
            break;
        }
    }
}
