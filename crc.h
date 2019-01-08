/* 
 * File:   crc.h
 * Author: Chris Hemingway - B8062339
 * POLY = 0x8fdb, INIT = 0xffff, non reversed, no final XOR
 * Created on 27 November 2018, 10:17
 */

#ifndef CRC_H
#define	CRC_H


#include <stdint.h>
#include <stddef.h>

/*****************function to Calculate CRC************************/
uint16_t CalculateCRC(uint8_t* message, size_t length);


#endif	/* CRC_H */
