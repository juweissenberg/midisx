#include "writer.h"

#include <cstring>
#include <climits>
#include <algorithm>
#include <deque>
#include "constants.h"

namespace midisx {

SysexBufferWriter::SysexBufferWriter(): _buffer() { _buffer.push_back(SX_HEADER); }

template<typename T> bool SysexBufferWriter::write(const T &value) {
    auto t_size = sizeof(T) * CHAR_BIT;
    auto sx_byte_count = t_size / SX_BYTE_SHIFT;
    T max_value = (1 << (sx_byte_count * SX_BYTE_SHIFT)) - 1;
    auto tmp_buffer = std::deque<uint8_t>();
    T tmp = std::min(value, max_value);
    for(auto i=sx_byte_count; i>0; i--){
        tmp_buffer.push_front(static_cast<uint8_t>(tmp & SX_BYTE_MASK));
        tmp >>= SX_BYTE_SHIFT;
    }
    _buffer.insert(_buffer.end(), tmp_buffer.begin(), tmp_buffer.end());
    return true;
}

template bool SysexBufferWriter::write<uint8_t>(const uint8_t&);

template bool SysexBufferWriter::write<uint16_t>(const uint16_t&);

std::shared_ptr<const std::vector<uint8_t>> SysexBufferWriter::get() {
    _buffer.push_back(SX_FOOTER);
    return std::make_shared<const std::vector<uint8_t>>(_buffer);
}

}