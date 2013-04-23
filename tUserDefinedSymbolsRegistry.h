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
/*!\file    rrlib/si_units/tUserDefinedSymbolsRegistry.h
 *
 * \author  Tobias Föhst
 *
 * \date    2013-04-22
 *
 * \brief   Contains tUserDefinedSymbolsRegistry
 *
 * \b tUserDefinedSymbolsRegistry
 *
 * This class allows a user to define symbols for specific units and manages their lifetime
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__si_units__include_guard__
#error Invalid include directive. Try #include "rrlib/si_units/si_units.h" instead.
#endif

#ifndef __rrlib__si_units__tUserDefinedSymbolsRegistry_h__
#define __rrlib__si_units__tUserDefinedSymbolsRegistry_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <list>
#include <ios>

#include "rrlib/design_patterns/singleton.h"

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/si_units/tSymbol.h"

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
class tUserDefinedSymbolsRegistry;
typedef design_patterns::tSingletonHolder<tUserDefinedSymbolsRegistry> tUserDefinedSymbols;

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
//! SHORT_DESCRIPTION
/*!
 * This class allows a user to define symbols for specific units and manages their lifetime
 */
class tUserDefinedSymbolsRegistry
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  static int KeyIOSIndex()
  {
    static int index = std::ios_base::xalloc();
    return index;
  }

  tUserDefinedSymbolsRegistry()
  {}

  inline void Register(const tSymbol &symbol)
  {
    this->global_symbols.push_back(symbol);
  }

  inline void Unregister(const tSymbol &symbol)
  {
    this->global_symbols.remove(symbol);
  }

  inline const std::list<tSymbol> &GlobalSymbols() const
  {
    return this->global_symbols;
  }

  inline int GetNextStreamKey()
  {
    this->persistent_stream_symbols.push_back(std::list<tSymbol>());
    this->temporary_stream_symbols.push_back(std::list<tSymbol>());
    assert(this->persistent_stream_symbols.size() == this->temporary_stream_symbols.size());
    return this->persistent_stream_symbols.size();
  }

  void RegisterForStream(int key, const tSymbol &symbol, bool persistent = true)
  {
    assert(0 < key && static_cast<size_t>(key) <= this->persistent_stream_symbols.size());
    (persistent ? this->persistent_stream_symbols : this->temporary_stream_symbols)[key - 1].push_back(symbol);
  }

  inline const std::list<tSymbol> &PersistentStreamSymbols(int key) const
  {
    assert(0 < key && static_cast<size_t>(key) <= this->persistent_stream_symbols.size());
    return this->persistent_stream_symbols[key - 1];
  }

  inline const std::list<tSymbol> &TemporaryStreamSymbols(int key) const
  {
    assert(0 < key && static_cast<size_t>(key) <= this->persistent_stream_symbols.size());
    return this->temporary_stream_symbols[key - 1];
  }

  inline void ClearTemporaryStreamSymbols(int key)
  {
    assert(0 < key && static_cast<size_t>(key) <= this->persistent_stream_symbols.size());
    this->temporary_stream_symbols[key - 1].clear();
  }

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  std::list<tSymbol> global_symbols;
  std::vector<std::list<tSymbol>> persistent_stream_symbols;
  std::vector<std::list<tSymbol>> temporary_stream_symbols;

};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
