//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) Finroc GbR (finroc.org)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//----------------------------------------------------------------------
/*!\file    tQuantity.h
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
template <typename TUnit>
struct tQuantity;

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
//!
/*!
 *
 */
template <int Tlength, int Tmass, int Ttime, int Telectric_current, int Ttemperature, int Tamount_of_substance, int Tluminous_intensity>
class tQuantity<tSIUnit<Tlength, Tmass, Ttime, Telectric_current, Ttemperature, Tamount_of_substance, Tluminous_intensity>>
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  typedef tSIUnit<Tlength, Tmass, Ttime, Telectric_current, Ttemperature, Tamount_of_substance, Tluminous_intensity> tUnit;

  tQuantity() : value(0) {};

  tQuantity(double value)
    : value(value)
  {
    assert(!isnan(this->value) && !isinf(this->value));
  };

  inline double Value() const
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

  double value;

};


//----------------------------------------------------------------------
// Addition
//----------------------------------------------------------------------
template <typename TUnit>
const tQuantity<TUnit> operator + (tQuantity<TUnit> left, tQuantity<TUnit> right)
{
  tQuantity<TUnit> result(left);
  result += right;
  return result;
}

//----------------------------------------------------------------------
// Subtraction
//----------------------------------------------------------------------
template <typename TUnit>
const tQuantity<TUnit> operator - (tQuantity<TUnit> left, tQuantity<TUnit> right)
{
  tQuantity<TUnit> result(left);
  result -= right;
  return result;
}

//----------------------------------------------------------------------
// Multiplication
//----------------------------------------------------------------------
template <typename TLeftUnit, typename TRightUnit>
const tQuantity<typename operators::tProduct<TLeftUnit, TRightUnit>::tResult> operator *(tQuantity<TLeftUnit> left, tQuantity<TRightUnit> right)
{
  return tQuantity<typename operators::tProduct<TLeftUnit, TRightUnit>::tResult>(left.Value() * right.Value());
}

template <typename TUnit>
const tQuantity<TUnit> operator *(tQuantity<TUnit> quantity, double scalar)
{
  return tQuantity<TUnit>(quantity.Value() * scalar);
}
template <typename TUnit>
const tQuantity<TUnit> operator *(double scalar, tQuantity<TUnit> quantity)
{
  return quantity * scalar;
}

//----------------------------------------------------------------------
// Division
//----------------------------------------------------------------------
template <typename TLeftUnit, typename TRightUnit>
const tQuantity<typename operators::tQuotient<TLeftUnit, TRightUnit>::tResult> operator / (tQuantity<TLeftUnit> left, tQuantity<TRightUnit> right)
{
  return tQuantity<typename operators::tQuotient<TLeftUnit, TRightUnit>::tResult>(left.Value() / right.Value());
}

template <typename TUnit>
const tQuantity<TUnit> operator /(tQuantity<TUnit> quantity, double scalar)
{
  return quantity / tQuantity<tSIUnit<0, 0, 0, 0, 0, 0, 0>>(scalar);
}
template <typename TUnit>
const tQuantity<typename operators::tQuotient<tSIUnit<0, 0, 0, 0, 0, 0, 0>, TUnit>::tResult> operator /(double scalar, tQuantity<TUnit> quantity)
{
  return tQuantity<tSIUnit<0, 0, 0, 0, 0, 0, 0>>(scalar) / quantity;
}

//----------------------------------------------------------------------
// Comparison
//----------------------------------------------------------------------
template <typename TUnit>
const bool operator == (tQuantity<TUnit> left, tQuantity<TUnit> right)
{
  return left.Value() == right.Value();
}

template <typename TUnit>
const bool operator != (tQuantity<TUnit> left, tQuantity<TUnit> right)
{
  return !(left == right);
}

template <typename TUnit>
const bool operator < (tQuantity<TUnit> left, tQuantity<TUnit> right)
{
  return left.Value() < right.Value();
}

template <typename TUnit>
const bool operator > (tQuantity<TUnit> left, tQuantity<TUnit> right)
{
  return left.Value() > right.Value();
}

template <typename TUnit>
const bool operator <= (tQuantity<TUnit> left, tQuantity<TUnit> right)
{
  return !(left > right);
}

template <typename TUnit>
const bool operator >= (tQuantity<TUnit> left, tQuantity<TUnit> right)
{
  return !(left < right);
}

template <typename TUnit>
const bool IsEqual(tQuantity<TUnit> a, tQuantity<TUnit> b, float max_error = 1.0E-6, math::tFloatComparisonMethod method = math::eFCM_ABSOLUTE_ERROR)
{
  return IsEqual(a.Value(), b.Value(), max_error, method);
}

//----------------------------------------------------------------------
// Streaming
//----------------------------------------------------------------------
template <typename TUnit>
std::ostream &operator << (std::ostream &stream, tQuantity<TUnit> quantity)
{
  stream << quantity.Value() << " " << TUnit();
  return stream;
}

#ifdef _LIB_RRLIB_SERIALIZATION_PRESENT_

template <typename TUnit>
inline serialization::tOutputStream& operator << (serialization::tOutputStream &stream, tQuantity<TUnit> quantity)
{
  stream << quantity.Value();
  return stream;
}

template <typename TUnit>
inline serialization::tInputStream& operator >> (serialization::tInputStream &stream, tQuantity<TUnit> &quantity)
{
  double value;
  stream >> value;
  quantity = tQuantity<TUnit>(value);
  return stream;
}

template <typename TUnit>
inline serialization::tStringOutputStream &operator << (serialization::tStringOutputStream &stream, tQuantity<TUnit> quantity)
{
  std::stringstream str;
  str << quantity;
  stream << str.str();
  return stream;
}

template <typename TUnit>
inline serialization::tStringInputStream &operator >> (serialization::tStringInputStream &stream, tQuantity<TUnit> &quantity)
{
  RRLIB_LOG_PRINT(ERROR, "De-Serializing from strings not (yet) supported");
  throw std::exception();
  return stream;
}

#endif


//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
