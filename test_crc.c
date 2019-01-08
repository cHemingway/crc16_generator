/* 
 * Unit tests for CRC 16 functions
 * Assumes POLY=0x8fdb, INIT = 0xffff, will fail if these are changed
 * Author: Chris Hemingway B8062399
 * Date: 01/12/2018
 */

#include <stdio.h>

/* "Greatest" unit test framework: https://github.com/silentbicycle/greatest */
#include "greatest.h"

#include "crc.h"

/* For zero input, should get nonzero output */
TEST nonzero_output(void) {
    uint8_t message[] = {0x00, 0x00, 0x00, 0x00};
    uint16_t crc = CalculateCRC(message, sizeof(message));
    ASSERT(crc!=0);
    PASS();
}

/* For zero input, should get non initial message */
TEST noninit_output(void) {
    uint8_t message[] = {0x00, 0x00, 0x00, 0x00};
    uint16_t crc = CalculateCRC(message, sizeof(message));
    ASSERT(crc!=0xffff);
    PASS();
}

/* Test for some known values */
TEST known_crc(void) {
    uint8_t message[] = {0xaa, 0xde, 0xad, 0xbe, 0xef};
    uint8_t message2[] = {0x0b, 0xb9, 0x7f, 0x4c, 0x4a, 0x32, 0xe6, 0x6b, 0x5e, 
                          0xef, 0x86, 0xb1, 0xc2, 0x4b, 0x31};
    uint16_t crc = CalculateCRC(message, sizeof(message));
    ASSERT_EQ(0xC149, crc);

    crc = CalculateCRC(message2, sizeof(message2));
    ASSERT_EQ(0x5BEE, crc);
    
    PASS();
}

/* Test a very long message */
TEST long_message(void) {
    uint8_t message[4096];
    uint16_t crc;
    int i;
    for (i=0; i<sizeof(message); i++) {
        message[i] = i % 256;
    }
    crc = CalculateCRC(message, sizeof(message));
    ASSERT_EQ(0x1fb5, crc);
    PASS();
}

/* Collect tests into a suite */
SUITE(the_suite) {
    RUN_TEST(nonzero_output);
    RUN_TEST(noninit_output);
    RUN_TEST(known_crc);
    RUN_TEST(long_message);
}

/* Main definitions for Greatest */
GREATEST_MAIN_DEFS();

int main(int argc, char*argv[]) {
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(the_suite);
    GREATEST_MAIN_END(); 
}
