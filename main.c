#include <stdint.h>
#include <stdio.h>

#include "ble_mac_ext.h"
#include "ble_mac.h"


static void print_buf(const char *comment, const void *buf, size_t buf_len)
{
	printf("%s[%u]:", comment, (unsigned)buf_len);
	for (size_t i = 0; i < buf_len; i++) {
		printf(" %02x", ((uint8_t *)buf)[i]);
	}
	printf("\n");
}


int main(void)
{
	uint8_t addr[6];
	uint8_t key[16];

	ble_mac_ext_random(key, sizeof(key));

	ble_mac_generate_addr_private_resolvable(addr, key);

	print_buf("key ", key, sizeof(key));
	print_buf("addr", addr, sizeof(addr));

	printf("private resolvable %u\n",
		ble_mac_check_addr_private_resolvable(addr, key));
}
