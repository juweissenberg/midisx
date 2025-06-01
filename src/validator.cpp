#include "validator.h"

#include "constants.h"

namespace midisx {

bool validateSysexBuffer(const std::shared_ptr<std::vector<uint8_t>> &buffer) {
    if(buffer->size()<2) return false;
    auto iter = buffer->begin();
    if(*iter != SX_HEADER) return false;
    iter++;
    while(iter != --buffer->end()) {
        if(*iter >> 7) return false;
        iter++;
    }
    if(*iter != SX_FOOTER) return false;
    return true;
}

}