#include <cstdint>
#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "reader.h"

using namespace midisx;

constexpr uint8_t T_HEADER = 0xF0;
constexpr uint8_t T_FOOTER = 0xF7;

class ReadUint8Fixture : public testing::TestWithParam<uint8_t> {};

TEST_P(ReadUint8Fixture, ReadValue) {
    auto expected = GetParam();
    ASSERT_LE(expected , 127);
    auto buffer = std::make_shared<std::vector<uint8_t>>();
    buffer->push_back(T_HEADER);
    buffer->push_back(expected);
    buffer->push_back(T_FOOTER);
    auto reader = SysexBufferReader(buffer);
    uint8_t actual = expected == 0 ? 1 : 0;
    auto ok = reader.read(actual);
    ASSERT_EQ(ok, true);
    ASSERT_EQ(actual, expected);
    // test that reading beyond the buffer is well handled
    for(auto i = 0; i<10; i++) {
        uint8_t shouldnt_be_mutated = 0;
        auto should_be_false = reader.read(shouldnt_be_mutated);
        ASSERT_EQ(should_be_false, false);
        ASSERT_EQ(shouldnt_be_mutated, 0);
    }
}

INSTANTIATE_TEST_SUITE_P(ReaderTest, ReadUint8Fixture,
    testing::Values(0, 1, 2, 4, 50, 99, 110, 127));

class ReadUint16Fixture : public testing::TestWithParam<uint16_t> {};

TEST_P(ReadUint16Fixture, ReadValue) {
    auto expected = GetParam();
    ASSERT_LE(expected , 16383);
    auto buffer = std::make_shared<std::vector<uint8_t>>();
    buffer->push_back(T_HEADER);
    buffer->push_back((expected >> 7) & 0x7F);
    buffer->push_back(expected & 0x7F);
    buffer->push_back(T_FOOTER);
    auto reader = SysexBufferReader(buffer);
    uint16_t actual = expected == 0 ? 1 : 0;
    auto ok = reader.read(actual);
    ASSERT_EQ(ok, true);
    ASSERT_EQ(actual, expected);
    // test that reading beyond the buffer is well handled
    for(auto i = 0; i<10; i++) {
        uint16_t shouldnt_be_mutated = 0;
        auto should_be_false = reader.read(shouldnt_be_mutated);
        ASSERT_EQ(should_be_false, false);
        ASSERT_EQ(shouldnt_be_mutated, 0);
    }
}

INSTANTIATE_TEST_SUITE_P(ReaderTest, ReadUint16Fixture,
    testing::Values(0, 1, 2, 99, 127, 130, 1000, 16000));
