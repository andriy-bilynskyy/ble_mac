#ifndef BLE_MAC_EXT_H_
#define BLE_MAC_EXT_H_

#include <stddef.h>
#include <stdint.h>


#define BLE_MAC_EXT_AES128_SIZE           16


void ble_mac_ext_random(void *buf, size_t buf_len);
void ble_mac_ext_aes_ecb128(
	const uint8_t key[BLE_MAC_EXT_AES128_SIZE],
	const uint8_t in[BLE_MAC_EXT_AES128_SIZE],
	uint8_t out[BLE_MAC_EXT_AES128_SIZE]);

#endif /* BLE_MAC_EXT_H_ */
