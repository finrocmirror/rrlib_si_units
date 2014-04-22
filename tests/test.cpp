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
/*!\file    rrlib/si_units/tests/test.cpp
 *
 * \author  Tobias Foehst
 *
 * \date    2010-03-15
 *
 */
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include "rrlib/util/tUnitTestSuite.h"

#include <type_traits>

#include "rrlib/si_units/si_units.h"

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

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Const values
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------
class tTestSIUnits : public util::tUnitTestSuite
{
  RRLIB_UNIT_TESTS_BEGIN_SUITE(tTestSIUnits);
  RRLIB_UNIT_TESTS_ADD_TEST(BasicOperations);
  RRLIB_UNIT_TESTS_ADD_TEST(MixedValueTypes);
  RRLIB_UNIT_TESTS_ADD_TEST(Typedefs);
  RRLIB_UNIT_TESTS_ADD_TEST(Symbols);
  RRLIB_UNIT_TESTS_END_SUITE;

private:

  virtual void InitializeTests()
  {}

  virtual void CleanUp()
  {}

  void BasicOperations()
  {
    tQuantity<tSIUnit<1, 0, 0, 0, 0, 0, 0>> length = 10.0;
    RRLIB_UNIT_TESTS_EQUALITY(10.0, length.Value());
    tQuantity<tSIUnit<0, 0, 1, 0, 0, 0, 0>> time = 2.0;
    RRLIB_UNIT_TESTS_EQUALITY(2.0, time.Value());

    RRLIB_UNIT_TESTS_ASSERT((std::is_same < decltype(length / time), tQuantity < tSIUnit < 1, 0, -1, 0, 0, 0, 0 >>>::value));
    RRLIB_UNIT_TESTS_EQUALITY((tQuantity < tSIUnit < 1, 0, -1, 0, 0, 0, 0 >> (5.0)), length / time);

    tVelocity<> velocity = length / time;
    RRLIB_UNIT_TESTS_EQUALITY(tVelocity<>(2.5), 0.5 * velocity);
    RRLIB_UNIT_TESTS_EQUALITY(0.5 * velocity, velocity * 0.5);
  }

  void MixedValueTypes()
  {
    tQuantity<tSIUnit<1, 0, 0, 0, 0, 0, 0>> length = 10.0;
    tQuantity<tSIUnit<0, 0, 1, 0, 0, 0, 0>, float> time = 2.0;
    RRLIB_UNIT_TESTS_ASSERT((std::is_same < decltype(length / time), tQuantity < tSIUnit < 1, 0, -1, 0, 0, 0, 0 >>>::value));
    RRLIB_UNIT_TESTS_EQUALITY((tQuantity < tSIUnit < 1, 0, -1, 0, 0, 0, 0 >> (5.0)), length / time);

    tVelocity<> velocity = length / time;
    RRLIB_UNIT_TESTS_EQUALITY(tVelocity<>(2.5), 0.5 * velocity);
    RRLIB_UNIT_TESTS_EQUALITY(0.5 * velocity, velocity * 0.5);
  }

  void Typedefs()
  {
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tSIUnit<1, 0, 0, 0, 0, 0, 0>, tMeter>::value));
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tSIUnit<0, 1, 0, 0, 0, 0, 0>, tKilogram>::value));
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tSIUnit<0, 0, 1, 0, 0, 0, 0>, tSecond>::value));
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tSIUnit<0, 0, 0, 1, 0, 0, 0>, tAmpere>::value));
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tSIUnit<0, 0, 0, 0, 1, 0, 0>, tKelvin>::value));
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tSIUnit<0, 0, 0, 0, 0, 1, 0>, tMole>::value));
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tSIUnit<0, 0, 0, 0, 0, 0, 1>, tCandela>::value));
  }

  void Symbols()
  {
    std::stringstream stream;
    stream << tVelocity<>();
    RRLIB_UNIT_TESTS_EQUALITY(std::string("0 m/s"), stream.str());

    stream.str("");
    stream << tFrequency<>();
    RRLIB_UNIT_TESTS_EQUALITY(std::string("0 1/s"), stream.str());

    stream.str("");
    stream << UseSymbol(tHertz(), "Hz", false) << tFrequency<>() << tFrequency<>();
    RRLIB_UNIT_TESTS_EQUALITY(std::string("0 Hz0 1/s"), stream.str());

    stream.str("");
    stream << UseSymbol(tHertz(), "Hz") << tFrequency<>() << tFrequency<>();
    RRLIB_UNIT_TESTS_EQUALITY(std::string("0 Hz0 Hz"), stream.str());

    stream.str("");
    stream << tLength<>(1) / tLength<>(1) / tLength<>(1) / tLength<>(1) / tLength<>(1) / tLength<>(1) * tTemperature<>(1);
    RRLIB_UNIT_TESTS_EQUALITY(std::string("1 K/m^4"), stream.str());

    stream.str("");
    stream << tForce<>(1) * tLength<>(1);
    RRLIB_UNIT_TESTS_EQUALITY(std::string("1 Nm"), stream.str());

    stream.str("");
    stream << 1 / (tForce<>(1) * tLength<>(1));
    RRLIB_UNIT_TESTS_EQUALITY(std::string("1 1/Nm"), stream.str());
  }
};

RRLIB_UNIT_TESTS_REGISTER_SUITE(tTestSIUnits);

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}