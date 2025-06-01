#pragma once

#include <cstdint>
#include <memory>
#include <vector>

namespace midisx {

class SysexBufferWriter {
public:
    SysexBufferWriter();
    template<typename T> bool write(const T &value);
    std::shared_ptr<const std::vector<uint8_t>> get();
private:
    std::vector<uint8_t> _buffer;
};

}