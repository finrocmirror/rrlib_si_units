//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) Finroc GbR (finroc.org)
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
//----------------------------------------------------------------------
/*!\file    rrlib/si_units/tQuantity.h
 *
 * \author  Tobias Foehst
 *
 * \date    2010-03-15
 *
 * \brief Contains tQuantity
 *
 * \b tQuantity
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__si_units__include_guard__
#error Invalid include directive. Try #include "rrlib/si_units/si_units.h" instead.
#endif

#ifndef __rrlib__si_units__tQuantity_h__
#define __rrlib__si_units__tQuantity_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <cmath>
#include <type_traits>
#include <chrono>

#include "rrlib/math/utilities.h"

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/si_units/operators/tProduct.h"
#include "rrlib/si_units/operators/tQuotient.h"

#ifdef _LIB_RRLIB_SERIALIZATION_PRESENT_
#include "rrlib/serialization/serialization.h"
#endif

//----------------------------------------------------------------------
// Debugging
//----------------------------------------------------------------------
#include <cassert>

//----------------------------------------------------------------------
// Namespace declaration
//----------------------------------------------------------------------
namespace rrlib
{
namespace si_units
{

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------
template <typename TUnit, typename TValue = double>
class tQuantity;

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
class tQuantityBase
{};

//!
/*!
 *
 */
template <int Tlength, int Tmass, int Ttime, int Telectric_current, int Ttemperature, int Tamount_of_substance, int Tluminous_intensity, typename TValue>
class tQuantity<tSIUnit<Tlength, Tmass, Ttime, Telectric_current, Ttemperature, Tamount_of_substance, Tluminous_intensity>, TValue> : public tQuantityBase
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  typedef tSIUnit<Tlength, Tmass, Ttime, Telectric_current, Ttemperature, Tamount_of_substance, Tluminous_intensity> tUnit;
  typedef TValue tValue;

  tQuantity()
  {
    std::memset(this, 0, sizeof(tQuantity));
  }

  template < typename T, typename = typename std::enable_if < !std::is_base_of<tQuantityBase, T>::value, decltype(TValue(T())) >::type >
  tQuantity(T value)
    : value(TValue(value))
  {}

  template <typename TRep, typename TPeriod, typename = typename std::enable_if <std::is_same<tUnit, tSIUnit<0, 0, 1, 0, 0, 0, 0>>::value, TRep>::type>
  tQuantity(std::chrono::duration<TRep, TPeriod> duration)
    : value(std::chrono::nanoseconds(duration).count() * 1E-9)
  {}

  template <typename TOtherValue>
  tQuantity(tQuantity<tUnit, TOtherValue> other)
    : value(other.Value())
  {}

  template <typename TOtherValue>
  tQuantity &operator= (tQuantity<tUnit, TOtherValue> other)
  {
    this->value = other.Value();
    return *this;
  }

  template < typename T, typename = typename std::enable_if < !std::is_base_of<tQuantityBase, T>::value, decltype(T(TValue())) >::type >
  explicit inline operator T() const
  {
    return static_cast<T>(this->value);
  }

  template <typename TRep, typename TPeriod, typename = typename std::enable_if <std::is_same<tUnit, tSIUnit<0, 0, 1, 0, 0, 0, 0>>::value, TRep>::type>
  explicit inline operator std::chrono::duration<TRep, TPeriod>() const
  {
    return std::chrono::duration_cast<std::chrono::duration<TRep, TPeriod>>(std::chrono::nanoseconds(TRep(this->value * 1E+9)));
  }

  inline TValue Value() const
  {
    return this->value;
  }

  tQuantity operator += (tQuantity other)
  {
    this->value += other.value;
    return *this;
  }

  tQuantity operator -= (tQuantity other)
  {
    this->value -= other.value;
    return *this;
  }

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  TValue value;

};

//----------------------------------------------------------------------
// Unary minus
//----------------------------------------------------------------------
template <typename TUnit, typename TValue>
tQuantity<TUnit, TValue> operator - (tQuantity<TUnit, TValue> value)
{
  return tQuantity<TUnit, TValue>(-value.Value());
}

//----------------------------------------------------------------------
// Addition
//----------------------------------------------------------------------
template <typename TUnit, typename TLeftValue, typename TRightValue>
tQuantity < TUnit, decltype(TLeftValue() + TRightValue()) > operator + (tQuantity<TUnit, TLeftValue> left, tQuantity<TUnit, TRightValue> right)
{
  tQuantity < TUnit, decltype(TLeftValue() + TRightValue()) > result(left);
  result += right;
  return result;
}

