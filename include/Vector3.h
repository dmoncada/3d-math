/// @file Vector3.h
/// @brief This header file contains the declaration of the Vector3 class.
/// @author David Moncada

#pragma once

#include "MathObject.h"

/// @namespace Math3D
namespace Math3D
{
    /// @class Vector3
    /// @brief The Vector3 class declaration.
    ///
    /// Basic mathematical building block used almost ubiquitously in game
    /// development. Used to describe such concepts as points in space and
    /// coordinate transforms.
    class Vector3 : public MathObject
    {
    public:
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        /// @brief Shorthand for Vector3(0, 0, 0).
        static const Vector3 zero;
        /// @brief Shorthand for Vector3(1, 1, 1).
        static const Vector3 one;
        /// @brief Shorthand for Vector3(1, 0, 0).
        static const Vector3 right;
        /// @brief Shorthand for Vector3(0, 1, 0).
        static const Vector3 up;
        /// @brief Shorthand for Vector3(0, 0, 1).
        static const Vector3 forward;
        /// @brief Shorthand for Vector3(-1, 0, 0).
        static const Vector3 left;
        /// @brief Shorthand for Vector3(0, -1, 0).
        static const Vector3 down;
        /// @brief Shorthand for Vector3(0, 0, -1).
        static const Vector3 back;

        /// @brief Computes the angle between two vectors.
        /// @return The angle between the inputs in degrees, which is in the range
        /// [0,180].
        static float angle(const Vector3& v, const Vector3& w)
        {
            return rad2deg(std::acosf(dot(v, w) / (v.magnitude() * w.magnitude())));
        }

        /// @brief Computes the cross product of two vectors.
        ///
        /// Also known as the vector product, if the inputs are parallel, either
        /// because they point in the same or in opposite directions, their cross
        /// product is zero. Otherwise, the result is a vector that is perpendicular
        /// to the plane established by the two inputs.
        ///
        /// The direction of the resulting vector is determined by the _handedness_
        /// of the underlying coordinate system.
        ///
        /// @param v The first Vector3.
        /// @param w The second Vector3.
        /// @return The Vector3 resulting from the cross product of the two inputs.
        static Vector3 cross(const Vector3& v, const Vector3& w)
        {
            return Vector3(
                v.y * w.z - v.z * w.y,
                v.z * w.x - v.x * w.z,
                v.x * w.y - v.y * w.x
            );
        }

        /// @brief Computes the distance between two points.
        /// @param v The first Vector3.
        /// @param w The second Vector3.
        /// @return The distance between the given points.
        static float distance(const Vector3& v, const Vector3& w)
        {
            return (v - w).magnitude();
        }

        /// @brief Computes the dot product of two vectors.
        ///
        /// The dot product provides a computationally cheap way to determine how
        /// much two vectors are parallel (or perpendicular) to each other.
        ///
        /// If both inputs are unit vectors, the dot product is in the range [-1,1].
        /// The dot product is positive (resp. negative) when the angle between the
        /// vectors is less (resp. greater) than 90 degrees. It attains its largest
        /// positive (resp. negative) value when both vectors are parallel and point
        /// in the same (resp. opposite) direction.
        ///
        /// @param v The first Vector3.
        /// @param w The second Vector3.
        /// @return The dot product of the two inputs.
        static float dot(const Vector3& v, const Vector3& w)
        {
            return v.x * w.x + v.y * w.y + v.z * w.z;
        }

        /// @brief Linearly interpolates between two points.
        /// @param v The first Vector3.
        /// @param w The second Vector3.
        /// @param t The interpolant parameter, clamped to [0,1].
        /// @return The fraction of the way along a line between the given points.
        static Vector3 lerp(const Vector3& v, const Vector3& w, float t)
        {
            // Clamp t to [0,1]
            t = std::fmax(t, 0.0f);
            t = std::fmin(t, 1.0f);
            return v + (w - v) * t;
        }

        /// @brief Turns an arbitrary vector into a unit vector.
        /// @param v The Vector3 to normalize.
        static Vector3& normalize(Vector3& v)
        {
            v /= v.magnitude();
            return v;
        }

        /// @brief Computes the projection of a vector onto another.
        /// @return The component of vector v that is parallel to vector w.
        static Vector3 project(const Vector3& v, const Vector3& w)
        {
            return w * (dot(v, w) * dot(w, w));
        }

        /// @brief Computes the rejection of a vector onto another.
        /// @return The component of vector v that is perpendicular to vector w.
        static Vector3 reject(const Vector3& v, const Vector3& w)
        {
            return v - project(v, w);
        }

        /// @brief Multiplies two vectors component-wise.
        /// @return The result of scaling vector v by vector w.
        static Vector3 scale(const Vector3& v, const Vector3& w)
        {
            return Vector3(v.x * w.x, v.y * w.y, v.z * w.z);
        }

        // Constructors.
        Vector3() = default;
        Vector3(const Vector3&);
        Vector3(float, float, float);

        // Member functions.
        float magnitude() const;
        Vector3 normalized() const;
        void scale(const Vector3&);
        float sqr_magnitude() const;

        // Arithmetic operators overloads.
        Vector3 operator+(const Vector3&) const;
        Vector3 operator-(const Vector3&) const;
        Vector3 operator-() const;
        Vector3 operator*(const float) const;
        Vector3 operator/(const float) const;

        // Compound assignment operators overloads.
        Vector3& operator+=(const Vector3&);
        Vector3& operator-=(const Vector3&);
        Vector3& operator*=(const float);
        Vector3& operator/=(const float);

        // Assignment operator overload.
        Vector3& operator=(const Vector3&);

        // Comparison operators overloads.
        bool operator==(const Vector3&) const;

        // to_string() overload.
        std::ostream& to_string(std::ostream& os) const override;
    };
}
