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
/*!\file    rrlib/si_units/tSymbolParser.cpp
 *
 * \author  Max Reichardt
 *
 * \date    2014-11-06
 *
 */
//----------------------------------------------------------------------
#include "rrlib/si_units/si_units.h"

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include "rrlib/util/string.h"

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
namespace internal
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

double GetFactorToBaseUnit(const std::string& symbol_string, const std::string& prefixable_base_symbol, const std::vector<tCustomSymbol>& other_symbols, bool throw_exception_if_not_found)
{
  if (symbol_string == prefixable_base_symbol)
  {
    return 1;
  }
  if (util::EndsWith(symbol_string, prefixable_base_symbol))
  {
    if (symbol_string.length() == prefixable_base_symbol.length() + 1)
    {
      char prefix = symbol_string[0];
      switch (prefix)
      {
      case 'y':
        return cYOCTO;
      case 'z':
        return cZEPTO;
      case 'a':
        return cATTO;
      case 'f':
        return cFEMTO;
      case 'p':
        return cPICO;
      case 'n':
        return cNANO;
        //case 'µ': return cMICRO;
      case 'm':
        return cMILLI;
      case 'c':
        return cCENTI;
      case 'd':
        return cDECI;
      case 'D':
        return cDECA;
      case 'h':
        return cHECTO;
      case 'k':
        return cKILO;
      case 'M':
        return cMEGA;
      case 'G':
        return cGIGA;
      case 'T':
        return cTERA;
      case 'P':
        return cPETA;
      case 'E':
        return cEXA;
      case 'Z':
        return cZETTA;
      case 'Y':
        return cYOTTA;
      default:
        throw std::runtime_error("Error parsing symbol: Unknown prefix in '" + symbol_string + "'");
      }
    }
    else if (symbol_string == ("mc" + prefixable_base_symbol) || symbol_string == ("µ" + prefixable_base_symbol))
    {
      return cMICRO;
    }
  }
  for (const tCustomSymbol & other_symbol : other_symbols)
  {
    if (other_symbol.first == symbol_string)
    {
      return other_symbol.second;
    }
  }
  throw std::runtime_error("Symbol '" + symbol_string + "' cannot be parsed. Try '" + prefixable_base_symbol + "' (possibly with prefixes).");
}


//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
}
