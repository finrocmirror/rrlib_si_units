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
/*!\file    rrlib/si_units/tSymbol.h
 *
 * \author  Tobias Föhst
 *
 * \date    2013-04-18
 *
 * \brief   Contains tSymbol
 *
 * \b tSymbol
 *
 * This class implements the mapping between a (derived) SI unit and its symbol
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__si_units__include_guard__
#error Invalid include directive. Try #include "rrlib/si_units/si_units.h" instead.
#endif

#ifndef __rrlib__si_units__tSymbol_h__
#define __rrlib__si_units__tSymbol_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Internal includes with ""
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
//! SHORT_DESCRIPTION
/*!
 * This class implements the mapping between a (derived) SI unit and its symbol
 */
class tSymbol
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  std::string cSYMBOL;
  const int cEXPONENTS[7];

  template <typename TUnit>
  tSymbol(TUnit unit, const std::string &symbol) :
    cSYMBOL(symbol),
    cEXPONENTS {TUnit::cLENGTH, TUnit::cMASS, TUnit::cTIME, TUnit::cELECTRIC_CURRENT, TUnit::cTEMPERATURE, TUnit::cAMOUNT_OF_SUBSTANCE, TUnit::cLUMINOUS_INTENSITY}
  {}

};

inline bool operator == (const tSymbol &left, const tSymbol &right)
{
  for (size_t i = 0; i < 7; ++i)
  {
    if (left.cEXPONENTS[i] != right.cEXPONENTS[i])
    {
      return false;
    }
  }
  return left.cSYMBOL == right.cSYMBOL;
}

inline bool operator < (const tSymbol &left, const tSymbol &right)
{
  int left_exponents = 0;
  int right_exponents = 0;
  for (size_t i = 0; i < 7; ++i)
  {
    left_exponents += abs(left.cEXPONENTS[i]);
    right_exponents += abs(right.cEXPONENTS[i]);
  }
  if (left_exponents != right_exponents)
  {
    return left_exponents < right_exponents;
  }

  for (size_t i = 0; i < 7; ++i)
  {
    if (abs(left.cEXPONENTS[i]) != abs(right.cEXPONENTS[i]))
    {
      return abs(left.cEXPONENTS[i]) < abs(right.cEXPONENTS[i]);
    }
  }

  return false;
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
