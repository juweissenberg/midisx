#pragma once

#include <cstdint>
#include <memory>
#include <vector>

namespace midisx {

bool validateSysexBuffer(const std::shared_ptr<std::vector<uint8_t>> &buffer);

}
