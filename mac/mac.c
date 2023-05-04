#include "mac.h"
#include <string.h>
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

void mac(const uint8_t *K, const uint8_t *D, int len, uint8_t *C)
{
    // algorithm block length (in bytes)
    int n = 16;
    uint8_t Opre[16], Ebuf[16];

    SM4_Encrypt(K, D, n, Opre);
    D += n;

    int i = 2;
    while (i <= len / n)
    {
        XOR(D, Opre, n, Ebuf);
        SM4_Encrypt(K, Ebuf, n, Opre);
        D += n;
        i++;
    }
    int d = len % n;
    if (len % n != 0)
    {
        memcpy(Ebuf, D, d);
        memset(Ebuf + d, 0, n - d);
        XOR(Ebuf, Opre, n, Ebuf);
        SM4_Encrypt(K, Ebuf, n, Opre);
    }
    memcpy(C, Opre, n);
}