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
/*!\file    rrlib/si_units/rtti.cpp
 *
 * \author  Tobias Föhst
 *
 * \date    2014-08-06
 *
 */
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include "rrlib/si_units/si_units.h"

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Debugging
//----------------------------------------------------------------------
#include <cassert>

//----------------------------------------------------------------------
// Namespace usage
//----------------------------------------------------------------------

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

//----------------------------------------------------------------------
// Const values
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------

static rtti::tType init_types[] =
{
  rtti::tDataType<tLength<double>>(),
  rtti::tDataType<tLength<float>>(),
  rtti::tDataType<tMass<double>>(),
  rtti::tDataType<tMass<float>>(),
  rtti::tDataType<tTime<double>>(),
  rtti::tDataType<tTime<float>>(),
  rtti::tDataType<tElectricCurrent<double>>(),
  rtti::tDataType<tElectricCurrent<float>>(),
  rtti::tDataType<tTemperature<double>>(),
  rtti::tDataType<tTemperature<float>>(),
  rtti::tDataType<tAmountOfSubstance<double>>(),
  rtti::tDataType<tAmountOfSubstance<float>>(),
  rtti::tDataType<tLuminousIntensity<double>>(),
  rtti::tDataType<tLuminousIntensity<float>>(),

  rtti::tDataType<tFrequency<double>>(),
  rtti::tDataType<tFrequency<float>>(),
  rtti::tDataType<tForce<double>>(),
  rtti::tDataType<tForce<float>>(),
  rtti::tDataType<tPressure<double>>(),
  rtti::tDataType<tPressure<float>>(),

  rtti::tDataType<tVelocity<double>>(),
  rtti::tDataType<tVelocity<float>>(),
  rtti::tDataType<tAcceleration<double>>(),
  rtti::tDataType<tAcceleration<float>>(),

  rtti::tDataType<tAngularVelocity<double, math::angle::Radian>>(),
  rtti::tDataType<tAngularVelocity<float, math::angle::Radian>>(),
  rtti::tDataType<tAngularVelocity<double, math::angle::Degree>>(),
  rtti::tDataType<tAngularVelocity<float, math::angle::Degree>>(),
};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

