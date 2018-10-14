#include "gtest/gtest.h"
#include "MathObject.h"
#include "Vector3.h"

using Math3D::Vector3;
using Math3D::IsAlmostEqual;

namespace Vector3Tests
{
  class Vector3Test : public testing::Test
  {
  protected:
    Vector3 u;
    Vector3 v;
    Vector3 w;

    // virtual void SetUp() {}
    // virtual void TearDown() {}
  };

  TEST_F(Vector3Test, CrossProductTest)
  {
    // Assert the result is the zero vector if the inputs are parallel.

    v = Vector3(1.0f, 2.0f, 3.0f);
    w = Vector3(2.0f, 4.0f, 6.0f); // Parallel to the above.

    EXPECT_EQ(Vector3::cross(v, w), Vector3::zero())
      << "The cross product of two parallel vectors should be a zero vector.";

    // Test the result is perpendicular to the inputs if they're not parallel.

    u = Vector3::cross(v, w);
    bool result1 = IsAlmostEqual(Vector3::dot(v, u), 0.0f);
    bool result2 = IsAlmostEqual(Vector3::dot(w, u), 0.0f);

    EXPECT_TRUE(result1 && result2)
      << "The cross product of two non-parallel vectors should be "
      << "perpendicular to the inputs.";
  }

  TEST_F(Vector3Test, DotProductTest)
  {
    v = Vector3(1.0f, 2.0f, 3.0f);
    w = Vector3(0.0f, 3.0f, -2.0f); // Perpendicular to the above.

    EXPECT_TRUE(IsAlmostEqual(Vector3::dot(v, w), 0.0f))
      << "The dot product of two perpendicular vectors should be zero.";
  }

  TEST_F(Vector3Test, NormalizedVectorMagnitudeIsOne)
  {
    // Assert the magnitude of a normalized vector is one.

    v = Vector3(1.0f, 2.0f, 3.0f);
    w = Vector3::normalize(v);

    EXPECT_TRUE(IsAlmostEqual(w.magnitude(), 1.0f))
      << "The magnitude of a normalized vector should be one";
  }

  TEST_F(Vector3Test, MagSquaredIsSquareMag)
  {
    // Assert the square of the magnitude operation for a vector equals its
    // square magnitude operation.

    v = Vector3(1.0f, 2.0f, 3.0f);
    float mag_squared = std::powf(v.magnitude(), 2.0f);

    EXPECT_TRUE(IsAlmostEqual(mag_squared, v.sqr_magnitude()))
      << "Squaring Vector3::magnitude() should yield the same result as "
      << "Vector3::sqr_magnitude()";
  }
}
