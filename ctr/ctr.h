
#ifndef _CTR_H_
#define _CTR_H_

#include <stdint.h>

/**
 * @brief CTR 加密
 *
 * @param K 密钥
 * @param IV 计数器初值
 * @param P 明文
 * @param len 明文长度（in bytes）
 * @param C 密文输出
 */
void ctr_enc(const uint8_t *K, const uint8_t *IV, const uint8_t *P, int len, uint8_t *C);

/**
 * @brief CTR 解密
 *
 * @param K 密钥
 * @param IV 计数器初值
 * @param C 密文
 * @param len 密文长度（in bytes）
 * @param P 明文输出
 */
void ctr_dec(const uint8_t *K, const uint8_t *IV, const uint8_t *C, int len, uint8_t *P);

#endif // _CTR_H_