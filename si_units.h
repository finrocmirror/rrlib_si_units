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
/*!\file    si_units.h
 *
 * \author  Tobias Foehst
 *
 * \date    2010-03-15
 *
 * \brief
 *
 * \b
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__si_units__si_units_h__
#define __rrlib__si_units__si_units_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include "rrlib/math/tAngle.h"

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#define __rrlib__si_units__include_guard__

#include "rrlib/si_units/tSIUnit.h"
#include "rrlib/si_units/tQuantity.h"
#include "rrlib/si_units/tUseSymbolStreamManipulator.h"
#include "rrlib/si_units/rtti.h"

#undef __rrlib__si_units__include_guard__

//----------------------------------------------------------------------
// Debugging
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
typedef tSIUnit<0, 0, 0, 0, 0, 0, 0> tNoUnit;

// the seven basic units
typedef tSIUnit<1, 0, 0, 0, 0, 0, 0> tMeter;
typedef tSIUnit<0, 1, 0, 0, 0, 0, 0> tKilogram;
typedef tSIUnit<0, 0, 1, 0, 0, 0, 0> tSecond;
typedef tSIUnit<0, 0, 0, 1, 0, 0, 0> tAmpere;
typedef tSIUnit<0, 0, 0, 0, 1, 0, 0> tKelvin;
typedef tSIUnit<0, 0, 0, 0, 0, 1, 0> tMole;
typedef tSIUnit<0, 0, 0, 0, 0, 0, 1> tCandela;

// the seven basic quantities
template <typename T = double> using tLength = tQuantity<tMeter, T>;
template <typename T = double> using tMass = tQuantity<tKilogram, T>;
template <typename T = double> using tTime = tQuantity<tSecond, T>;
template <typename T = double> using tElectricCurrent = tQuantity<tAmpere, T>;
template <typename T = double> using tTemperature = tQuantity<tKelvin, T>;
template <typename T = double> using tAmountOfSubstance = tQuantity<tMole, T>;
template <typename T = double> using tLuminousIntensity = tQuantity<tCandela, T>;

// some derived units
typedef tSIUnit < 0, 0, -1, 0, 0, 0, 0 > tHertz;
typedef tSIUnit < 1, 1, -2, 0, 0, 0, 0 > tNewton;
typedef tSIUnit < -1, 1, -2, 0, 0, 0, 0 > tPascal;

// some derived quantities
template <typename T = double> using tFrequency = tQuantity<tHertz, T>;
template <typename T = double> using tForce = tQuantity<tNewton, T>;
template <typename T = double> using tPressure = tQuantity<tPascal, T>;

template <typename T = double> using tVelocity = tQuantity < tSIUnit < 1, 0, -1, 0, 0, 0, 0 > , T >;
template <typename T = double> using tAcceleration = tQuantity < tSIUnit < 1, 0, -2, 0, 0, 0, 0 > , T >;

template <typename T = double, typename TAngleUnit = math::angle::Radian> using tAngularVelocity = tQuantity<tHertz, math::tAngle<T, TAngleUnit, math::angle::NoWrap>>;

//----------------------------------------------------------------------
// Const values
//----------------------------------------------------------------------
const double cYOCTO = 1E-24;
const double cZEPTO = 1E-21;
const double cATTO = 1E-18;
const double cFEMTO = 1E-15;
const double cPICO = 1E-12;
const double cNANO = 1E-9;
const double cMICRO = 1E-6;
const double cMILLI = 1E-3;
const double cCENTI = 1E-2;
const double cDECI = 1E-1;
const double cNO_PREFIX = 1.0;
const double cDECA = 1E+1;
const double cHECTO = 1E+2;
const double cKILO = 1E+3;
const double cMEGA = 1E+6;
const double cGIGA = 1E+9;
const double cTERA = 1E+12;
const double cPETA = 1E+15;
const double cEXA = 1E+18;
const double cZETTA = 1E+21;
const double cYOTTA = 1E+24;

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
