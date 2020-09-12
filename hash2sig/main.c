#include <stdio.h>
#include <assert.h>
#include <gmp.h>

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

#define APP_KEY_MOD APP_CUSTOM_KEY_MOD
#define APP_KEY_EXP APP_CUSTOM_KEY_EXP

int main(int argc, char *argv[])
{
    mpz_t sig;
    mpz_t exp;
    mpz_t mod;
    mpz_t hash;

    assert(argc == 2);

    mpz_init(sig);
    mpz_init_set_str(hash, argv[1], 16);
    mpz_init_set_str(mod, APP_KEY_MOD, 16);
    mpz_init_set_str(exp, APP_KEY_EXP, 16);

    mpz_powm(sig, hash, exp, mod);

    mpz_out_str(stdout, 16, sig);
    fprintf(stdout, "\n");

    return 0;
}
