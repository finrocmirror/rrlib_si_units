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
/*!\file    rrlib/si_units/tUseSymbolStreamManipulator.h
 *
 * \author  Tobias Föhst
 *
 * \date    2013-04-22
 *
 * \brief   Contains tUseSymbolStreamManipulator
 *
 * \b tUseSymbolStreamManipulator
 *
 * This class allows a user to define symbols for a specific stream like with <iomanip>
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__si_units__include_guard__
#error Invalid include directive. Try #include "rrlib/si_units/si_units.h" instead.
#endif

#ifndef __rrlib__si_units__tUseSymbolStreamManipulator_h__
#define __rrlib__si_units__tUseSymbolStreamManipulator_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/si_units/tSymbol.h"
#include "rrlib/si_units/tUserDefinedSymbolsRegistry.h"

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
 * This class allows a user to define symbols for a specific stream like with <iomanip>
 */
struct tUseSymbolStreamManipulator
{
  tSymbol symbol;
  bool only_once;
};


inline std::ostream &operator << (std::ostream &stream, const tUseSymbolStreamManipulator &manipulator)
{
  int registry_key = stream.iword(tUserDefinedSymbolsRegistry::KeyIOSIndex());
  if (registry_key == 0)
  {
    registry_key = tUserDefinedSymbols::Instance().GetNextStreamKey();
    stream.iword(tUserDefinedSymbolsRegistry::KeyIOSIndex()) = registry_key;
  }
  tUserDefinedSymbols::Instance().RegisterForStream(registry_key, manipulator.symbol, manipulator.only_once);

  return stream;
}

template <typename TUnit>
inline tUseSymbolStreamManipulator UseSymbol(const TUnit &unit, const std::string &symbol, bool persistent = true)
{
  return { tSymbol(unit, symbol), persistent };
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
