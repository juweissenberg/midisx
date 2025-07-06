#include <iostream>
#include <vector>
#include <memory>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include "reader.h"

std::unique_ptr<midisx::SysexBufferReader> make_sysex_buffer_reader(const emscripten::val &value) {
    auto bytes = emscripten::vecFromJSArray<uint8_t>(value);
    auto bytes_ptr = std::make_shared<std::vector<uint8_t>>(bytes);
    auto reader_ptr = std::make_unique<midisx::SysexBufferReader>(bytes_ptr);
    return reader_ptr;
}

EMSCRIPTEN_BINDINGS(midisx_wasm) {
    emscripten::class_<midisx::SysexBufferReader>("SysexBufferReader")
        .constructor(&make_sysex_buffer_reader)
        .function("readU8", &midisx::SysexBufferReader::try_read<uint8_t>)
        .function("readU16", &midisx::SysexBufferReader::try_read<uint16_t>);
}

int main() {
    std::cout << "midisx wasm module loaded" << std::endl;
    return 0;
}