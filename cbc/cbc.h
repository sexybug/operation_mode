
#ifndef _CBC_H_
#define _CBC_H_

#include <stdint.h>

/**
 * @brief CBC 加密
 *
 * @param K 密钥
 * @param IV
 * @param P 明文
 * @param len 明文长度（in bytes）
 * @param C 密文输出
 */
void cbc_enc(const uint8_t *K, const uint8_t *IV, const uint8_t *P, int len, uint8_t *C);

/**
 * @brief CBC 解密
 *
 * @param K 密钥
 * @param IV
 * @param C 密文
 * @param len 密文长度（in bytes）
 * @param P 明文输出
 */
void cbc_dec(const uint8_t *K, const uint8_t *IV, const uint8_t *C, int len, uint8_t *P);

#endif // _CBC_H_