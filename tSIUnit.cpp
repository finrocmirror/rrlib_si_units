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
/*!\file    tSIUnit.cpp
 *
 * \author  Tobias Foehst
 *
 * \date    2013-04-22
 *
 */
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <set>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/si_units/si_units.h"

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

const std::set<tSymbol> &BasicUnitSymbols()
{
  static const std::set<tSymbol> cBASIC_UNIT_SYMBOLS
  {
    tSymbol(tMeter(), "m"),
    tSymbol(tKilogram(), "kg"),
    tSymbol(tSecond(), "s"),
    tSymbol(tAmpere(), "A"),
    tSymbol(tKelvin(), "K"),
    tSymbol(tCandela(), "cd"),
    tSymbol(tMole(), "mol")
  };
  return cBASIC_UNIT_SYMBOLS;
}

const std::set<tSymbol> &DerivedUnitSymbols()
{
  static const std::set<tSymbol> cDERIVED_UNIT_SYMBOLS
  {
    tSymbol(tNewton(), "N"),
    tSymbol(tPascal(), "Pa")
  };
  return cDERIVED_UNIT_SYMBOLS;
};

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------

namespace
{

//----------------------------------------------------------------------
// ExtractSymbolFromExponents
//----------------------------------------------------------------------
bool ExtractSymbolFromExponents(tSymbol symbol, int *exponents)
{
  for (size_t i = 0; i < cNUMBER_OF_BASIC_DIMENSIONS; ++i)
  {
    if (symbol.cEXPONENTS[i] > 0 && exponents[i] < symbol.cEXPONENTS[i])
    {
      return false;
    }
    if (symbol.cEXPONENTS[i] < 0 && exponents[i] > symbol.cEXPONENTS[i])
    {
      return false;
    }
  }

  for (size_t i = 0; i < cNUMBER_OF_BASIC_DIMENSIONS; ++i)
  {
    exponents[i] -= symbol.cEXPONENTS[i];
  }

  return true;
}

//----------------------------------------------------------------------
// ProcessSymbol
//----------------------------------------------------------------------
void ProcessSymbol(std::vector<std::string> &output, int *exponents, const tSymbol &symbol)
{
  unsigned int multiplicity = 0;
  while (ExtractSymbolFromExponents(symbol, exponents))
  {
    multiplicity++;
  }
  if (multiplicity > 0)
  {
    output.push_back(symbol.cSYMBOL);
    if (multiplicity > 1)
    {
      output.back() += "^" + std::to_string(multiplicity);
    }
  }
}

//----------------------------------------------------------------------
// FlipExponents
//----------------------------------------------------------------------
void FlipExponents(int *exponents)
{
  for (size_t i = 0; i < cNUMBER_OF_BASIC_DIMENSIONS; ++i)
  {
    exponents[i] = -exponents[i];
  }
}

//----------------------------------------------------------------------
// ExponentsAreZero
//----------------------------------------------------------------------
bool ExponentsAreZero(int *exponents)
{
  for (size_t i = 0; i < cNUMBER_OF_BASIC_DIMENSIONS; ++i)
  {
    if (exponents[i] != 0)
    {
      return false;
    }
  }
  return true;
}

}

//----------------------------------------------------------------------
// DetermineSymbolComponentsFromExponentList
//----------------------------------------------------------------------
void DetermineSymbolComponentsFromExponentList(std::vector<std::string> &nominator, std::vector<std::string> &denominator, int *exponents, std::ostream &stream)
{
  std::set<tSymbol> symbols;

  int registry_key = stream.iword(tUserDefinedSymbolsRegistry::KeyIOSIndex());
  if (registry_key != 0)
  {
    symbols.insert(tUserDefinedSymbols::Instance().TemporaryStreamSymbols(registry_key).rbegin(), tUserDefinedSymbols::Instance().TemporaryStreamSymbols(registry_key).rend());
    symbols.insert(tUserDefinedSymbols::Instance().PersistentStreamSymbols(registry_key).rbegin(), tUserDefinedSymbols::Instance().PersistentStreamSymbols(registry_key).rend());
    tUserDefinedSymbols::Instance().ClearTemporaryStreamSymbols(registry_key);
  }
  symbols.insert(tUserDefinedSymbols::Instance().GlobalSymbols().rbegin(), tUserDefinedSymbols::Instance().GlobalSymbols().rend());
  symbols.insert(DerivedUnitSymbols().begin(), DerivedUnitSymbols().end());
  symbols.insert(BasicUnitSymbols().begin(), BasicUnitSymbols().end());

  for (auto it = symbols.rbegin(); it != symbols.rend(); ++it)
  {
    ProcessSymbol(nominator, exponents, *it);
    FlipExponents(exponents);
    ProcessSymbol(denominator, exponents, *it);
    FlipExponents(exponents);
    if (ExponentsAreZero(exponents))
    {
      break;
    }
  }
  assert(ExponentsAreZero(exponents));
}


//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
