## Basic CRC-16 Table Generator and Implementation
Table generator in python, function to use it in C, and unit tests for both.

Compiles with `-Wall -std=c89 -pedantic` with no errors.


For Newcastle Uni [EEE8121](https://www.ncl.ac.uk/module-catalogue/module.php?code=EEE8121), written by Chris Hemingway.
Not that useful otherwise, much more flexible generators are available, and the default poly chosen is only good for 16 bits.

It's my first time setting up C debugging in VSCode as well, so expect some odd settings files if you choose to use them.

### Credits
* [Sunshine](http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html#ch5) for CRC tutorial, and algorithm to calculate table and values (in C#)
* Phillip Koopman's [Best CRC Polynomials](https://users.ece.cmu.edu/~koopman/crc/) guide for polynomial used.
* Scott Vokes's [Greatest](https://github.com/silentbicycle/greatest) C unit testing framework

### Requirements
* Python 3

### Test Requirements
* C compiler for C tests
* Make
* [crccheck](https://bitbucket.org/martin_scharrer/crccheck) python module for python tests
* VS Code, optional workspace/setup files provided

## Usage
### Generate table
`python crc16_gen.py > crc_table.inc`

### Build and run C tests
This will also generate the table if not done already.

`make test`

### Run python tests
(You probably don't need this if C tests pass)

`python test_crc16_gen.py`
