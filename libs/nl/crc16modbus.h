// The _bit, _byte, and _word routines return the CRC of the len bytes at mem,
// applied to the previous CRC value, crc. If mem is NULL, then the other
// arguments are ignored, and the initial CRC, i.e. the CRC of zero bytes, is
// returned. Those routines will all return the same result, differing only in
// speed and code complexity. The _rem routine returns the CRC of the remaining
// bits in the last byte, for when the number of bits in the message is not a
// multiple of eight. The low bits bits of the low byte of val are applied to
// crc. bits must be in 0..8.

#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif

// Compute the CRC a bit at a time.
// unsigned crc16modbus_bit(unsigned crc, void const *mem, size_t len);

// Compute the CRC of the low bits bits in val.
// unsigned crc16modbus_rem(unsigned crc, unsigned val, unsigned bits);

// Compute the CRC a byte at a time.
// unsigned crc16modbus_byte(unsigned crc, void const *mem, size_t len);

// Compute the CRC a word at a time.
/**
 * @return The calculated CRC
 * @param crc The previous CRC value
 * @param mem Data to be processed
 * @param len The number of bytes in mem
 * If mem is NULL, returns the appropriate initialization CRC (0xFFFF)
 *
 * Generated using crcany https://github.com/madler/crcany
 * width=16 poly=0x8005 init=0xffff refin=true refout=true xorout=0x0000
 *    check=0xb4c8 residue=0x0000 name="CRC-16/Modbus"
 */
unsigned crc16modbus_word(unsigned crc, void const *mem, size_t len);

#ifdef __cplusplus
}
#endif
