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
/*!\file    tSIUnit.h
 *
 * \author  Tobias Foehst
 *
 * \date    2010-03-15
 *
 * \brief Contains tSIUnit
 *
 * \b tSIUnit
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__si_units__include_guard__
#error Invalid include directive. Try #include "rrlib/si_units/si_units.h" instead.
#endif

#ifndef __rrlib__si_units__tSIUnit_h__
#define __rrlib__si_units__tSIUnit_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include "rrlib/util/join.h"

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

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
//!
/*!
 *
 */
template <int Tlength, int Tmass, int Ttime, int Telectric_current, int Ttemperature, int Tamount_of_substance, int Tluminous_intensity>
struct tSIUnit
{
  static const int cLENGTH = Tlength;
  static const int cMASS = Tmass;
  static const int cTIME = Ttime;
  static const int cELECTRIC_CURRENT = Telectric_current;
  static const int cTEMPERATURE = Ttemperature;
  static const int cAMOUNT_OF_SUBSTANCE = Tamount_of_substance;
  static const int cLUMINOUS_INTENSITY = Tluminous_intensity;
};


void DetermineSymbolComponentsFromExponentList(std::vector<std::string> &nominator, std::vector<std::string> &denominator, int *exponents, std::ostream &stream);


template <int Tlength, int Tmass, int Ttime, int Telectric_current, int Ttemperature, int Tamount_of_substance, int Tluminous_intensity>
std::ostream &operator << (std::ostream &stream, tSIUnit<Tlength, Tmass, Ttime, Telectric_current, Ttemperature, Tamount_of_substance, Tluminous_intensity> unit)
{
  std::vector<std::string> nominator;
  std::vector<std::string> denominator;
  int exponents[7] = { Tlength, Tmass, Ttime, Telectric_current, Ttemperature, Tamount_of_substance, Tluminous_intensity };

  DetermineSymbolComponentsFromExponentList(nominator, denominator, exponents, stream);

  if (!nominator.empty())
  {
    stream << util::Join(nominator, "");
  }
  if (!denominator.empty())
  {
    stream << (nominator.empty() ? "1/" : "/");
    stream << util::Join(denominator, "");
  }

  return stream;
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
