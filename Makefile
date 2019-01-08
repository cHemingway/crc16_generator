CFLAGS=-Wall -g -ansi -pedantic

ifeq ($(OS),Windows_NT)
    RM = del
else
    RM = rm -f
endif

test_crc.exe: test_crc.c crc.c crc.h crc_table.inc
		gcc test_crc.c crc.c $(CFLAGS) -o test_crc.exe

crc_table.inc: crc16_gen.py
		python3 crc16_gen.py > crc_table.inc

test: test_crc.exe
	./test_crc.exe

.PHONY : clean
clean:
	$(RM) test_crc.exe crc_table.inc