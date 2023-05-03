
#ifndef _OFBNLF_H_
#define _OFBNLF_H_

#include <stdint.h>

/**
 * @brief OFBNLF 加密
 *
 * @param K 密钥
 * @param IV 
 * @param P 明文
 * @param len 明文长度（in bytes）
 * @param C 密文输出
 */
void ofbnlf_enc(const uint8_t *K, const uint8_t *IV, const uint8_t *P, int len, uint8_t *C);

/**
 * @brief OFBNLF 解密
 *
 * @param K 密钥
 * @param IV 
 * @param C 密文
 * @param len 密文长度（in bytes）
 * @param P 明文输出
 */
void ofbnlf_dec(const uint8_t *K, const uint8_t *IV, const uint8_t *C, int len, uint8_t *P);

#endif // _OFBNLF_H_