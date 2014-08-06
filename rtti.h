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
/*!\file    rrlib/si_units/rtti.h
 *
 * \author  Tobias Föhst
 *
 * \date    2014-08-06
 *
 * Register names of SI Quantities for RTTI
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__si_units__include_guard__
#error Invalid include directive. Try #include "rrlib/si_units/si_units.h" instead.
#endif

#ifndef __rrlib__si_units__rtti_h__
#define __rrlib__si_units__rtti_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <sstream>

#include "rrlib/rtti/rtti.h"

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Namespace declaration
//----------------------------------------------------------------------
namespace rrlib
{
namespace rtti
{

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Function declarations
//----------------------------------------------------------------------

template <typename TUnit, typename TValue>
struct TypeName<si_units::tQuantity<TUnit, TValue>>
{
  /*!
   * \return Type name to use in rrlib_rttti for type T
   */
  static std::string Get()
  {
    std::stringstream str;
    str << "tQuantity<" << TUnit() << ", " << TypeName<TValue>::Get() << ">";
    return str.str();
  }
};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
