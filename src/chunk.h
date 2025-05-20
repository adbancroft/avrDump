#pragma once

#include <assert.h>
#include <stdint.h>
#include <avr/eeprom.h>
#include <avr/io.h>
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
static inline chunk_t populateChunk(uint16_t address, chunk_t c) {
  assert(c.length <= _countof(chunk_t::data));
  eeprom_read_block ((void*)c.data, (const void*)address, c.length);
  return c;
}

/** @brief Read a chunk of data starting at the given address */
static inline chunk_t readChunk(uint16_t address, uint8_t length) {
  assert(address + length <= E2END);

  return populateChunk(address, { .data = {0}, .length = length });
}