#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// `uintN_t` has a lot of advantages like portability

uint8_t main() {
    // a 32-bit integer is stored as 4 bytes (4 * 8 = 32) in memory!
    uint32_t x = 255 * 2;
    uint8_t *bytes = (uint8_t*)&x;
    printf("the bytes, laid out in memory, (probably) in little endian:\n%u, %u, %u, %u\n", bytes[0], bytes[1], bytes[2], bytes[3]);

    // pointer arithmetic depends on the type of the thing the pointer points to!
    uint16_t *y = malloc(4);
    printf(
        "%p - %p = %ld, not %ld!\n",
        y + 1, y,
        (uint8_t*)(y + 1) - (uint8_t*)y,
        (y + 1) - y
    );

    return 5;
}
