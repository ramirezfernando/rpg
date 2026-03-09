#include "math.h"  // NOLINT(modernize-deprecated-headers)

#include <gtest/gtest.h>

#include "graphics/sprite.h"

namespace Math {

TEST(GetRandomInt, ReturnsWithinRange) {
  // Try several times since it's random.
  const int iterations = 100;
  for (int i = 0; i < iterations; ++i) {
    const int result = GetRandomInt(/*min=*/5, /*max=*/10);
    EXPECT_GE(result, 5);
    EXPECT_LE(result, 10);
  }
}

struct RowMajorOrderTestParams {
  int row;
  int column;
  int expected_index;
};

class GetRowMajorOrderIndexTest
    : public ::testing::TestWithParam<RowMajorOrderTestParams> {};

TEST_P(GetRowMajorOrderIndexTest, ReturnsCorrectIndex) {
  const auto& params = GetParam();
  EXPECT_EQ(GetRowMajorOrderIndex(params.row, params.column),
            params.expected_index);
}

INSTANTIATE_TEST_SUITE_P(MathTests, GetRowMajorOrderIndexTest,
                         ::testing::Values(RowMajorOrderTestParams{0, 0, 0},
                                           RowMajorOrderTestParams{0, 15, 15},
                                           RowMajorOrderTestParams{2, 3, 35},
                                           RowMajorOrderTestParams{15, 0,
                                                                   240}));

struct CoordinateTestParams {
  int x_pos;
  int y_pos;
  int expected_index;
};

class GetRowMajorOrderIndexFromCoordinatesTest
    : public ::testing::TestWithParam<CoordinateTestParams> {};

TEST_P(GetRowMajorOrderIndexFromCoordinatesTest, ReturnsCorrectIndex) {
  const auto& params = GetParam();
  const Sprite::Coordinate coordinate{.x_pos = params.x_pos,
                                      .y_pos = params.y_pos};
  EXPECT_EQ(GetRowMajorOrderIndexFromCoordinates(coordinate),
            params.expected_index);
}

// Map columns = 16. Sprite width = 16, Scale = 3 -> Tile size = 48.
INSTANTIATE_TEST_SUITE_P(
    MathTests, GetRowMajorOrderIndexFromCoordinatesTest,
    ::testing::Values(
        CoordinateTestParams{0, 0, 0},
        CoordinateTestParams{5, 5, 0},       // Should floor to 0.
        CoordinateTestParams{48, 48, 17},    // Row 1, Col 1 -> 1 * 16 + 1.
        CoordinateTestParams{100, 200, 66},  // Row 4, Col 2 -> 4 * 16 + 2.
        CoordinateTestParams{500, 700, 234}  // Row 14, Col 10 -> 14 * 16 + 10.
        ));

}  // namespace Math
