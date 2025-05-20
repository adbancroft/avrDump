#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <assert.h>
#include "utils.h"

/** @brief Structure to hold a chunk of EEPROM data */
struct chunk_t {
  char data[32U]; // EEPROM data
  uint8_t length;   // Length of the data 
};

/** @brief Populate the chunk data field by reading from the supplied EEPROM
 * 
 * @param eeprom The EEPROM to read from
 * @param address The address to start reading from
 * @param c The chunk to populate
 * @return The populated chunk
 */
static inline chunk_t populateChunk(EEPROMClass &eeprom, uint16_t address, chunk_t c) {
  assert(c.length <= _countof(chunk_t::data));

  for (uint8_t i = 0; i < c.length; i++) {
    c.data[i] = eeprom.read(address + i);
  }
  return c;
}

/** @brief Read a chunk of data starting at the given address */
static inline chunk_t readChunk(EEPROMClass &eeprom, uint16_t address, uint8_t length) {
  assert(address + length <= eeprom.length());

  return populateChunk(eeprom, address, { .data = {0}, .length = length });
}