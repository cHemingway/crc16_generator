/*
 * CRC-16 calculation routine
 * POLY = 0x8fdb, INIT = 0xffff, non reversed, no final XOR
 * Author: Chris Hemingway - B8062339
 * Date: 01/12/2018
 */

#include "crc.h"

/*
 * CRC Table calculated using crc16_gen.py, in this folder
 * Poly is from Koopman's Best CRC Polynomials: https://users.ece.cmu.edu/~koopman/crc/
 * This polynomial is best known for <=15 byte message, protects to HD=8
 * May not be as good for longer messages!
 */ 
const uint16_t crc_table[256] = {
    #include "crc_table.inc"
};

/* 
 * Initial value of 0xffff chosen 
 * If initial value is 0x0000, leading bytes with 0 value are not "seen" by CRC 
 */
const uint16_t INIT = 0xffff;

/* 
 * Calculate the CRC for a message
 * Name is chosen to match codebase elsewhere
 */
uint16_t CalculateCRC(uint8_t* message, size_t length) {
    uint16_t crc = INIT; /* Set initial value */
    uint16_t i, table_index;
    /* Following algorithm from 
     * http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html#ch5
     * Changed to C from C#, slightly nicer variable names
     */
    for (i=0; i<length; i++) {
        table_index = ((crc >> 8) ^ message[i]) & 0xff;
        crc = (uint16_t)((crc << 8) ^ crc_table[table_index]);
    }
    return crc;
}
