//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) AG Robotersysteme TU Kaiserslautern
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
#error Invalid include directive. Try #include "rrlib/si_unitssi_units.h" instead.
#endif

#ifndef __rrlib__si_units__tSIUnit_h__
#define __rrlib__si_units__tSIUnit_h__

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
template <int Tlength, int Tmass, int Ttime, int Telectric_current, int Ttemperature, int Tluminous_intensity, int Tamount_of_substance>
struct tSIUnit
{
  static const int cLENGTH = Tlength;
  static const int cMASS = Tmass;
  static const int cTIME = Ttime;
  static const int cELECTRIC_CURRENT = Telectric_current;
  static const int cTEMPERATURE = Ttemperature;
  static const int cLUMINOUS_INTENSITY = Tluminous_intensity;
  static const int cAMOUNT_OF_SUBSTANCE = Tamount_of_substance;
};

namespace
{

template <int Tlength, int Tmass, int Ttime, int Telectric_current, int Ttemperature, int Tluminous_intensity, int Tamount_of_substance>
inline void WriteInterpretedExponentsToStream(std::ostream &stream)
{
  if (Tlength > 0)
  {
    stream << "m" << (Tlength == 2 ? "²" : Tlength == 3 ? "³" : "");
    if (Tlength > 3)
    {
      stream << "^" << Tlength;
    }
  }
  if (Tmass > 0)
  {
    stream << "kg" << (Tmass == 2 ? "²" : Tmass == 3 ? "³" : "");
    if (Tmass > 3)
    {
      stream << "^" << Tmass;
    }
  }
  if (Ttime > 0)
  {
    stream << "s" << (Ttime == 2 ? "²" : Ttime == 3 ? "³" : "");
    if (Ttime > 3)
    {
      stream << "^" << Ttime;
    }
  }
  if (Telectric_current > 0)
  {
    stream << "A" << (Telectric_current == 2 ? "²" : Telectric_current == 3 ? "³" : "");
    if (Telectric_current > 3)
    {
      stream << "^" << Telectric_current;
    }
  }
  if (Ttemperature > 0)
  {
    stream << "K" << (Ttemperature == 2 ? "²" : Ttemperature == 3 ? "³" : "");
    if (Ttemperature > 3)
    {
      stream << "^" << Ttemperature;
    }
  }
  if (Tluminous_intensity > 0)
  {
    stream << "cd" << (Tluminous_intensity == 2 ? "²" : Tluminous_intensity == 3 ? "³" : "");
    if (Tluminous_intensity > 3)
    {
      stream << "^" << Tluminous_intensity;
    }
  }
  if (Tamount_of_substance > 0)
  {
    stream << "mol" << (Tamount_of_substance == 2 ? "²" : Tamount_of_substance == 3 ? "³" : "");
    if (Tamount_of_substance > 3)
    {
      stream << "^" << Tamount_of_substance;
    }
  }
}

}

template <typename TUnit>
inline bool WriteDerivedUnitToStream(std::ostream &stream, TUnit)
{
  return false;
}

template <int Tlength, int Tmass, int Ttime, int Telectric_current, int Ttemperature, int Tluminous_intensity, int Tamount_of_substance>
std::ostream &operator << (std::ostream &stream, tSIUnit<Tlength, Tmass, Ttime, Telectric_current, Ttemperature, Tluminous_intensity, Tamount_of_substance> unit)
{
  if (!WriteDerivedUnitToStream(stream, tSIUnit<Tlength, Tmass, Ttime, Telectric_current, Ttemperature, Tluminous_intensity, Tamount_of_substance>()))
  {
    bool nominator = Tlength > 0 || Tmass > 0 || Ttime > 0 || Telectric_current > 0 || Ttemperature > 0 || Tluminous_intensity > 0 || Tamount_of_substance > 0;
    bool denominator = Tlength < 0 || Tmass < 0 || Ttime < 0 || Telectric_current < 0 || Ttemperature < 0 || Tluminous_intensity < 0 || Tamount_of_substance < 0;

    if (nominator)
    {
      WriteInterpretedExponentsToStream<Tlength, Tmass, Ttime, Telectric_current, Ttemperature, Tluminous_intensity, Tamount_of_substance>(stream);
    }
    if (denominator)
    {
      stream << (!nominator ? "1/" : "/");
      WriteInterpretedExponentsToStream < -Tlength, -Tmass, -Ttime, -Telectric_current, -Ttemperature, -Tluminous_intensity, -Tamount_of_substance > (stream);
    }
  }

  return stream;
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
