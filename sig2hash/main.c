#include <stdio.h>
#include <assert.h>
#include <gmp.h>

#define APP_E 3
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

#define APP_KEY_MOD APP_CUSTOM_KEY_MOD

int main(int argc, char *argv[])
{
    mpz_t sig;
    mpz_t mod;
    mpz_t hash;

    assert(argc == 2);

    mpz_init(hash);
    mpz_init_set_str(sig, argv[1], 16);
    mpz_init_set_str(mod, APP_KEY_MOD, 16);

    mpz_powm_ui(hash, sig, APP_E, mod);

    mpz_out_str(stdout, 16, hash);
    fprintf(stdout, "\n");

    return 0;
}
