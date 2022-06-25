#include <boost/crc.hpp>      // for boost::crc_basic, boost::crc_optimal
#include <boost/cstdint.hpp>  // for boost::uint16_t
#include <algorithm>  // for std::for_each
#include <cassert>    // for assert
#include <cstddef>    // for std::size_t
#include <iostream>   // for std::cout
#include <ostream>    // for std::endl

int main()
{
    unsigned char const  data[] = 
    { 
        0x24, 0x04, 0x51, 0x04, 0x34, 
        0x04, 0x3e, 0x04, 0x40, 0x04,
        0x2c, 0x00, 0x20, 0x00, 0x41,
        0x04, 0x20, 0x00, 0x34, 0x04,
        0x3d, 0x04, 0x51, 0x04, 0x3c,
        0x04, 0x20, 0x00, 0x40, 0x04,
        0x3e, 0x04, 0x36, 0x04, 0x34,
        0x04, 0x35, 0x04, 0x3d, 0x04,
        0x38, 0x04, 0x4f, 0x04, 0x21, 
        0x00
    };
    //количество символов в строке
    std::size_t const data_len = sizeof(data) / sizeof(data[0]);

    // Simulate CRC-CCITT
    boost::crc_basic<64> crc_ccitt64WE(0x42f0e1eba9ea3693, 0xffffffffffffffff, 0, false, false);
    crc_ccitt64WE.process_bytes(data, data_len);
    crc_ccitt64WE.checksum();


    boost::crc_optimal<64, 0x42f0e1eba9ea3693, 0xffffffffffffffff, 0, false, false> crc;
    crc.process_bytes(data, data_len);
    crc.checksum();
    return 0;
}