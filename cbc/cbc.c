#include "cbc.h"
#include "../sm4/sm4.h"

/**
 * @brief 异或 Z = X ^ Y
 *
 * @param X
 * @param Y
 * @param len (in bytes)
 * @param Z
 */
static void XOR(const uint8_t *X, const uint8_t *Y, int len, uint8_t *Z)
{
    for (int i = 0; i < len; i++)
    {
        Z[i] = X[i] ^ Y[i];
    }
}

void cbc_enc(const uint8_t *K, const uint8_t *IV, const uint8_t *P, int len, uint8_t *C)
{
    // algorithm block length (in bytes)
    int n = 16;
    uint8_t buf[16];

    XOR(P, IV, n, buf);
    SM4_Encrypt(K, buf, n, C);
    P += n;
    C += n;

    int i = 2, q = len / n;
    while (i <= q)
    {
        XOR(P, C - n, n, buf);
        SM4_Encrypt(K, buf, n, C);
        P += n;
        C += n;
        i++;
    }
}

void cbc_dec(const uint8_t *K, const uint8_t *IV, const uint8_t *C, int len, uint8_t *P)
{
    // algorithm block length (in bytes)
    int n = 16;
    uint8_t buf[16];

    SM4_Decrypt(K, C, n, buf);
    XOR(buf, IV, n, P);
    C += n;
    P += n;

    int i = 2, q = len / n;
    while (i <= q)
    {
        SM4_Decrypt(K, C, n, buf);
        XOR(buf, C - n, n, P);
        P += n;
        C += n;
        i++;
    }
}