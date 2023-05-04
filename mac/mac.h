
#ifndef _MAC_H_
#define _MAC_H_

#include <stdint.h>

/**
 * @brief MAC
 *
 * @param K 密钥
 * @param D Data
 * @param len Data Length（in bytes）
 * @param C  Message Authentication Code
 */
void mac(const uint8_t *K, const uint8_t *D, int len, uint8_t *C);

#endif // _MAC_H_