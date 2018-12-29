/// @file Matrix3.h
/// @brief This header file contains the declaration of the Matrix3 class.
/// @author David Moncada

#pragma once

#include "MathObject.h"
#include "Vector3.h"

/// @namespace Math3D
namespace Math3D {

  /// @class Matrix3
  /// @brief The Matrix3 class declaration.
  ///
  /// Matrices represent coordinate system transformations; they are used to
  /// describe how a vector, point, line, plane, or even another transformation
  /// can be moved from one coordinate system with its own origin and set of
  /// axes to a different one.
  class Matrix3 : public MathObject {

  private:
    float m[3][3];

  public:
    /// @brief Returns the identity matrix.
    /// @return A Matrix3 with ones in its main diagonal and zeros elsewhere.
    static Matrix3 identity()
    {
      return Matrix3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    }

    /// @brief Transposes a matrix.
    /// @param mat The Matrix3 to transpose.
    static Matrix3& transpose(Matrix3& mat)
    {
      for (int i = 0; i < 3 - 1; ++i)
        for (int j = i + 1; j < 3; ++j)
          std::swap(mat.m[i][j], mat.m[j][i]);

      return mat;
    }

    // Constructors.
    Matrix3() = default;
    Matrix3(const Matrix3&);
    Matrix3(const Vector3&, const Vector3&, const Vector3&);
    Matrix3(float, float, float, float, float, float, float, float, float);

    // Member functions.
    float determinant() const;
    Matrix3 inverse() const;
    Matrix3 transposed() const;

    // () overloads.
    float& operator()(int, int);
    const float& operator()(int, int) const;

    // [] overloads.
    Vector3 operator[](int);
    const Vector3 operator[](int) const;

    // Arithmetic operators overloads.
    Matrix3 operator+(const Matrix3&) const;
    Matrix3 operator-(const Matrix3&) const;
    Matrix3 operator*(const Matrix3&) const;
    Vector3 operator*(const Vector3&) const;

    // Compound assignment operators overloads.
    Matrix3& operator+=(const Matrix3&);
    Matrix3& operator-=(const Matrix3&);

    // Assignment operator overload.
    Matrix3& operator=(const Matrix3&);

    // Comparison operators overloads.
    bool operator==(const Matrix3&) const;

    // to_string() overload.
    std::ostream& to_string(std::ostream& os) const override;
  };
}
