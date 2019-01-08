''' Unit tests for crc16_gen '''
# Author: Chris Hemingway

import unittest
import crc16_gen

# Third party crccheck library to test our CRC algorithm against
import crccheck

class Test_gen_table(unittest.TestCase):
    def test_length(self):
        table = crc16_gen.gen_table(0xbeef)
        self.assertEqual(len(table),256)

    def test_zero(self):
        ''' For zero, we should get remainder zero'''
        for i in [0x0000, 0xdead, 0xbeef, 0xffff]:
            table = crc16_gen.gen_table(i)
            self.assertEqual(table[0],0)


class Test_output(unittest.TestCase):
    ''' Tests against a reference implementation '''
    def setUp(self):
        self.poly = crc16_gen.POLY
        self.init = crc16_gen.INIT
        self.table = crc16_gen.gen_table(self.poly)
        # Reference implementation for comparision
        self.reference_crc = crccheck.crc.Crc(width=16, poly=self.poly,
                                             initvalue=self.init)

    def test_nozero_output(self):
        ''' CRC should not be zero when all zero input '''
        message = bytearray([0x00] * 10)
        our_crc = crc16_gen.crc16(message, self.table, self.init)
        self.assertNotEqual(our_crc, 0)

    def test_known_crc(self):
        ''' Test against a known message, calculated online '''
        message = bytearray("iotwsncrctest".encode("ASCII"))
        our_crc = crc16_gen.crc16(message, self.table, self.init)
        self.assertEquals(our_crc, 0x76F5)

    def test_long_message(self):
        message = bytearray(i%256 for i in range(0,4096))
        our_crc = crc16_gen.crc16(message, self.table, self.init)
        self.reference_crc.process(message)
        there_crc = self.reference_crc.final()
        self.assertEqual(our_crc, there_crc)
        

if __name__ == '__main__':
    unittest.main()