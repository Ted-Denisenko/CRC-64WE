#include <boost/crc.hpp>      // for boost::crc_basic, boost::crc_optimal
#include <boost/cstdint.hpp>  // for boost::uint16_t
#include <cassert>    // for assert
#include <cstddef>    // for std::size_t

int main()
{

    unsigned char const  check_data[] = 
    { 
    0x31, 0x32, 0x33,
    0x34, 0x35, 0x36,
    0x37, 0x38, 0x39 
    };

    // CRC-64WE для "123456789", используется для проверки работы перевода
    boost::uint64_t const  expected = 0x62ec59e3f1a4f00a;

    // Проверка двумя способами: через crc_basic и crc_optimal
    std::size_t const check_data_len = sizeof(check_data) / sizeof(check_data[0]);
    boost::crc_basic<64> crc_check_basic(0x42f0e1eba9ea3693, 0xffffffffffffffff, 0xffffffffffffffff, false, false);
    crc_check_basic.process_bytes(check_data, check_data_len);
    assert(crc_check_basic.checksum() == expected);

    boost::crc_optimal<64, 0x42f0e1eba9ea3693, 0xffffffffffffffff, 0xffffffffffffffff, false, false> crc_check_optimal;
    crc_check_optimal.process_bytes(check_data, check_data_len);
    assert(crc_check_optimal.checksum() == expected);

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

    // Количество символов в строке
    std::size_t const data_len = sizeof(data) / sizeof(data[0]);

    // Создаем CRC-64WE
    boost::crc_basic<64> crc_ccitt64WE(0x42f0e1eba9ea3693, 0xffffffffffffffff, 0xffffffffffffffff, false, false);
    crc_ccitt64WE.process_bytes(data, data_len);
    crc_ccitt64WE.checksum();


    boost::crc_optimal<64, 0x42f0e1eba9ea3693, 0xffffffffffffffff, 0xffffffffffffffff, false, false> crc;
    crc.process_bytes(data, data_len);
    crc.checksum();
    return 0;
}