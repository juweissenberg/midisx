#include "reader.h"

#include <stdexcept>
#include <climits>
#include "constants.h"
#include "validator.h"

namespace midisx {

SysexBufferReader::SysexBufferReader(
    const std::shared_ptr<std::vector<uint8_t>> &buffer
): _buffer(buffer), _iterator(_buffer->begin()) {
    auto ok = validateSysexBuffer(buffer);
    if(!ok) throw std::invalid_argument("cannot read invalid sysex buffer.");
    std::advance(_iterator, 1);
}

template<typename T> [[nodiscard]] bool SysexBufferReader::read(T &value) noexcept {
    auto t_size = sizeof(T) * CHAR_BIT;
    auto sx_byte_count = t_size / SX_BYTE_SHIFT;
    T tmp = 0;
    while(sx_byte_count>0 && *_iterator != SX_FOOTER){
        tmp |= (*_iterator & SX_BYTE_MASK) << ((sx_byte_count-1)*SX_BYTE_SHIFT);
        sx_byte_count--;
        std::advance(_iterator, 1);
    }
    if(sx_byte_count>0) { return false; }
    value = tmp;
    return true;
}

template bool SysexBufferReader::read<uint8_t>(uint8_t &value) noexcept;

template bool SysexBufferReader::read<uint16_t>(uint16_t &value) noexcept;

}