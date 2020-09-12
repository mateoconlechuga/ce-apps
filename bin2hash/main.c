#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define ROR(x, y) ((x) >> (y) | (x) << (32 - (y)))

static void process_block(uint32_t *state, const void *block)
{
    static const uint32_t k[64] =
    {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };
    uint32_t a, b, c, d, e, f, g, h;
    uint32_t w[64];
    int i;

    memcpy(w, block, 64);
    for (i = 16; i < 64; i++)
    {
        uint32_t s0 = ROR(w[i-15], 7) ^ ROR(w[i-15], 18) ^ (w[i-15] >> 3);
        uint32_t s1 = ROR(w[i-2], 17) ^ ROR(w[i-2], 19) ^ (w[i-2] >> 10);
        w[i] = w[i-16] + s0 + w[i-7] + s1;
    }

    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    f = state[5];
    g = state[6];
    h = state[7];

    for (i = 0; i < 64; i++)
    {
        uint32_t s0 = ROR(a, 2) ^ ROR(a, 13) ^ ROR(a, 22);
        uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
        uint32_t t2 = s0 + maj;
        uint32_t s1 = ROR(e, 6) ^ ROR(e, 11) ^ ROR(e, 25);
        uint32_t ch = (e & f) ^ (~e & g);
        uint32_t t1 = h + s1 + ch + k[i] + w[i];

        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;
}

int main(int argc, char *argv[])
{
    uint32_t state[8] =
    {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
    uint8_t *buffer;
    unsigned long binsize;
    unsigned long numbits;
    unsigned long msgsize;
    unsigned long padsize;
    unsigned long offset;
#if DEBUG
    unsigned int i;
#endif
    FILE *fd;

    assert(argc == 2);

    fd = fopen(argv[1], "rb");
    assert(fd);

    fseek(fd, 0L, SEEK_END);
    binsize = ftell(fd);
    fseek(fd, 0L, SEEK_SET);

    buffer = calloc(binsize + 128, sizeof(uint8_t));
    assert(buffer);

    assert(fread(buffer, sizeof(uint8_t), binsize, fd) == binsize);
    fclose(fd);

    buffer[binsize] = 0x80;
    padsize = 0x40 - (binsize & 0x3f);
    if (padsize < 9) padsize += 0x40;
    msgsize = binsize + padsize;
    numbits = binsize * 8;

    buffer[msgsize - 8] = (numbits >> 56) & 0xff;
    buffer[msgsize - 7] = (numbits >> 48) & 0xff;
    buffer[msgsize - 6] = (numbits >> 40) & 0xff;
    buffer[msgsize - 5] = (numbits >> 32) & 0xff;
    buffer[msgsize - 4] = (numbits >> 24) & 0xff;
    buffer[msgsize - 3] = (numbits >> 16) & 0xff;
    buffer[msgsize - 2] = (numbits >> 8) & 0xff;
    buffer[msgsize - 1] = (numbits >> 0) & 0xff;

#if DEBUG
    for (i = 0; i < msgsize; i++)
    {
        if (!(i % 64)) fprintf(stdout, "\n");
        fprintf(stdout, "%02x", buffer[i]);
    }
    fprintf(stdout, "\n");
    fprintf(stdout, "bin size: %lu\n", binsize);
    fprintf(stdout, "pad size: %lu\n", padsize);
    fprintf(stdout, "msg size: %lu\n", msgsize);
#endif

    offset = 0;
    while (offset != msgsize)
    {
        process_block(state, buffer + offset);
        offset += 64;
    }

    for (int i = sizeof(state) - 1; i >= 0; --i)
    {
        fprintf(stdout, "%02x", ((uint8_t*)state)[i]);
    }

    fprintf(stdout, "\n");

    free(buffer);

    return 0;
}
