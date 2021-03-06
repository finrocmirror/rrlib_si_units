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
/*!\file    rrlib/si_units/operators/tQuotient.h
 *
 * \author  Tobias Foehst
 *
 * \date    2010-03-15
 *
 * \brief Contains tQuotient
 *
 * \b tQuotient
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__si_units__include_guard__
#error Invalid include directive. Try #include "rrlib/si_units/si_units.h" instead.
#endif

#ifndef __rrlib__si_units__operators__tQuotient_h__
#define __rrlib__si_units__operators__tQuotient_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------

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
namespace operators
{

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------
template <typename TLeftUnit, typename TRightUnit>
class tQuotient;

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
//!
/*!
 *
 */
template <
int Tleft_length, int Tleft_mass, int Tleft_time, int Tleft_electric_current, int Tleft_temperature, int Tleft_amount_of_substance, int Tleft_luminous_intensity,
    int Tright_length, int Tright_mass, int Tright_time, int Tright_electric_current, int Tright_temperature, int Tright_amount_of_substance, int Tright_luminous_intensity
    >
class tQuotient <
  tSIUnit<Tleft_length, Tleft_mass, Tleft_time, Tleft_electric_current, Tleft_temperature, Tleft_amount_of_substance, Tleft_luminous_intensity>,
  tSIUnit<Tright_length, Tright_mass, Tright_time, Tright_electric_current, Tright_temperature, Tright_amount_of_substance, Tright_luminous_intensity>
  >
{
  typedef tSIUnit<Tleft_length, Tleft_mass, Tleft_time, Tleft_electric_current, Tleft_temperature, Tleft_amount_of_substance, Tleft_luminous_intensity> tLeftUnit;
  typedef tSIUnit<Tright_length, Tright_mass, Tright_time, Tright_electric_current, Tright_temperature, Tright_amount_of_substance, Tright_luminous_intensity> tRightUnit;

public:

  typedef tSIUnit <
  tLeftUnit::cLENGTH - tRightUnit::cLENGTH,
            tLeftUnit::cMASS - tRightUnit::cMASS,
            tLeftUnit::cTIME - tRightUnit::cTIME,
            tLeftUnit::cELECTRIC_CURRENT - tRightUnit::cELECTRIC_CURRENT,
            tLeftUnit::cTEMPERATURE - tRightUnit::cTEMPERATURE,
            tLeftUnit::cAMOUNT_OF_SUBSTANCE - tRightUnit::cAMOUNT_OF_SUBSTANCE,
            tLeftUnit::cLUMINOUS_INTENSITY - tRightUnit::cLUMINOUS_INTENSITY
            > tResult;
};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
}

#endif
