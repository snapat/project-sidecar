#include "unity.h"
#include "monocypher.h"
#include <string.h>

/* ==========================================
   FORWARD DECLARATION
   (The function we haven't built yet)
   ========================================== */
int verify_firmware_signature(const uint8_t* firmware, size_t length, const uint8_t* signature, const uint8_t* public_key);

void setUp(void) {}
void tearDown(void) {}

/* ==========================================
   TEST CASE 1: The "Hacker" Check
   ========================================== */
void test_Bootloader_Should_Reject_Tampered_Firmware(void) {
    // 1. SETUP: Create a valid "Golden" firmware image
    uint8_t firmware[4] = {0xAA, 0xBB, 0xCC, 0xDD}; 
    uint8_t signature[64];
    uint8_t public_key[32];
    uint8_t secret_key[32];

    // Generate valid keys (Simulating the factory signing process)
    crypto_sign_key_pair(public_key, secret_key, crypto_memcmp);
    crypto_sign(signature, secret_key, public_key, firmware, sizeof(firmware));

    // 2. ATTACK: Tamper with the firmware (Simulate corruption or hacking)
    firmware[0] = 0x00; // Flip the first byte

    // 3. ASSERT: The verification MUST fail (return 0)
    int is_valid = verify_firmware_signature(firmware, sizeof(firmware), signature, public_key);
    TEST_ASSERT_EQUAL_INT(0, is_valid);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_Bootloader_Should_Reject_Tampered_Firmware);
    return UNITY_END();
}