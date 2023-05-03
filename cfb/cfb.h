
#ifndef _CFB_H_
#define _CFB_H_

#include <stdint.h>

/**
 * @brief CFB 加密
 *
 * @param K 密钥
 * @param IV
 * @param P 明文
 * @param len 明文长度（in bytes）
 * @param k 反馈长度（in bytes）
 * @param C 密文输出
 */
void cfb_enc(const uint8_t *K, const uint8_t *IV, const uint8_t *P, int len, int k, uint8_t *C);

/**
 * @brief CFB 解密
 *
 * @param K 密钥
 * @param IV
 * @param C 密文
 * @param len 密文长度（in bytes）
 * @param k 反馈长度（in bytes）
 * @param P 明文输出
 */
void cfb_dec(const uint8_t *K, const uint8_t *IV, const uint8_t *C, int len, int k, uint8_t *P);

#endif // _CFB_H_