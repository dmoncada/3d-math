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

  /// @brief The determinant of this matrix.
  ///
  /// The determinant can be thought of as a sort of magnitude for the matrix.
  /// It can be positive of negative depending on the orientation of the set of
  /// vectors consisting of the n rows (or columns) of the matrix.
  ///
  /// The determinant is computed using _expansion by minors_, where _minor_ is
  /// the determinant of a submatrix that excludes a row and a column.
  ///
  /// @return The determinant of this matrix.
  float Matrix3::determinant() const
  {
    return (*this)(0, 0) * ((*this)(1, 1) * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 1)) +
           (*this)(0, 1) * ((*this)(1, 2) * (*this)(2, 0) - (*this)(1, 0) * (*this)(2, 2)) +
           (*this)(0, 2) * ((*this)(1, 0) * (*this)(2, 1) - (*this)(1, 1) * (*this)(2, 0));
  }

  /// @brief The inverse of this matrix.
  ///
  /// The inverse is found using _Gauss-Jordan elimination_, in which elementary
  /// row operations are successively applied to the matrix until it is
  /// transformed into the identity matrix. A matrix has an inverse if and only
  /// if its determinant is not zero.
  ///
  /// @return The inverse of this matrix as a new Matrix3.
  Matrix3 Matrix3::inverse() const
  {
    const Vector3 a = (*this)[0];
    const Vector3 b = (*this)[1];
    const Vector3 c = (*this)[2];

    Vector3 u = Vector3::cross(b, c);
    Vector3 v = Vector3::cross(c, a);
    Vector3 w = Vector3::cross(a, b);

    float det = Vector3::dot(w, c);

    if (is_almost_equal(det, 0.0f, 0.000001))
    {
      throw "The determinant of the matrix is zero.";
    }

    u /= det;
    v /= det;
    w /= det;

    return Matrix3(u.x, u.y, u.z, v.x, v.y, v.z, w.x, w.y, w.z);
  }

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
    if (row < 0.0f || row > dim || col < 0.0f || col > dim)
    {
      throw std::out_of_range("Index out of range.");
    }

    return m[dim * row + col];
  }

  /// @brief Overload for the parenthesis operator.
  const float& Matrix3::operator()(int row, int col) const
  {
    if (row < 0.0f || row > dim || col < 0.0f || col > dim)
    {
      throw std::out_of_range("Index out of range.");
    }

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
