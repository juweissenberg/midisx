#include <cstdint>
#include <gtest/gtest.h>
#include "writer.h"

using namespace midisx;

constexpr uint8_t T_HEADER = 0xF0;
constexpr uint8_t T_FOOTER = 0xF7;

class WriteUint8Fixture : public testing::TestWithParam<uint8_t> {};

TEST_P(WriteUint8Fixture, WriteValue) {
    auto writer = SysexBufferWriter();
    const auto value = GetParam();
    constexpr uint8_t max_value = 127;
    const auto expected = std::min(value, max_value);
    auto ok = writer.write(value);
    ASSERT_EQ(ok, true);
    auto buffer = writer.get();
    ASSERT_EQ(buffer->at(0), T_HEADER);
    ASSERT_EQ(buffer->at(1), expected);
    ASSERT_EQ(buffer->at(2), T_FOOTER);
}

INSTANTIATE_TEST_SUITE_P(WriterTest, WriteUint8Fixture,
    testing::Values(0, 1, 2, 48, 50, 100, 110, 127, 160, 255));

class WriteUint16Fixture : public testing::TestWithParam<uint16_t> {};

TEST_P(WriteUint16Fixture, WriteValue) {
    auto writer = SysexBufferWriter();
    const uint16_t value = GetParam();
    constexpr uint16_t max_value = 16383;
    const uint16_t expected = std::min(value, max_value); 
    auto ok = writer.write(value);
    ASSERT_EQ(ok, true);
    auto buffer = writer.get();
    ASSERT_EQ(buffer->at(0), T_HEADER);
    ASSERT_EQ(buffer->at(1), expected >> 7);
    ASSERT_EQ(buffer->at(2), expected & 127);
    ASSERT_EQ(buffer->at(3), T_FOOTER);
    uint16_t actual = 0;
    actual |= buffer->at(1) << 7;
    actual |= buffer->at(2);
    ASSERT_EQ(actual, expected);
}

INSTANTIATE_TEST_SUITE_P(WriterTest, WriteUint16Fixture,
    testing::Values(0, 1, 2, 100, 127, 1000, 16000, 20000, 60000, 65535));
