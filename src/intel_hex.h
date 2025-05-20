#pragma once

#include "chunk.h"

/** @brief Generate a header field for a data record (type 00) */
static inline String createHexDataRecordHeader(int address, const chunk_t &c) {
    char buff[12];
    snprintf(buff, _countof(buff)-1, ":%02X%04X00", c.length, address);
    return String(buff);
}

/** @brief Generate the End of File marker */
static inline String createHexEof(void) {
    return ":00000001FF";
}

/// @cond
// Helper function
static inline String _createHexByte(byte value) {
    char buff[4];
    snprintf(buff, _countof(buff)-1, "%02X", value);
    return String(buff);
}
/// @endcond

/** @brief Create an Intel HEX data record (type 00) */
static inline String createHexDataRecord(const chunk_t &c) {
    String record;
    for (uint8_t i = 0; i < c.length; i++) {
        record += _createHexByte(c.data[i]);
    }
    return record;
}

/** @brief Create a checksum for the given chunk at the given address */
static inline String createHexChecksum(uint16_t address, const chunk_t &c) {
    // The checksum is the 2's complement of the sum of all bytes in the record (including the header)

    // uint32_t chk = address  + c.length; // <-- This is wrong, since the address is written as 4 bytes (see createHexDataRecordHeader)

    // Sum up the header (length, address, type)
    uint32_t chk = address/256 + address%256 + c.length;
    // Sum up the data
    for (uint8_t i = 0; i < c.length; ++i) {
        chk += c.data[i];
    }
    // Two's complement
    chk = ((chk ^ 255U) + 1U) & 255;
    return _createHexByte(chk);
}
