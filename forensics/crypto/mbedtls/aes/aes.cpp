#include "mbedtls/aes.h"

#include <cstdint>

class Aes
{
public:
  Aes()
  {
    mbedtls_aes_init(&ctx);
  }

  ~Aes()
  {
    mbedtls_aes_free(&ctx);
  }

private:
  mbedtls_aes_context ctx;
};

int main(int argc, char *argv[])
{
  uint8_t key[32];
  Aes a;

  // ::mbedtls_aes_setkey_enc(&aes, key, 256);

  return 0;
}
