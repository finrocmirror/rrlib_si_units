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
#include "rrlib/rtti_conversion/tStaticCastOperation.h"
#include "rrlib/rtti/tStaticTypeRegistration.h"

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

rtti::tStaticTypeRegistration init_type = rtti::tStaticTypeRegistration("rrlib_si_units").
    Add<tLength<>>("rrlib.si_units.Length", "Quantity<m, double>").
    Add<tMass<>>("rrlib.si_units.Mass", "Quantity<kg, double>").
    Add<tTime<>>("rrlib.si_units.Time", "Quantity<s, double>").
    Add<tElectricCurrent<>>("rrlib.si_units.ElectricCurrent", "Quantity<A, double>").
    Add<tTemperature<>>("rrlib.si_units.Temperature", "Quantity<K, double>").
    Add<tAmountOfSubstance<>>("rrlib.si_units.AmountOfSubstance").
    Add<tLuminousIntensity<>>("rrlib.si_units.LuminousIntensity").

    Add<tFrequency<>>("rrlib.si_units.Frequency", "Quantity<Hz, double>").
    Add<tForce<>>("rrlib.si_units.Force", "Quantity<N, double>").
    Add<tPressure<>>("rrlib.si_units.Pressure", "Quantity<Pa, double>").

    Add<tVelocity<>>("rrlib.si_units.Velocity", "Quantity<m/s, double>").
    Add<tAcceleration<>>("rrlib.si_units.Acceleration", "Quantity<m/s^2, double>").
    Add<tAngularVelocity<>>("rrlib.si_units.AngularVelocity", "Quantity<1/s, Angle>").
    Add<tAngularAcceleration<>>("rrlib.si_units.AngularAcceleration", "Quantity<1/s^2, Angle>");

auto& cTYPE_CASTS = rrlib::rtti::conversion::tStaticCastOperation::Register<rrlib::time::tDuration, rrlib::si_units::tTime<>, true>();

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

