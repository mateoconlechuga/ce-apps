#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <gmp.h>
 
#define APP_REAL_KEY_EXP \
  "8a8a15ffe28c79323c8988b06caf67fcc2" \
  "a2cb132baf628f9501e6aa5e90933e0445" \
  "5aca6419c58e892ec248b8411c3e3b4df4" \
  "e0bc9653a938ca0faaa396996c342a1559" \
  "4dc112fe7bee00025386846470a627ad13" \
  "cd3fb4efb6d737746d811e1c28d9a1ac92" \
  "a222deb2916fafc0d9a755e9b2e2e440c9" \
  "d744c445ecf74ee496"

#define APP_CUSTOM_KEY_EXP \
  "75f566e4f129d4e8bd54df7cb2758ebcba" \
  "49b1bb21d1658b325b2d0c4fe859fbcdff" \
  "943421a7646d9ab218a25ffde943b3c6fe" \
  "ad15af83337278e0dd3cf2ccfc130267ed" \
  "ae82b31e9cd65ba6226a41ddc4078ea316" \
  "198c83779563834adae022b3460e6e6b34" \
  "63469b8cfd6ce991c17fdd23de7c01f1eb" \
  "368d2877903dc24dea4afed157dd6101cf" \
  "7caaa9a0086a5f1303a91fedc516cbe31c" \
  "0ce4a7e508e1fb684312c1aace8ffda9b9" \
  "e1ce6d66c1887b6865b1e5676909d7a64f" \
  "957628ba08d0a23968794e55f9c30fb5cc" \
  "72c527f8d3e7024e5ac697dbc4ecfbcda9" \
  "6d07be2f5faba2773ebdb173a353eb7fe0" \
  "5d6485e8b72b2b7b278bba850e6a7b3bc293"

#define APP_REAL_KEY_MOD \
  "cfcf20ffd3d2b5cb5ace4d08a3071bfb23" \
  "f4309cc18713d75f82d9ff8dd8dcdd0668" \
  "082f9626a855cdc6236d1461aa5d58f4ef" \
  "511ae17d7dd52f177ff561e6224e3f2005" \
  "f4a19c7db9e500037d49c696a8f93b839d" \
  "b3df8f679242d32ea441ad2a3d467282db" \
  "f3344e0bda2787a1467b00de8c5456612e" \
  "c2e72668e372f656e35030961c9cbb4417" \
  "0eb2460340e5beaaf6564c5dd4fd3a9fd4" \
  "033bd5598c9279df49e6c29665e0de07de" \
  "889cd5b11d29c41662420665ce89b8d2b9" \
  "33074adb5f86bd5feafb0dc1c7e6f58838" \
  "24d7c7cb34115621c7475ebc8ba5009880" \
  "47b7349c4fd8fd230dcf28e5df2755beed" \
  "d6007fcf6aa0cef32066fb48a40222a6d523"

#define APP_CUSTOM_KEY_MOD \
  "b0f01a5769bebf5d1bff4f3b0bb0561b17" \
  "6e8a98b2ba1850cb88c39277dc86f9b4ff" \
  "5e4e327b16a4680b24f38ffcdde58daa7e" \
  "03a08744cd2bb5514bdb6c337a1c839be4" \
  "85c40cadeb418979339f62cca60b55f4a1" \
  "2652c533601544f04850340ce915a5a0ce" \
  "94e9e9537c235e5aa23fcbb5cdba02eae0" \
  "d1d3bcb3585ca374e11c2cb2fd07c8779f" \
  "c372ed1c47c50b3eb113a67632b2343fdf" \
  "4654fcdf9786794faeef5df69f8aed562b" \
  "78746b1f4853848e9bb13ae7c59059df11" \
  "58e31311a98b6cd29494a5058dd3c9230a" \
  "769c5ac40daaa7535d41e2cf8caae861dd" \
  "4056437eb4610ec2d355650a4898daad4f" \
  "f0c97faf4d397ebdde091e6d2f00183e7f3d"

#define KNOWN_BYTES (sizeof(APP_REAL_KEY_EXP) - 1) / 2

void rand_str(char *dest)
{
    unsigned int length = 512 - KNOWN_BYTES;

    dest += KNOWN_BYTES;

    while (length--)
    {
        *dest++ = "0123456789abcdef"[rand() & 15];
    }
}

void fill_str(char *dest)
{
    unsigned int length = 512 - KNOWN_BYTES;

    dest += KNOWN_BYTES;

    while (length--)
    {
        *dest++ = '0';
    }
}

int main(void)
{
    mpz_t sig;
    mpz_t exp;
    mpz_t mod;
    mpz_t hash;
    mpz_t comphash;
    unsigned int count0 = 0;
    unsigned int count1 = 0;
    static char expstr[513];
    unsigned int seed = clock();

    memset(expstr, 0, sizeof expstr);

    srand(seed);
    seed = rand();
    srand(seed);

#if TRY_REAL
    strcpy(expstr, APP_REAL_KEY_EXP);
    fill_str(expstr);
    fprintf(stdout, "rand seed: %u\n", seed);
    fprintf(stdout, "known bytes: %lu\n", KNOWN_BYTES);
    fprintf(stdout, "known bits: %lu\n", KNOWN_BYTES * 8);
#else
    strcpy(expstr, APP_CUSTOM_KEY_EXP);
#endif

    mpz_init(sig);
    mpz_init(exp);
    mpz_init(comphash);
    mpz_init_set_str(hash, "a43c003505d3dde28d2d653070646f926e3b1823e89446e57e38728f30eaee9e", 16);
#if TRY_REAL
    mpz_init_set_str(mod, APP_REAL_KEY_MOD, 16);
#else
    mpz_init_set_str(mod, APP_CUSTOM_KEY_MOD, 16);
#endif

    for (;;)
    {
        mpz_set_str(exp, expstr, 16);

        mpz_powm(sig, hash, exp, mod);
        mpz_powm_ui(comphash, sig, 3, mod);

        if (mpz_cmp(hash, comphash) == 0)
        {
            fprintf(stdout, "found exponent!\n");
            mpz_out_str(stdout, 16, exp);
            fprintf(stdout, "\n");
            break;
        }

        count0++;

        if (count0 == 1000)
        {
            count1++;
            fprintf(stdout, "tried %u thousand random exponents\n", count1);
            count0 = 0;
        }

        rand_str(expstr);
    }

    for (;;)
    {
        sleep(30);
    }

    return 0;
}
