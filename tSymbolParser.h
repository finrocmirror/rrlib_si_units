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
/*!\file    rrlib/si_units/tSymbolParser.h
 *
 * \author  Max Reichardt
 *
 * \date    2014-11-06
 *
 * \brief   Contains tSymbolParser
 *
 * \b tSymbolParser
 *
 * Parses symbols for the SI unit provided as template parameter.
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__si_units__tSymbolParser_h__
#define __rrlib__si_units__tSymbolParser_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <sstream>

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

/*! Custom symbol for a unit (first entry is symbol string, second the factor to the base unit) */
typedef std::pair<std::string, double> tCustomSymbol;

namespace internal
{
/*!
 * Helper method for tSymbolParser specializations.
 * Defined outside templates to avoid code bloat.
 *
 * \param symbol_string String to be parsed
 * \param prefixable_base_symbol Symbol that can have prefixes (e.g. "m" for length => "ym" to "Ym" can be handled).
 * \param other_symbols Other symbols to accept (e.g. "t" for mass)
 * \param throw_exception_if_not_found Throw a std::runtime_error if symbol_string cannot be parsed
 * \return Factor to base unit
 */
double GetFactorToBaseUnit(const std::string& symbol_string, const std::string& prefixable_base_symbol, const std::vector<tCustomSymbol>& other_symbols = std::vector<tCustomSymbol>(), bool throw_exception_if_not_found = true);
}

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
//! SI Unit symbol parser
/*!
 * Parses symbols for the SI unit provided as template parameter.
 * The default implementation only accepts the default symbol of a unit.
 * For common units, there are template specializations that accept
 * the common symbols (e.g. m, dm, cm, mm, ..., ym - and up to Ym).
 */
template <typename TUnit>
struct tSymbolParser
{
  /*!
   * Check whether the provided string is a supported symbol string for this unit.
   * Throws a std::runtime_error if this is not the case.
   * Otherwise, the factor of the provided string to the base unit is returned.
   *
   * \param symbol_string String to check
   * \return Factor to base unit
   */
  static double GetFactorToBaseUnit(const std::string& symbol_string)
  {
    std::ostringstream stream;
    stream << TUnit();
    if (symbol_string == stream.str())
    {
      return 1;
    }
    throw std::runtime_error("Symbol '" + symbol_string + "' cannot be parsed. Only '" + stream.str() + "' is accepted.");
  }
};

template <>
struct tSymbolParser<tSIUnit<1, 0, 0, 0, 0, 0, 0>> // meter
{
  static double GetFactorToBaseUnit(const std::string& symbol_string)
  {
    return internal::GetFactorToBaseUnit(symbol_string, "m");
  }
};

template <>
struct tSymbolParser<tSIUnit<0, 1, 0, 0, 0, 0, 0>> // kilogram
{
  static double GetFactorToBaseUnit(const std::string& symbol_string)
  {
    return 0.001 * internal::GetFactorToBaseUnit(symbol_string, "g", { tCustomSymbol("t", 1000000) });
  }
};

template <>
struct tSymbolParser<tSIUnit<0, 0, 1, 0, 0, 0, 0>> // second
{
  static double GetFactorToBaseUnit(const std::string& symbol_string)
  {
    return internal::GetFactorToBaseUnit(symbol_string, "s", { tCustomSymbol("h", 3600) });
  }
};

template <>
struct tSymbolParser<tSIUnit<0, 0, 0, 1, 0, 0, 0>> // ampere
{
  static double GetFactorToBaseUnit(const std::string& symbol_string)
  {
    return internal::GetFactorToBaseUnit(symbol_string, "A");
  }
};

template <>
struct tSymbolParser < tSIUnit < 0, 0, -1, 0, 0, 0, 0 >> // hertz
{
  static double GetFactorToBaseUnit(const std::string& symbol_string)
  {
    return internal::GetFactorToBaseUnit(symbol_string, "Hz", { tCustomSymbol("1/s", 1) });
  }
};

template <>
struct tSymbolParser < tSIUnit < 1, 1, -2, 0, 0, 0, 0 >> // newton
{
  static double GetFactorToBaseUnit(const std::string& symbol_string)
  {
    return internal::GetFactorToBaseUnit(symbol_string, "N");
  }
};

template <>
struct tSymbolParser < tSIUnit < -1, 1, -2, 0, 0, 0, 0 >> // pascal
{
  static double GetFactorToBaseUnit(const std::string& symbol_string)
  {
    return internal::GetFactorToBaseUnit(symbol_string, "Pa");
  }
};

template <>
struct tSymbolParser < tSIUnit < 1, 0, -1, 0, 0, 0, 0 >> // velocity
{
  static double GetFactorToBaseUnit(const std::string& symbol_string)
  {
    return internal::GetFactorToBaseUnit(symbol_string, "m/s", { tCustomSymbol("km/h", 1 / 3.6) });
  }
};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
