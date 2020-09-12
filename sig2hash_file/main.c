#include <stdio.h>
#include <assert.h>
#include <gmp.h>

#define APP_E 3
#define APP_KEY_MOD \
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

int main(int argc, char *argv[])
{
    FILE *fd;
    unsigned char buffer[256];
    unsigned long binsize;
    mpz_t sig;
    mpz_t mod;
    mpz_t hash;

    assert(argc == 2);
    fd = fopen(argv[1], "rb");
    assert(fd);

    fseek(fd, 0L, SEEK_END);
    binsize = ftell(fd);
    assert(binsize == 256);
    fseek(fd, 0L, SEEK_SET);

    assert(fread(buffer, 1, binsize, fd) == binsize);
    fclose(fd);

    mpz_init(hash);
    mpz_init(sig);
    mpz_import(sig, 256, -1, 1, -1, 0, buffer);
    mpz_init_set_str(mod, APP_KEY_MOD, 16);

    mpz_powm_ui(hash, sig, APP_E, mod);

    mpz_out_str(stdout, 16, hash);
    fprintf(stdout, "\n");

    return 0;
}
