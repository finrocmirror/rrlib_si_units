//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) AG Robotersysteme TU Kaiserslautern
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
#error Invalid include directive. Try #include "rrlib/si_unitssi_units.h" instead.
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

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  double value;

};



template <typename TUnit>
const tQuantity<TUnit> operator + (tQuantity<TUnit> left, tQuantity<TUnit> right)
{
  return tQuantity<TUnit>(left.Value() + right.Value());
}

template <typename TUnit>
const tQuantity<TUnit> operator - (tQuantity<TUnit> left, tQuantity<TUnit> right)
{
  return tQuantity<TUnit>(left.Value() - right.Value());
}

template <typename TLeftUnit, typename TRightUnit>
const tQuantity<typename operators::tProduct<TLeftUnit, TRightUnit>::tResult> operator *(tQuantity<TLeftUnit> left, tQuantity<TRightUnit> right)
{
  return tQuantity<typename operators::tProduct<TLeftUnit, TRightUnit>::tResult>(left.Value() * right.Value());
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

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
