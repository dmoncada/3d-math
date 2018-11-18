#include "Matrix3.h"

/// @namespace Math3D
namespace Math3D {

  /// @brief Copy constructor for Matrix3.
  Matrix3::Matrix3(const Matrix3& other)
  {
    for (int i = 0; i < dim * dim; ++i)
      this->m[i] = other.m[i];
  }

  /// @brief Constructor for Matrix3.
  Matrix3::Matrix3(float m00, float m01, float m02,
                   float m10, float m11, float m12,
                   float m20, float m21, float m22)
    : m { m00, m01, m02, m10, m11, m12, m20, m21, m22 } {}

  /// @brief Constructor for Matrix3.
  Matrix3::Matrix3(const Vector3& u, const Vector3& v, const Vector3& w)
    : m { u.x, v.x, w.x, u.y, v.y, w.y, u.z, v.z, w.z } {}

  // TODO: add doc.
  float Matrix3::determinant() const
  {
    return (*this)(0, 0) * ((*this)(1, 1) * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 1)) +
           (*this)(0, 1) * ((*this)(1, 2) * (*this)(2, 0) - (*this)(1, 0) * (*this)(2, 2)) +
           (*this)(0, 2) * ((*this)(1, 0) * (*this)(2, 1) - (*this)(1, 1) * (*this)(2, 0));
  }

  // TODO: add doc.
  Matrix3 Matrix3::inverse() const
  {
    const Vector3 a = (*this)[0];
    const Vector3 b = (*this)[1];
    const Vector3 c = (*this)[2];

    Vector3 u = Vector3::cross(b, c);
    Vector3 v = Vector3::cross(c, a);
    Vector3 w = Vector3::cross(a, b);

    // TODO: Throw if the dot product of w and c is zero.
    float invdet = 1.0f / Vector3::dot(w, c);

    return Matrix3(
      u.x * invdet, u.y * invdet, u.z * invdet,
      v.x * invdet, v.y * invdet, v.z * invdet,
      w.x * invdet, w.y * invdet, w.z * invdet
    );
  }

  /// @brief Turns a matrix into its transpose.
  /// @param m The Matrix3 to transpose.

  /// @brief Returns the transpose of this matrix.
  /// @return The transpose of this matrix as a new Matrix3.
  Matrix3 Matrix3::transposed() const
  {
    Matrix3 m = *this;
    Matrix3::transpose(m);
    return m;
  }

  /// @brief Overload for the parenthesis operator.
  float& Matrix3::operator()(int row, int col)
  {
    // TODO: Throw if either row or col is out of bounds.
    return m[dim * row + col];
  }

  /// @brief Overload for the parenthesis operator.
  const float& Matrix3::operator()(int row, int col) const
  {
    // TODO: Throw if either row or col is out of bounds.
    return m[dim * row + col];
  }

  /// @brief Overload for the brackets operator.
  Vector3 Matrix3::operator[](int col)
  {
    return Vector3((*this)(0, col), (*this)(1, col), (*this)(2, col));
  }

  /// @brief Overload for the brackets operator.
  const Vector3 Matrix3::operator[](int col) const
  {
    return Vector3((*this)(0, col), (*this)(1, col), (*this)(2, col));
  }

  /// @brief Overload for the addition operator.
  Matrix3 Matrix3::operator+(const Matrix3& other) const
  {
    return Matrix3(*this) += other;
  }

  /// @brief Overload for the subtraction operator.
  Matrix3 Matrix3::operator-(const Matrix3& other) const
  {
    return Matrix3(*this) -= other;
  }

  /// @brief Overload for the multiplication operator.
  Matrix3 Matrix3::operator*(const Matrix3& other) const
  {
    return Matrix3(
      (*this)(0, 0) * other(0, 0) + (*this)(0, 1) * other(1, 0) + (*this)(0, 2) * other(2, 0),
      (*this)(0, 0) * other(0, 1) + (*this)(0, 1) * other(1, 1) + (*this)(0, 2) * other(2, 1),
      (*this)(0, 0) * other(0, 2) + (*this)(0, 1) * other(1, 2) + (*this)(0, 2) * other(2, 2),
      (*this)(1, 0) * other(0, 0) + (*this)(1, 1) * other(1, 0) + (*this)(1, 2) * other(2, 0),
      (*this)(1, 0) * other(0, 1) + (*this)(1, 1) * other(1, 1) + (*this)(1, 2) * other(2, 1),
      (*this)(1, 0) * other(0, 2) + (*this)(1, 1) * other(1, 2) + (*this)(1, 2) * other(2, 2),
      (*this)(2, 0) * other(0, 0) + (*this)(2, 1) * other(1, 0) + (*this)(2, 2) * other(2, 0),
      (*this)(2, 0) * other(0, 1) + (*this)(2, 1) * other(1, 1) + (*this)(2, 2) * other(2, 1),
      (*this)(2, 0) * other(0, 2) + (*this)(2, 1) * other(1, 2) + (*this)(2, 2) * other(2, 2)
    );
  }

  /// @brief Overload for the multiplication operator.
  Vector3 Matrix3::operator*(const Vector3& v) const
  {
    return Vector3(
      (*this)(0, 0) * v.x + (*this)(0, 1) * v.y + (*this)(0, 2) * v.z,
      (*this)(1, 0) * v.x + (*this)(1, 1) * v.y + (*this)(1, 2) * v.z,
      (*this)(2, 0) * v.x + (*this)(2, 1) * v.y + (*this)(2, 2) * v.z
    );
  }

  /// @brief Overload for the addition-assignment operator.
  Matrix3& Matrix3::operator+=(const Matrix3& other)
  {
    for (int i = 0; i < dim * dim; ++i)
      this->m[i] += other.m[i];

    return *this;
  }

  /// @brief Overload for the subtraction-assignment operator.
  Matrix3& Matrix3::operator-=(const Matrix3& other)
  {
    for (int i = 0; i < dim * dim; ++i)
      this->m[i] -= other.m[i];

    return *this;
  }

  /// @brief Overload for the assignment operator.
  Matrix3& Matrix3::operator=(const Matrix3& other)
  {
    if (this != &other)
      for (int i = 0; i < dim * dim; ++i)
        this->m[i] = other.m[i];

    return *this;
  }

  /// @brief Overload for the equality comparison operator.
  bool Matrix3::operator==(const Matrix3& other) const
  {
    for (int row = 0; row < dim; ++row)
      for (int col = 0; col < dim; ++col)
        if (!is_almost_equal((*this)(row, col), other(row, col)))
          return false;

    return true;
  }

  /// @brief Overload for the to_string() member function in the base class.
  std::ostream& Matrix3::to_string(std::ostream& os) const
  {
    for (int row = 0; row < dim; ++row)
    {
      os << '|';

      for (int col = 0; col < dim; ++col)
        os << ' ' << std::fixed << std::setw(3) << (*this)(row, col);

      os << " |" << std::endl;
    }

    return os;
  }
}
