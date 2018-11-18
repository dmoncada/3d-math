/// @file MathObject.h
/// @brief This header file contains the MathObject interface.
/// @author David Moncada

#pragma once

#include <cmath>
#include <iomanip>
#include <iostream>

/// @namespace Math3D
namespace Math3D {

  /// @brief The pi mathematical constant.
  const float pi = std::atanf(1.0f) * 4.0f;

  /// @brief Helper function to convert from radians to degrees.
  /// @return The input in degrees.
  inline float rad2deg(const float rad)
  {
    return 180.0f * rad / pi;
  }

  /// @brief Helper function to assert if two floats are reasonably close.
  /// @returns @c true if the inputs are within epsilon from each other, @c
  /// false otherwise.
  inline bool is_almost_equal(const float a, const float b, float e = 0.001f)
  {
    return std::fabsf(a - b) < e;
  }

  /// @class MathObject
  /// @brief Interface for mathematical objects.
  class MathObject {

  public:
    virtual ~MathObject() = default;
    virtual std::ostream& to_string(std::ostream&) const = 0;
  };

  /// @brief Override for the output stream insertion operator, for classes
  /// deriving from MathObject.
  inline std::ostream& operator<<(std::ostream& os, MathObject& obj)
  {
    return obj.to_string(os);
  }
}
