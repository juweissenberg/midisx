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
}

template<typename T> bool SysexBufferReader::read(T &value) {
    auto t_size = sizeof(T) * CHAR_BIT;
    auto sx_byte_count = t_size / SX_BYTE_SHIFT;
    T tmp = 0;
    for(auto i=sx_byte_count; i>0; i--){
        std::advance(_iterator, 1);
        if(_iterator == _buffer->end() || *_iterator == SX_FOOTER) return false;
        tmp |= (*_iterator & SX_BYTE_MASK) << ((i-1)*SX_BYTE_SHIFT);
    }
    value = tmp;
    return true;
}

template bool SysexBufferReader::read<uint8_t>(uint8_t &value);

template bool SysexBufferReader::read<uint16_t>(uint16_t &value);

}