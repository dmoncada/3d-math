#include "gtest/gtest.h"
#include "MathObject.h"
#include "Matrix3.h"

using Math3D::Matrix3;
using Math3D::Vector3;
using Math3D::is_almost_equal;

namespace Matrix3Tests {

  class Matrix3Test : public testing::Test {

  protected:
    Matrix3 m, n, o;
    Vector3 v;

    // virtual void SetUp() {}
    // virtual void TearDown() {}
  };

  TEST_F(Matrix3Test, MatrixDeterminant)
  {
    m = Matrix3(1.0f, 5.0f, 3.0f, 2.0f, 4.0f, 7.0f, 4.0f, 6.0f, 2.0f);

    EXPECT_TRUE(is_almost_equal(m.determinant(), 74.0f))
      << "The computed determinant is incorrect.";
  }

  TEST_F(Matrix3Test, MatrixInverse)
  {
    m = Matrix3(1.0f, 1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    n = Matrix3(0.0f, -1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -0.5f);

    EXPECT_EQ(m.inverse(), n)
      << "The computed inverse is incorrect.";
  }

  TEST_F(Matrix3Test, MatrixTranspose)
  {
    m = Matrix3(1.0f, 5.0f, 3.0f, 2.0f, 4.0f, 7.0f, 4.0f, 6.0f, 2.0f);
    n = Matrix3(5.0f, 3.0f, 2.0f, 4.0f, 7.0f, 4.0f, 6.0f, 2.0f, 1.0f);

    EXPECT_EQ((m * n).transposed(), n.transposed() * m.transposed())
      << "The transpose of the product of two matrices should be the same as "
      << "the product of the two matrices transposed, with the order of the "
      << "factors reversed.";
  }

  TEST_F(Matrix3Test, MatrixMatrixProduct)
  {
    m = Matrix3(-32, -2.5, -6.2, -11.7, 1.6, 18.1, -0.3, 46.2, -18.6);
    n = Matrix3(-15.8, 40.9, -19.8, 11.7, 11, 38.5, -5.1, 31.7, 11.9);
    o = Matrix3(507.97, -1532.84, 463.57, 111.27, 112.84, 508.65, 640.14, -93.69, 1563.3);

    EXPECT_EQ(m * n, o)
      << "The computed Matrix-Matrix product is incorrect.";
  }

  TEST_F(Matrix3Test, MatrixVectorProduct)
  {
    m = Matrix3(1.0f, 5.0f, 3.0f, 2.0f, 4.0f, 7.0f, 4.0f, 6.0f, 2.0f);
    v = Vector3(1.0f, 2.0f, 3.0f);

    EXPECT_EQ(m * v, Vector3(20.0f, 31.0f, 22.0f))
      << "The computed Matrix-Vector product is incorrect.";
  }

  TEST_F(Matrix3Test, ProductIsIdentityIfMatricesAreInverseToOneAnother)
  {
    m = Matrix3(1.0f, 1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
    n = Matrix3(0.0f, -1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -0.5f);

    EXPECT_EQ(m * n, Matrix3::identity())
      << "When two matrices are inverse to one another, their product should "
      << "be the identity matrix.";
  }
}
