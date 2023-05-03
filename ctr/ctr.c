#include "ctr.h"
#include <string.h>
#include "../sm4/sm4.h"

/**
 * @brief 计数器自增1
 *
 * @param T 计数器值
 * @param len ctr长度(in bytes)
 */
static void increase(uint8_t *T, int len)
{
    int i = len - 1;
    T[i]++;
    while (T[i] == 0 && i > 0)
    {
        i--;
        T[i]++;
    }
}

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

void ctr_enc(const uint8_t *K, const uint8_t *IV, const uint8_t *P, int len, uint8_t *C)
{
    // algorithm block length (in bytes)
    int n = 16;
    uint8_t T[16],Y[16];

    memcpy(T, IV, 16);
    int i = 1;
    while (i <= len / n)
    {
        SM4_Encrypt(K, T, n, Y);
        XOR(P, Y, n, C);
        P += n;
        C += n;
        increase(T, n);
        i++;
    }
    int d = len % n;
    if (d != 0)
    {
        SM4_Encrypt(K, T, n, Y);
        XOR(P, Y, d, C);
    }
}

void ctr_dec(const uint8_t *K, const uint8_t *IV, const uint8_t *C, int len, uint8_t *P)
{
    return ctr_enc(K, IV, C, len, P);
}