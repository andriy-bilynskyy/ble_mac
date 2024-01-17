#include "ble_mac.h"

#include <string.h>


void ble_mac_generate_addr_static(uint8_t mac[BLE_MAC_ADDR_SIZE])
{
	ble_mac_ext_random(mac, BLE_MAC_ADDR_SIZE);
	mac[BLE_MAC_ADDR_SIZE - 1] |= 0xc0;           /* 0b11 */
}

bool ble_mac_check_addr_static(const uint8_t mac[BLE_MAC_ADDR_SIZE])
{
	bool result = false;

	if ((mac[BLE_MAC_ADDR_SIZE - 1] & 0xc0) == 0xc0) {
		result = true;
	}

	return result;
}

void ble_mac_generate_addr_private_resolvable(
	uint8_t mac[BLE_MAC_ADDR_SIZE],
	const uint8_t irk[BLE_MAC_EXT_AES128_SIZE])
{
	ble_mac_ext_random(&mac[BLE_MAC_ADDR_SIZE / 2], BLE_MAC_ADDR_SIZE / 2);
	mac[5] = ((mac[5] & 0x3f) | 0x40);            /* 0b01 */

	uint8_t tmp[BLE_MAC_EXT_AES128_SIZE];

	memcpy(tmp, &mac[BLE_MAC_ADDR_SIZE / 2], BLE_MAC_ADDR_SIZE / 2);
	memset(&tmp[BLE_MAC_ADDR_SIZE / 2], 0, sizeof(tmp) - BLE_MAC_ADDR_SIZE / 2);
	ble_mac_ext_aes_ecb128(irk, tmp, tmp);
	memcpy(mac, tmp, BLE_MAC_ADDR_SIZE / 2);
}

bool ble_mac_check_addr_private_resolvable(
	const uint8_t mac[BLE_MAC_ADDR_SIZE],
	const uint8_t irk[BLE_MAC_EXT_AES128_SIZE])
{
	bool result = false;

	if ((mac[BLE_MAC_ADDR_SIZE - 1] & 0xc0) == 0x40) {
		uint8_t tmp[BLE_MAC_EXT_AES128_SIZE];

		memcpy(tmp, &mac[BLE_MAC_ADDR_SIZE / 2], BLE_MAC_ADDR_SIZE / 2);
		memset(&tmp[BLE_MAC_ADDR_SIZE / 2], 0, sizeof(tmp) - BLE_MAC_ADDR_SIZE / 2);
		ble_mac_ext_aes_ecb128(irk, tmp, tmp);
		if (!memcmp(mac, tmp, BLE_MAC_ADDR_SIZE / 2)) {
			result = true;
		}
	}

	return result;
}

void ble_mac_generate_addr_private_non_resolvable(uint8_t mac[BLE_MAC_ADDR_SIZE])
{
	ble_mac_ext_random(mac, BLE_MAC_ADDR_SIZE);
	mac[BLE_MAC_ADDR_SIZE - 1] &= 0x3f;           /* 0b00 */
}

bool ble_mac_check_addr_private_non_resolvable(const uint8_t mac[BLE_MAC_ADDR_SIZE])
{
	bool result = false;

	if ((mac[BLE_MAC_ADDR_SIZE - 1] & 0xc0) == 0x00) {
		result = true;
	}

	return result;
}
