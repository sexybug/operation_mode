
#include <stdio.h>
#include <string.h>
#include "../test.h"
#include "xts.h"
#define BLOCK_LEN 16
//GF(2^128)乘上生成元alpha，输入为大端表示
int gf128_mult_alpha_big(unsigned char* p)
{
	unsigned char temp, carry = 0;
	unsigned char p_byte[BLOCK_LEN];
	memcpy(p_byte, p, BLOCK_LEN);

	for (int i = 0; i < 16; i++)
	{
		temp = (p_byte[i] & 0x01) ? 0x80 : 0;
		p_byte[i] = carry | (p_byte[i] >> 1);
		carry = temp;
	}
	p_byte[0] = (carry) ? (p_byte[0] ^ 0xe1) : p_byte[0];

	memcpy(p, p_byte, BLOCK_LEN);
	return 1;
}
//GF(2^128)上乘法，输入为大端表示
int gf128_modmul(unsigned char* p_in, unsigned char* key, unsigned char* p_out)
{
	unsigned char temp;
	unsigned char piv[BLOCK_LEN], pt[BLOCK_LEN], ct[BLOCK_LEN];
	memcpy(piv, key, BLOCK_LEN);
	memcpy(pt, p_in, BLOCK_LEN);

	memset(ct, 0, BLOCK_LEN);
	int i, j, k;
	for (i = 0; i < 128; i++)
	{

		j = i / 8;
		temp = (piv[j] & 0x80);
		piv[j] = piv[j] << 1;
		if (temp)
		{
			for (k = 0; k < BLOCK_LEN; k++)
			{
				ct[k] ^= pt[k];
			}
		}
		gf128_mult_alpha_big(pt);
	}

	memcpy(p_out, ct, BLOCK_LEN);

	return 1;
}

int main(int argc, char **argv)
{
    uint8_t K1_str[32] = "2B7E151628AED2A6ABF7158809CF4F3C";
    uint8_t K2_str[32] = "000102030405060708090A0B0C0D0E0F";

    uint8_t TW_str[32] = "F0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF";

    uint8_t P_str[128] = "6BC1BEE22E409F96E93D7E117393172A"
                         "AE2D8A571E03AC9C9EB76FAC45AF8E51"
                         "30C81C46A35CE411E5FBC1191A0A52EF"
                         "F69F2445DF4F9B17";

    uint8_t C_str[128] = "E9538251C71D7B80BBE4483FEF497BD1"
                         "2C5C581BD6242FC51E08964FB4F60FDB"
                         "0BA42F63499279213D318D2C11F6886E"
                         "903BE7F93A1B3479";

    uint8_t K1[16], K2[16],TW[16], P[64], C[64], enc_out[64], dec_out[64];
    HexString2Hex(K1_str, 16, K1);
    HexString2Hex(K2_str, 16, K2);
    HexString2Hex(TW_str, 16, TW);
    HexString2Hex(P_str, 64, P);
    HexString2Hex(C_str, 64, C);

    // 加密测试
    xts_enc(K1, K2,TW, P, 56, enc_out);

    printf("enc:\n");
    dump_mem(enc_out, 56);
    printf("memcmp result: %d\n", memcmp(enc_out, C, 56));

    uint8_t U[16];
    uint8_t V[16],W[16];
    memset(U,0,16);
    memset(V,0,16);
    U[0]=0x80;
    V[0]=0x80;
    GF2_128_Multiply(U,V,W);
    dump_mem(W,16);
    gf128_modmul(U,V,W);
    dump_mem(W,16);

    // 解密测试
    xts_dec(K1, K2,TW, C, 56, dec_out);

    printf("dec:\n");
    dump_mem(dec_out, 56);
    printf("memcmp result: %d\n", memcmp(dec_out, P, 56));
    return 0;
}