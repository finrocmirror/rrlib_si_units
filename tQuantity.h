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
template <int Tlength, int Tmass, int Ttime, int Telectric_current, int Ttemperature, int Tluminous_intensity, int Tamount_of_substance>
class tQuantity<tSIUnit<Tlength, Tmass, Ttime, Telectric_current, Ttemperature, Tluminous_intensity, Tamount_of_substance>>
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  typedef tSIUnit<Tlength, Tmass, Ttime, Telectric_current, Ttemperature, Tluminous_intensity, Tamount_of_substance> tUnit;

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

  operator double() const
  {
    return this->Value();
  }

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  double value;

};



template <typename TUnit>
const tQuantity<TUnit> operator + (tQuantity<TUnit> left, tQuantity<TUnit> right)
{
  tQuantity<TUnit> result(left);
  result += right;
  return result;
}

template <typename TUnit>
const tQuantity<TUnit> operator - (tQuantity<TUnit> left, tQuantity<TUnit> right)
{
  tQuantity<TUnit> result(left);
  result -= right;
  return result;
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

template <typename TLeftUnit, typename TRightUnit>
const tQuantity<typename operators::tQuotient<TLeftUnit, TRightUnit>::tResult> operator / (tQuantity<TLeftUnit> left, tQuantity<TRightUnit> right)
{
  return tQuantity<typename operators::tQuotient<TLeftUnit, TRightUnit>::tResult>(left.Value() / right.Value());
}

template <typename TUnit>
std::ostream &operator << (std::ostream &stream, tQuantity<TUnit> quantity)
{
  stream << quantity.Value() << " " << TUnit();
  return stream;
}


#ifdef _LIB_RRLIB_SERIALIZATION_PRESENT_

template <typename TUnit>
inline rrlib::serialization::tOutputStream& operator << (rrlib::serialization::tOutputStream& stream, const tQuantity<TUnit>& o)
{
  stream << o.Value();
  return stream;
}

template <typename TUnit>
inline rrlib::serialization::tInputStream& operator >> (rrlib::serialization::tInputStream& stream, tQuantity<TUnit>& o)
{
  double value;
  stream >> value;
  o = tQuantity<TUnit>(value);
  return stream;
}

template <typename TUnit>
inline rrlib::serialization::tStringOutputStream& operator << (rrlib::serialization::tStringOutputStream& stream, const tQuantity<TUnit>& o)
{
  std::stringstream str;
  str << o;
  stream << str.str();
  return stream;
}

template <typename TUnit>
inline rrlib::serialization::tStringInputStream& operator >> (rrlib::serialization::tStringInputStream& stream, tQuantity<TUnit>& o)
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
