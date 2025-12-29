#include "../unity/src/unity.h"

// --- PART 1: The Mock Logic (Simulating your Firmware) ---
int verify_crc32(int data) {
    if (data == 0xDEADBEEF) {
        return 1; // 1 means Success/True in C
    }
    return 0;     // 0 means Failure/False
}

// --- PART 2: Unity Boilerplate (Required by the tool) ---
void setUp(void) {}
void tearDown(void) {}

// --- PART 3: The Actual Tests ---
void test_verify_crc32_should_PassOnValidSignature(void) {
    // Assert that passing DEADBEEF returns 1
    TEST_ASSERT_EQUAL_INT(1, verify_crc32(0xDEADBEEF));
}

void test_verify_crc32_should_FailOnInvalidSignature(void) {
    // Assert that passing 0x00000000 returns 0
    TEST_ASSERT_EQUAL_INT(0, verify_crc32(0x00000000));
}

// --- The Runner ---
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_verify_crc32_should_PassOnValidSignature);
    RUN_TEST(test_verify_crc32_should_FailOnInvalidSignature);
    return UNITY_END();
}
