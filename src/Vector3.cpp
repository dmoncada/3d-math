#include "Vector3.h"

namespace Math3D
{
  /// @brief Copy constructor for Vector3.
  Vector3::Vector3(const Vector3& v) : Vector3(v.x, v.y, v.z) {}

  /// @brief Constructor for Vector3.
  Vector3::Vector3(float x, float y, float z) : x {x}, y {y}, z {z} {}

  /// @brief The magnitude of the vector.
  /// @return The length of the line segment represented by the vector.
  float Vector3::magnitude() const
  {
    return std::sqrtf(sqr_magnitude());
  }

  /// @brief The squared magnitude of the vector.
  ///
  /// Computing the squared magnitude of a vector is cheaper than computing its
  /// magnitude; when doing simple distance comparisons, it is usually faster to
  /// compare squared magnitudes against the squares of distances, since the
  /// comparison will yield the same result.
  ///
  /// @return The square of the magnitude of the vector.
  float Vector3::sqr_magnitude() const
  {
    return x * x + y * y + z * z;
  }

  /// @brief Overload for the addition operator.
  Vector3 Vector3::operator+(const Vector3& other) const
  {
    return Vector3(*this) += other;
  }

  /// @brief Overload for the subtraction operator.
  Vector3 Vector3::operator-(const Vector3& other) const
  {
    return Vector3(*this) -= other;
  }

  /// @brief Overload for the unary negation operator.
  Vector3 Vector3::operator-() const
  {
    return Vector3(-x, -y, -z);
  }

  /// @brief Overload for the multiplication operator.
  Vector3 Vector3::operator*(const float s) const
  {
    return Vector3(*this) *= s;
  }

  /// @brief Overload for the division operator.
  Vector3 Vector3::operator/(const float s) const
  {
    return Vector3(*this) /= s;
  }

  /// @brief Overload for the addition-assignment operator.
  Vector3& Vector3::operator+=(const Vector3& other)
  {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  /// @brief Overload for the subtraction-assignment operator.
  Vector3& Vector3::operator-=(const Vector3& other)
  {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }

  /// @brief Overload for the multiplication-assignment operator.
  Vector3& Vector3::operator*=(const float s)
  {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }

  /// @brief Overload for the division-assignment operator.
  Vector3& Vector3::operator/=(const float s)
  {
    float t = 1.0f / s;
    x *= t;
    y *= t;
    z *= t;
    return *this;
  }

  /// @brief Overload for the assignment operator.
  Vector3& Vector3::operator=(const Vector3& other)
  {
    if (this != &other)
    {
      this->x = other.x;
      this->y = other.y;
      this->z = other.z;
    }
    return *this;
  }

  /// @brief Overload for the equality comparison operator.
  bool Vector3::operator==(const Vector3& other) const
  {
    return IsAlmostEqual(x, other.x) &&
           IsAlmostEqual(y, other.y) &&
           IsAlmostEqual(z, other.z);
  }

  /// @brief Overload for the stream insertion operator.
  std::ostream& operator<<(std::ostream& os, const Vector3& v)
  {
    return v.to_string(os);
  }
}
