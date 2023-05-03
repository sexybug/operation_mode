
#ifndef _ECB_H_
#define _ECB_H_

#include <stdint.h>

/**
 * @brief ECB 加密
 *
 * @param K 密钥
 * @param P 明文
 * @param len 明文长度（in bytes）
 * @param C 密文输出
 */
void ecb_enc(const uint8_t *K, const uint8_t *P, int len, uint8_t *C);

/**
 * @brief ECB 解密
 *
 * @param K 密钥
 * @param C 密文
 * @param len 密文长度（in bytes）
 * @param P 明文输出
 */
void ecb_dec(const uint8_t *K, const uint8_t *C, int len, uint8_t *P);

#endif // _ECB_H_