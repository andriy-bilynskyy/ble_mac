#include "ble_mac_ext.h"

/*******************************************************************************
 * Platform dependent implementation
 ******************************************************************************/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <aes.h>                                                /* tiny aes c */


void ble_mac_ext_random(void *buf, size_t buf_len)
{
	static bool random_inited;

	if (!random_inited) {
		random_inited = true;
		srand((unsigned)time(NULL));
	}
	for (size_t i = 0; i < buf_len; i++) {
		((uint8_t *)buf)[i] = rand();
	}
}

void ble_mac_ext_aes_ecb128(
	const uint8_t key[BLE_MAC_EXT_AES128_SIZE],
	const uint8_t in[BLE_MAC_EXT_AES128_SIZE],
	uint8_t out[BLE_MAC_EXT_AES128_SIZE])
{
	struct AES_ctx ctx;

	AES_init_ctx(&ctx, key);
	memcpy(out, in, BLE_MAC_EXT_AES128_SIZE);
	AES_ECB_encrypt(&ctx, out);
}
