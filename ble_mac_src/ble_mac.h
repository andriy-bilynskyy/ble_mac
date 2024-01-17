#ifndef BLE_MAC_H_
#define BLE_MAC_H_

#include <stdint.h>
#include <stdbool.h>

#include "ble_mac_ext.h"


#define BLE_MAC_ADDR_SIZE                 6


void ble_mac_generate_addr_static(uint8_t mac[BLE_MAC_ADDR_SIZE]);
bool ble_mac_check_addr_static(const uint8_t mac[BLE_MAC_ADDR_SIZE]);

void ble_mac_generate_addr_private_resolvable(
	uint8_t mac[BLE_MAC_ADDR_SIZE],
	const uint8_t irk[BLE_MAC_EXT_AES128_SIZE]);
bool ble_mac_check_addr_private_resolvable(
	const uint8_t mac[BLE_MAC_ADDR_SIZE],
	const uint8_t irk[BLE_MAC_EXT_AES128_SIZE]);

void ble_mac_generate_addr_private_non_resolvable(uint8_t mac[BLE_MAC_ADDR_SIZE]);
bool ble_mac_check_addr_private_non_resolvable(const uint8_t mac[BLE_MAC_ADDR_SIZE]);

#endif /* BLE_MAC_H_ */
