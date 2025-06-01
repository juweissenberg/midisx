#include <gtest/gtest.h>
#include <cstdint>
#include <memory>
#include <vector>
#include "validator.h"
#include "constants.h"

using namespace midisx;

class ValidBufferFixture : public testing::TestWithParam<std::vector<uint8_t>> {};

TEST_P(ValidBufferFixture, ValidSysexBuffer) {
    auto buffer = std::make_shared<std::vector<uint8_t>>(GetParam());
    auto ok = validateSysexBuffer(buffer);
    ASSERT_EQ(ok, true);
}

INSTANTIATE_TEST_SUITE_P(ValidatorTest, ValidBufferFixture,
    testing::Values(
        std::vector<uint8_t>{SX_HEADER, SX_FOOTER},
        std::vector<uint8_t>{SX_HEADER, 1, 2, SX_FOOTER},
        std::vector<uint8_t>{SX_HEADER, 127, 127, SX_FOOTER}
    )
);

class InvalidBufferFixture : public testing::TestWithParam<std::vector<uint8_t>> {};

TEST_P(InvalidBufferFixture, InvalidSysexBuffer) {
    auto buffer = std::make_shared<std::vector<uint8_t>>(GetParam());
    auto ok = validateSysexBuffer(buffer);
    ASSERT_EQ(ok, false);
}

INSTANTIATE_TEST_SUITE_P(ValidatorTest, InvalidBufferFixture,
    testing::Values(
        std::vector<uint8_t>{},
        std::vector<uint8_t>{SX_HEADER},
        std::vector<uint8_t>{SX_HEADER, 127},
        std::vector<uint8_t>{SX_FOOTER},
        std::vector<uint8_t>{127, SX_FOOTER},
        std::vector<uint8_t>{SX_FOOTER, SX_HEADER},
        std::vector<uint8_t>{SX_HEADER, 128, SX_FOOTER},
        std::vector<uint8_t>{SX_HEADER, 0, 128, SX_FOOTER},
        std::vector<uint8_t>{SX_HEADER, 128, 128, SX_FOOTER}
    )
);