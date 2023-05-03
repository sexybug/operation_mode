
#ifndef _HCTR_H_
#define _HCTR_H_

#include <stdint.h>


/**
 * @brief HCTR 加密
 * 
 * @param K1 
 * @param K2 
 * @param TW 
 * @param P 明文
 * @param len 明文长度（in bytes）
 * @param C 密文输出
 */
void hctr_enc(const uint8_t *K1, const uint8_t *K2,const uint8_t *TW, const uint8_t *P, int len, uint8_t *C);

/**
 * @brief HCTR 解密
 *
 * @param K1 
 * @param K2 
 * @param TW 
 * @param C 密文
 * @param len 明文长度（in bytes）
 * @param P 明文输出
 */
void hctr_dec(const uint8_t *K1, const uint8_t *K2, const uint8_t *TW, const uint8_t *C, int len, uint8_t *P);

#endif // _HCTR_H_