#include "gtest/gtest.h"
#include "MathObject.h"
#include "Vector3.h"

namespace Math3D
{
    namespace Math3DTests
    {
        class Vector3Test : public testing::Test
        {
        protected:
            Vector3 u, v, w;

            // virtual void SetUp() {}
            // virtual void TearDown() {}
        };

        TEST_F(Vector3Test, CrossProductIsZeroIfVectorsAreParallel)
        {
            v = Vector3(1.0f, 2.0f, 3.0f);
            w = Vector3(2.0f, 4.0f, 6.0f); // Parallel to the above.

            EXPECT_EQ(Vector3::cross(v, w), Vector3::zero)
                << "The cross product of two parallel vectors should be a zero vector.";
        }

        TEST_F(Vector3Test, DotProductIsPositiveIfAngleIsBelowNinety)
        {
            v = Vector3(1.0f, 2.0f, 3.0f);
            w = Vector3(3.0f, 1.0f, 2.0f);

            EXPECT_TRUE(Vector3::angle(v, w) < 90.0f && Vector3::dot(v, w) > 0.0f)
                << "When the angle between two vectors is less that ninety, the dot "
                << "product should be positive.";
        }

        TEST_F(Vector3Test, DotProductIsNegativeIfAngleIsAboveNinety)
        {
            v = Vector3(1.0f, 2.0f, 3.0f);
            w = Vector3(-2.0f, -1.0f, -3.0f);

            EXPECT_TRUE(Vector3::angle(v, w) > 90.0f && Vector3::dot(v, w) < 0.0f)
                << "When the angle between two vectors is greater that ninety, the dot "
                << "product should be negative.";
        }

        TEST_F(Vector3Test, DotProductIsZeroIfVectorsArePerpendicular)
        {
            v = Vector3(1.0f, 2.0f, 3.0f);
            w = Vector3(0.0f, 3.0f, -2.0f); // Perpendicular to the above.

            EXPECT_TRUE(is_almost_equal(Vector3::dot(v, w), 0.0f))
                << "The dot product of two perpendicular vectors should be zero.";
        }

        TEST_F(Vector3Test, NormalizedVectorMagnitudeIsOne)
        {
            v = Vector3(1.0f, 2.0f, 3.0f);

            EXPECT_TRUE(is_almost_equal(v.normalized().magnitude(), 1.0f))
                << "The magnitude of a normalized vector should be one";
        }

        TEST_F(Vector3Test, MagSquaredIsSquareMag)
        {
            v = Vector3(1.0f, 2.0f, 3.0f);
            float mag_squared = std::powf(v.magnitude(), 2.0f);

            EXPECT_TRUE(is_almost_equal(mag_squared, v.sqr_magnitude()))
                << "Squaring Vector3::magnitude() should yield the same result as "
                << "Vector3::sqr_magnitude()";
        }
    }
}
