''' Program to generate a CRC-16 lookup table '''

# Author: Chris Hemingway

# This polynomial is from Koopman, see https://users.ece.cmu.edu/~koopman/crc/
# Best CRC-16 for up to 15 bytes, gives Hamming Distance of 8 (for random noise)
POLY = 0x8fdb 
# Initialisation value, non zero avoids missing leading zeros
INIT = 0xffff 

# Table generation method from http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html#ch5

import argparse
import textwrap

def gen_table(poly: int):
    ''' Generate a CRC table for the given 16 bit polynomial'''
    table = [0] * 256
    for i in range(256):
        byte = (i << 8) & 0xffff # Move value into MSB
        for _ in range(8): # Calculate CRC for this byte
            if ((byte & 0x8000) != 0): # Test for CRC, 16 bit   
                byte <<= 1 # Move the CRC along
                byte ^= poly    #   XOR in the polynomial (our divisor)
            else:
                byte <<= 1 # Move the CRC along
                
        table[i] = (byte & 0xffff)
    return table


def crc16(bytes: bytearray, crc16_table, initial_value):
    crc = initial_value # Initial value
    for b in bytes:
        # XOR byte into MSB of _current_ CRC
        # Table index is that , >> 8, mod 256
        table_index = ((crc ^ (b << 8)) >> 8) & 0xff
        # Shift along the CRC by one byte
        crc = crc << 8
        # Find the remainder from the lookup table
        remainder = crc16_table[table_index]
        # XOR the remainder with the CRC
        crc = (crc ^ remainder) & 0xffff
    return crc

def table_to_hex(crc16_table):
    # Convert to hex, and put on lines, wrapping to 80 chars
    vals = ", ".join("0x{:04X}".format(i) for i in crc16_table)
    return textwrap.fill(vals)

if __name__ == "__main__":
    # Parse command line arguments, most are default
    parser=argparse.ArgumentParser(description='Generate a CRC16 table')
    parser.add_argument("--poly", type=int, default=POLY,
                        help="16 bit polynomial",)
    args = parser.parse_args()

    # Output the table directly
    table = gen_table(args.poly)
    print(table_to_hex(table))