template <typename TValue, typename TRep, typename TPeriod>
tQuantity<tSIUnit<0, 0, 1, 0, 0, 0, 0>, TValue> operator + (tQuantity<tSIUnit<0, 0, 1, 0, 0, 0, 0>, TValue> time, std::chrono::duration<TRep, TPeriod> duration)
{
  return time + tQuantity<tSIUnit<0, 0, 1, 0, 0, 0, 0>, TValue>(duration);
}
template <typename TValue, typename TRep, typename TPeriod>
tQuantity<tSIUnit<0, 0, 1, 0, 0, 0, 0>, TValue> operator + (std::chrono::duration<TRep, TPeriod> duration, tQuantity<tSIUnit<0, 0, 1, 0, 0, 0, 0>, TValue> time)
{
  return time + duration;
}

//----------------------------------------------------------------------
// Subtraction
//----------------------------------------------------------------------
template <typename TUnit, typename TLeftValue, typename TRightValue>
tQuantity < TUnit, decltype(TLeftValue() - TRightValue()) > operator - (tQuantity<TUnit, TLeftValue> left, tQuantity<TUnit, TRightValue> right)
{
  tQuantity < TUnit, decltype(TLeftValue() - TRightValue()) > result(left);
  result -= right;
  return result;
}

template <typename TValue, typename TRep, typename TPeriod>
tQuantity<tSIUnit<0, 0, 1, 0, 0, 0, 0>, TValue> operator - (tQuantity<tSIUnit<0, 0, 1, 0, 0, 0, 0>, TValue> time, std::chrono::duration<TRep, TPeriod> duration)
{
  return time - tQuantity<tSIUnit<0, 0, 1, 0, 0, 0, 0>, TValue>(duration);
}
template <typename TValue, typename TRep, typename TPeriod>
tQuantity<tSIUnit<0, 0, 1, 0, 0, 0, 0>, TValue> operator - (std::chrono::duration<TRep, TPeriod> duration, tQuantity<tSIUnit<0, 0, 1, 0, 0, 0, 0>, TValue> time)
{
  return tQuantity<tSIUnit<0, 0, 1, 0, 0, 0, 0>, TValue>(duration) - time;
}

//----------------------------------------------------------------------
// Multiplication
//----------------------------------------------------------------------
template <typename TLeftUnit, typename TRightUnit, typename TLeftValue, typename TRightValue>
tQuantity<typename operators::tProduct<TLeftUnit, TRightUnit>::tResult, decltype(TLeftValue() * TRightValue())> operator *(tQuantity<TLeftUnit, TLeftValue> left, tQuantity<TRightUnit, TRightValue> right)
{
  return tQuantity<typename operators::tProduct<TLeftUnit, TRightUnit>::tResult, decltype(TLeftValue() * TRightValue())>(left.Value() * right.Value());
}

template <typename TUnit, typename TValue, typename TScalar>
tQuantity<TUnit, decltype(TValue() * TScalar())> operator *(tQuantity<TUnit, TValue> quantity, TScalar scalar)
{
  return tQuantity<TUnit, decltype(TValue() * TScalar())>(quantity.Value() * scalar);
}
template <typename TUnit, typename TValue, typename TScalar>
tQuantity<TUnit, decltype(TValue() * TScalar())> operator *(TScalar scalar, tQuantity<TUnit, TValue> quantity)
{
  return quantity * scalar;
}

template <typename TUnit, typename TValue, typename TRep, typename TPeriod>
tQuantity<typename operators::tProduct<TUnit, tSIUnit<0, 0, 1, 0, 0, 0, 0>>::tResult, TValue> operator *(tQuantity<TUnit, TValue> quantity, std::chrono::duration<TRep, TPeriod> duration)
{
  return quantity * tQuantity<tSIUnit<0, 0, 1, 0, 0, 0, 0>, TValue>(duration);
}
template <typename TUnit, typename TValue, typename TRep, typename TPeriod>
tQuantity<typename operators::tProduct<TUnit, tSIUnit<0, 0, 1, 0, 0, 0, 0>>::tResult, TValue> operator *(std::chrono::duration<TRep, TPeriod> duration, tQuantity<TUnit, TValue> quantity)
{
  return quantity * duration;
}

//----------------------------------------------------------------------
// Division
//----------------------------------------------------------------------
template <typename TLeftUnit, typename TRightUnit, typename TLeftValue, typename TRightValue>
tQuantity < typename operators::tQuotient<TLeftUnit, TRightUnit>::tResult, decltype(TLeftValue() / TRightValue()) > operator / (tQuantity<TLeftUnit, TLeftValue> left, tQuantity<TRightUnit, TRightValue> right)
{
  return tQuantity < typename operators::tQuotient<TLeftUnit, TRightUnit>::tResult, decltype(TLeftValue() / TRightValue()) > (left.Value() / right.Value());
}

