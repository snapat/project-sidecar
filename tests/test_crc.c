#include "unity.h"
#include "monocypher.h"
#include <string.h>

int verify_firmware_signature(const uint8_t* firmware, size_t length, const uint8_t* signature, const uint8_t* public_key);
//implemented in bootloader_secure/bootloader.c

void setUp(void) {}
void tearDown(void) {}

void test_Bootloader_Should_Reject_Tampered_Firmware(void)
{
    uint8_t firmware[4] = {0xAA, 0xBB, 0xCC, 0xDD}; //test case
    uint8_t signature[64]; // output of ed25519 signature is always 64 bytes

    uint8_t public_key[32]; //public key for verification
    uint8_t secret_key[64]; //secret key now 64 byte as of monocypher v4

    uint8_t seed[32];
    memset(seed, 0x42, 32);
    
    crypto_eddsa_key_pair(secret_key, public_key, seed);
    crypto_eddsa_sign(signature, secret_key, firmware, sizeof(firmware));
    
    firmware[0] = 0x00;

    int is_valid = verify_firmware_signature(firmware, sizeof(firmware), signature, public_key);
    TEST_ASSERT_EQUAL_INT(0, is_valid);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_Bootloader_Should_Reject_Tampered_Firmware);
    return UNITY_END();
}