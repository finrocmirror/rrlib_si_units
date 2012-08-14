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
/*!\file    tProduct.h
 *
 * \author  Tobias Foehst
 *
 * \date    2010-03-15
 *
 * \brief Contains tProduct
 *
 * \b tProduct
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__si_units__include_guard__
#error Invalid include directive. Try #include "rrlib/si_unitssi_units.h" instead.
#endif

#ifndef __rrlib__si_units__operators__tProduct_h__
#define __rrlib__si_units__operators__tProduct_h__

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
class tProduct;

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
//!
/*!
 *
 */
template <
int Tleft_length, int Tleft_mass, int Tleft_time, int Tleft_electric_current, int Tleft_temperature, int Tleft_luminous_intensity, int Tleft_amount_of_substance,
    int Tright_length, int Tright_mass, int Tright_time, int Tright_electric_current, int Tright_temperature, int Tright_luminous_intensity, int Tright_amount_of_substance
    >
struct tProduct <
    tSIUnit<Tleft_length, Tleft_mass, Tleft_time, Tleft_electric_current, Tleft_temperature, Tleft_luminous_intensity, Tleft_amount_of_substance>,
    tSIUnit<Tright_length, Tright_mass, Tright_time, Tright_electric_current, Tright_temperature, Tright_luminous_intensity, Tright_amount_of_substance>
    >
{
  typedef tSIUnit<Tleft_length, Tleft_mass, Tleft_time, Tleft_electric_current, Tleft_temperature, Tleft_luminous_intensity, Tleft_amount_of_substance> tLeftUnit;
  typedef tSIUnit<Tright_length, Tright_mass, Tright_time, Tright_electric_current, Tright_temperature, Tright_luminous_intensity, Tright_amount_of_substance> tRightUnit;

public:

  typedef tSIUnit <
  tLeftUnit::cLENGTH + tRightUnit::cLENGTH,
            tLeftUnit::cMASS + tRightUnit::cMASS,
            tLeftUnit::cTIME + tRightUnit::cTIME,
            tLeftUnit::cELECTRIC_CURRENT + tRightUnit::cELECTRIC_CURRENT,
            tLeftUnit::cTEMPERATURE + tRightUnit::cTEMPERATURE,
            tLeftUnit::cLUMINOUS_INTENSITY + tRightUnit::cLUMINOUS_INTENSITY,
            tLeftUnit::cAMOUNT_OF_SUBSTANCE + tRightUnit::cAMOUNT_OF_SUBSTANCE
            > tResult;
};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
}

#endif
