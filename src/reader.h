#pragma once

#include <cstdint>
#include <memory>
#include <vector>

namespace midisx {

class SysexBufferReader {
public:
    SysexBufferReader(const std::shared_ptr<std::vector<uint8_t>> &buffer);
    template<typename T> [[nodiscard]] bool read(T &value) noexcept;
    template<typename T> T try_read();

private:
    std::shared_ptr<const std::vector<uint8_t>> _buffer;
    std::vector<uint8_t>::const_iterator _iterator;
};

}