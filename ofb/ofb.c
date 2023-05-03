#include "ofb.h"
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

/**
 * @brief update feedback buffer with F
 * 
 * @param FB feedback buffer
 * @param FB_len feedback buffer length (in bytes)
 * @param F 
 * @param F_len 
 */
static void update_FB(uint8_t *FB, int FB_len, const uint8_t *F, int F_len)
{
    int i, j;
    for (i = 0; i < FB_len - F_len; i++)
    {
        FB[i] = FB[i + F_len];
    }
    j = 0;
    while (i < FB_len)
    {
        FB[i] = F[j];
        i++;
        j++;
    }
}

void ofb_enc(const uint8_t *K, const uint8_t *IV, const uint8_t *P, int len, int k, uint8_t *C)
{
    // algorithm block length (in bytes)
    int n = 16;
    uint8_t X[16], Y[16];

    int i = 1, q = len / k;
    memcpy(X, IV, n);
    while (i <= q)
    {
        SM4_Encrypt(K, X, n, Y);
        XOR(P, Y, k, C);
        memcpy(X,Y,n);

        P += k;
        C += k;
        i++;
    }
}

void ofb_dec(const uint8_t *K, const uint8_t *IV, const uint8_t *C, int len, int k, uint8_t *P)
{
    // algorithm block length (in bytes)
    int n = 16;
    uint8_t X[16], Y[16];

    int i = 1, q = len / k;
    memcpy(X, IV, n);
    while (i <= q)
    {
        SM4_Encrypt(K, X, n, Y);
        XOR(C, Y, k, P);
        memcpy(X,Y,n);

        P += k;
        C += k;
        i++;
    }
}