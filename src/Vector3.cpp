#include "Vector3.h"

/// @namespace Math3D
namespace Math3D
{
    /// @brief Shorthand for Vector3(0, 0, 0).
    const Vector3 Vector3::zero = Vector3(0.0f, 0.0f, 0.0f);
    /// @brief Shorthand for Vector3(1, 1, 1).
    const Vector3 Vector3::one = Vector3(1.0f, 1.0f, 1.0f);
    /// @brief Shorthand for Vector3(1, 0, 0).
    const Vector3 Vector3::right = Vector3(1.0f, 0.0f, 0.0f);
    /// @brief Shorthand for Vector3(0, 1, 0).
    const Vector3 Vector3::up = Vector3(0.0f, 1.0f, 0.0f);
    /// @brief Shorthand for Vector3(0, 0, 1).
    const Vector3 Vector3::forward = Vector3(0.0f, 0.0f, 1.0f);
    /// @brief Shorthand for Vector3(-1, 0, 0).
    const Vector3 Vector3::left = Vector3(-1.0f, 0.0f, 0.0f);
    /// @brief Shorthand for Vector3(0, -1, 0).
    const Vector3 Vector3::down = Vector3(0.0f, -1.0f, 0.0f);
    /// @brief Shorthand for Vector3(0, 0, -1).
    const Vector3 Vector3::back = Vector3(0.0f, 0.0f, -1.0f);

    /// @brief Copy constructor for Vector3.
    Vector3::Vector3(const Vector3& v) : Vector3(v.x, v.y, v.z) {}

    /// @brief Constructor for Vector3.
    Vector3::Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}

    /// @brief The magnitude of this vector.
    /// @return The length of the line segment represented by this vector.
    float Vector3::magnitude() const
    {
        return std::sqrtf(sqr_magnitude());
    }

    /// @brief Returns this vector as a unit vector.
    /// @return A Vector3 with a magnitude of one that points in the same
    /// direction as this.
    Vector3 Vector3::normalized() const
    {
        Vector3 v = *this;
        Vector3::normalize(v);
        return v;
    }

    /// @brief Multiplies every component of this vector by the same component of
    /// scale.
    /// @return The result of scaling this vector by the given vector.
    void Vector3::scale(const Vector3& scale)
    {
        x *= scale.x;
        y *= scale.y;
        z *= scale.z;
    }

    /// @brief The squared magnitude of this vector.
    ///
    /// Computing the squared magnitude of a vector is cheaper than computing its
    /// magnitude; when doing simple distance comparisons, it is usually faster to
    /// compare squared magnitudes against the squares of distances, since the
    /// comparison will yield the same result.
    ///
    /// @return The square of the magnitude of this vector.
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
        return Vector3(*this) *= -1.0f;
    }

    /// @brief Overload for the multiplication operator.
    Vector3 operator*(const float s, const Vector3& v)
    {
        return Vector3(v) *= s;
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
        return
            is_almost_equal(x, other.x) &&
            is_almost_equal(y, other.y) &&
            is_almost_equal(z, other.z);
    }

    /// @brief Overload for the to_string() member function in the base class.
    std::ostream& Vector3::to_string(std::ostream& os) const
    {
        return os << "("
            << std::setw(1) << x << ", "
            << std::setw(1) << y << ", "
            << std::setw(1) << z << ")";
    }
}
