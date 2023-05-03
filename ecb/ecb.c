#include "ecb.h"
#include "../sm4/sm4.h"

void ecb_enc(const uint8_t *K, const uint8_t *P, int len, uint8_t *C)
{
    // algorithm block length (in bytes)
    int n = 16;

    int i = 1, q = len / n;
    while (i <= q)
    {
        SM4_Encrypt(K, P, n, C);
        P += n;
        C += n;
        i++;
    }
}

void ecb_dec(const uint8_t *K, const uint8_t *C, int len, uint8_t *P)
{
    // algorithm block length (in bytes)
    int n = 16;

    int i = 1, q = len / n;
    while (i <= q)
    {
        SM4_Decrypt(K, C, n, P);
        C += n;
        P += n;
        i++;
    }
}