template <typename TUnit, typename TValue>
tQuantity < TUnit, decltype(TValue() / double()) > operator /(tQuantity<TUnit, TValue> quantity, double scalar)
{
  return quantity / tQuantity<tSIUnit<0, 0, 0, 0, 0, 0, 0>>(scalar);
}
template <typename TUnit, typename TValue>
tQuantity < typename operators::tQuotient<tSIUnit<0, 0, 0, 0, 0, 0, 0>, TUnit>::tResult, decltype(double() / TValue()) > operator /(double scalar, tQuantity<TUnit, TValue> quantity)
{
  return tQuantity<tSIUnit<0, 0, 0, 0, 0, 0, 0>>(scalar) / quantity;
}

template <typename TUnit, typename TValue, typename TRep, typename TPeriod>
tQuantity<typename operators::tQuotient<TUnit, tSIUnit<0, 0, 1, 0, 0, 0, 0>>::tResult, TValue> operator /(tQuantity<TUnit, TValue> quantity, std::chrono::duration<TRep, TPeriod> duration)
{
  return quantity / tQuantity<tSIUnit<0, 0, 1, 0, 0, 0, 0>, TValue>(duration);
}
template <typename TUnit, typename TValue, typename TRep, typename TPeriod>
tQuantity<typename operators::tQuotient<TUnit, tSIUnit<0, 0, 1, 0, 0, 0, 0>>::tResult, TValue> operator /(std::chrono::duration<TRep, TPeriod> duration, tQuantity<TUnit, TValue> quantity)
{
  return quantity / duration;
}

//----------------------------------------------------------------------
// Comparison
//----------------------------------------------------------------------
template <typename TUnit, typename TLeftValue, typename TRightValue>
const bool operator == (tQuantity<TUnit, TLeftValue> left, tQuantity<TUnit, TRightValue> right)
{
  return left.Value() == right.Value();
}

template <typename TUnit, typename TLeftValue, typename TRightValue>
const bool operator != (tQuantity<TUnit, TLeftValue> left, tQuantity<TUnit, TRightValue> right)
{
  return !(left == right);
}

template <typename TUnit, typename TLeftValue, typename TRightValue>
const bool operator < (tQuantity<TUnit, TLeftValue> left, tQuantity<TUnit, TRightValue> right)
{
  return left.Value() < right.Value();
}

template <typename TUnit, typename TLeftValue, typename TRightValue>
const bool operator > (tQuantity<TUnit, TLeftValue> left, tQuantity<TUnit, TRightValue> right)
{
  return left.Value() > right.Value();
}

template <typename TUnit, typename TLeftValue, typename TRightValue>
const bool operator <= (tQuantity<TUnit, TLeftValue> left, tQuantity<TUnit, TRightValue> right)
{
  return !(left > right);
}

template <typename TUnit, typename TLeftValue, typename TRightValue>
const bool operator >= (tQuantity<TUnit, TLeftValue> left, tQuantity<TUnit, TRightValue> right)
{
  return !(left < right);
}

template <typename TUnit, typename TLeftValue, typename TRightValue>
const bool IsEqual(tQuantity<TUnit, TLeftValue> a, tQuantity<TUnit, TRightValue> b, float max_error = 1.0E-6, math::tFloatComparisonMethod method = math::eFCM_ABSOLUTE_ERROR)
{
  return IsEqual(a.Value(), b.Value(), max_error, method);
}

//----------------------------------------------------------------------
// Streaming
//----------------------------------------------------------------------
template <typename TUnit, typename TValue>
std::ostream &operator << (std::ostream &stream, tQuantity<TUnit, TValue> quantity)
{
  stream << quantity.Value() << " " << TUnit();
  return stream;
}

#ifdef _LIB_RRLIB_SERIALIZATION_PRESENT_

template <typename TUnit, typename TValue>
inline serialization::tOutputStream& operator << (serialization::tOutputStream &stream, tQuantity<TUnit, TValue> quantity)
{
  stream << quantity.Value();
  return stream;
}

template <typename TUnit, typename TValue>
inline serialization::tInputStream& operator >> (serialization::tInputStream &stream, tQuantity<TUnit, TValue> &quantity)
{
  TValue value;
  stream >> value;
  quantity = tQuantity<TUnit, TValue>(value);
  return stream;
}

template <typename TUnit, typename TValue>
inline serialization::tStringOutputStream &operator << (serialization::tStringOutputStream &stream, tQuantity<TUnit, TValue> quantity)
{
  std::stringstream str;
  str << quantity;
  stream << str.str();
  return stream;
}

template <typename TUnit, typename TValue>
inline serialization::tStringInputStream &operator >> (serialization::tStringInputStream &stream, tQuantity<TUnit, TValue> &quantity)
{
  TValue value;
  stream.GetWrappedStringStream() >> value;
  std::string symbol_string = stream.ReadWhile("1/", serialization::tStringInputStream::cWHITESPACE | serialization::tStringInputStream::cLETTER, true);
  double factor = symbol_string.length() ? tSymbolParser<TUnit>::GetFactorToBaseUnit(symbol_string) : 1;
  quantity = tQuantity<TUnit, TValue>(static_cast<TValue>(factor * value));
  return stream;
}

#endif

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
