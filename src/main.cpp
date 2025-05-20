/**
 * @file 
 * 
 * @brief This sketch dumps the contents of the EEPROM to the UART in Intel HEX format.
 * @see https://en.wikipedia.org/wiki/Intel_HEX
 */

#include "intel_hex.h"

static void writeIntelHexChunk(uint16_t address, const chunk_t &c) {
    Serial.print(createHexDataRecordHeader(address, c));
    Serial.print(createHexDataRecord(c));
    Serial.println(createHexChecksum(address, c));  
}

static void dumpEEpromIntelHex(EEPROMClass &eeprom) {
  constexpr uint16_t IHEX_CHUNK_SIZE = _countof(chunk_t::data);
  uint16_t i = 0U;
  for (; i < EEPROM.length()/IHEX_CHUNK_SIZE; ++i) {
    uint16_t address = i*IHEX_CHUNK_SIZE;
    writeIntelHexChunk(address, readChunk(eeprom, address, IHEX_CHUNK_SIZE));
  }
  // Just in case the last chunk isn't IHEX_CHUNK_SIZE bytes long.
  // This will happen if EEPROM.length() is not a multiple of IHEX_CHUNK_SIZE
  if (i*IHEX_CHUNK_SIZE < EEPROM.length()) {
    uint16_t address = i*IHEX_CHUNK_SIZE;
    writeIntelHexChunk(address, readChunk(eeprom, address, EEPROM.length()-address));
  }
  Serial.println(createHexEof());
}

void setup() {
  Serial.begin(9600);
  dumpEEpromIntelHex(EEPROM);
}

void loop() {
  // put your main code here, to run repeatedly:
}