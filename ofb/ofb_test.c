
#include <stdio.h>
#include <string.h>
#include "../test.h"
#include "ofb.h"

int main(int argc, char **argv)
{
    uint8_t K_str[32] = "2B7E151628AED2A6ABF7158809CF4F3C";

    uint8_t IV_str[32] = "000102030405060708090A0B0C0D0E0F";

    uint8_t P_str[128] = "6BC1BEE22E409F96E93D7E117393172A"
                         "AE2D8A571E03AC9C9EB76FAC45AF8E51"
                         "30C81C46A35CE411E5FBC1191A0A52EF"
                         "F69F2445DF4F9B17AD2B417BE66C3710";

    uint8_t C_str[128] = "BC710D762D070B26361DA82B54565E46"
    "07A0C62834740AD3240D239125E11621"
    "D476B21CC9F04951F0741D2EF9E09498"
    "1584FC142BF13AA626B82F9D7D076CCE";

    uint8_t K[16], IV[16], P[64], C[64], enc_out[64], dec_out[64];
    HexString2Hex(K_str, 16, K);
    HexString2Hex(IV_str, 16, IV);
    HexString2Hex(P_str, 64, P);
    HexString2Hex(C_str, 64, C);

    // 加密测试
    ofb_enc(K, IV, P, 64, 128/8, enc_out);

    printf("enc:\n");
    dump_mem(enc_out, 64);
    printf("memcmp result: %d\n", memcmp(enc_out, C, 64));

    // 解密测试
    ofb_dec(K, IV, C, 64, 128/8, dec_out);

    printf("dec:\n");
    dump_mem(dec_out, 64);
    printf("memcmp result: %d\n", memcmp(dec_out, P, 64));
    return 0;
}