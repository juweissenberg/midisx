#pragma once

#include <cstdint>

namespace midisx {

constexpr uint8_t SX_HEADER = 0xF0;
constexpr uint8_t SX_FOOTER = 0xF7;
constexpr uint8_t SX_BYTE_MASK = 0x7F;
constexpr uint8_t SX_BYTE_SHIFT = 7;

}