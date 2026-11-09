/**
 * @file    Example_ByteOrder.c
 * @brief   Byte order of integers, shift-based serialization, bit-fields, and alignment queries
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct permission {
    unsigned int read    : 1;
    unsigned int write   : 1;
    unsigned int execute : 1;
    unsigned int level   : 4;
};

// Writes v in big-endian order. The shifts work on the value, so the result
// does not depend on the byte order of the host.
static void store_be32(unsigned char out[4], uint32_t v)
{
    out[0] = (unsigned char)(v >> 24);
    out[1] = (unsigned char)(v >> 16);
    out[2] = (unsigned char)(v >> 8);
    out[3] = (unsigned char)v;
}

static uint32_t load_be32(const unsigned char in[4])
{
    return ((uint32_t)in[0] << 24) | ((uint32_t)in[1] << 16) |
           ((uint32_t)in[2] << 8)  |  (uint32_t)in[3];
}

int main(void)
{
    // Inspect the bytes of an integer through unsigned char
    uint32_t value = 0x12345678;
    const unsigned char *byte = (const unsigned char *)&value;
    printf("in memory:");
    for (size_t i = 0; i < sizeof value; i++) {
        printf(" %02x", byte[i]);
    }
    printf(" (%s-endian host)\n", byte[0] == 0x78 ? "little" : "big");

    // A portable byte order for files and networks
    unsigned char wire[4];
    store_be32(wire, value);
    printf("big-endian: %02x %02x %02x %02x -> 0x%08x\n",
           wire[0], wire[1], wire[2], wire[3], load_be32(wire));

    // Bit-fields pack small unsigned values, but their layout is implementation-defined
    struct permission p = {1, 0, 1, 5};
    printf("sizeof(struct permission) = %zu, level = %u\n", sizeof p, p.level);

    // Alignment requirements and a safe way to read a misaligned integer
    printf("alignof(int) = %zu, alignof(double) = %zu, alignof(max_align_t) = %zu\n",
           alignof(int), alignof(double), alignof(max_align_t));

    unsigned char packed[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int word;
    memcpy(&word, packed + 1, sizeof word);
    printf("memcpy from offset 1: 0x%08x\n", (unsigned)word);

    return 0;
}
