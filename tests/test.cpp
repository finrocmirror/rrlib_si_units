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
class TestSIUnits : public util::tUnitTestSuite
{
  RRLIB_UNIT_TESTS_BEGIN_SUITE(TestSIUnits);
  RRLIB_UNIT_TESTS_ADD_TEST(BasicOperations);
  RRLIB_UNIT_TESTS_ADD_TEST(MixedValueTypes);
  RRLIB_UNIT_TESTS_ADD_TEST(Typedefs);
  RRLIB_UNIT_TESTS_ADD_TEST(Symbols);
  RRLIB_UNIT_TESTS_ADD_TEST(Streaming);
  RRLIB_UNIT_TESTS_ADD_TEST(Conversions);
  RRLIB_UNIT_TESTS_ADD_TEST(StringDeserialization);
  RRLIB_UNIT_TESTS_END_SUITE;

private:

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

  void Streaming()
  {
    tLength<double> length;
    tForce<float> force;

    serialization::tMemoryBuffer memory_buffer;
    serialization::tOutputStream output_stream(memory_buffer);
    serialization::tInputStream input_stream(memory_buffer);

    output_stream << tLength<double>(10);
    output_stream << tForce<float>(20);
    output_stream.Flush();

    input_stream >> length;
    RRLIB_UNIT_TESTS_EQUALITY(tLength<double>(10), length);
    input_stream >> force;
    RRLIB_UNIT_TESTS_EQUALITY(tForce<float>(20), force);
  }

  void Conversions()
  {
    time::tDuration duration(std::chrono::seconds(2));
    tTime<> time(duration);
    RRLIB_UNIT_TESTS_EQUALITY(time, tTime<>(2));
    time = duration;
    RRLIB_UNIT_TESTS_EQUALITY(time, tTime<>(2));
    tVelocity<> velocity(10);
    tLength<> length = duration * velocity;
    RRLIB_UNIT_TESTS_EQUALITY(length, tLength<>(20));
    velocity = length / duration;
    RRLIB_UNIT_TESTS_EQUALITY(velocity, tVelocity<>(10));
    RRLIB_UNIT_TESTS_EQUALITY(time::tDuration(std::chrono::seconds(5)).count(), time::tDuration(tTime<>(5)).count());
    RRLIB_UNIT_TESTS_EQUALITY(tTime<>(7), time + time::tDuration(std::chrono::seconds(5)));
    RRLIB_UNIT_TESTS_EQUALITY(tTime<>(8), time::tDuration(std::chrono::seconds(6)) + time);
    RRLIB_UNIT_TESTS_EQUALITY(tTime<>(1), time - time::tDuration(std::chrono::seconds(1)));
    RRLIB_UNIT_TESTS_EQUALITY(tTime<>(3), time::tDuration(std::chrono::seconds(5)) - time);
  }

  void StringDeserialization()
  {
    {
      tLength<> length;
      serialization::tStringInputStream stream(" 5 cm ");
      stream >> length;
      RRLIB_UNIT_TESTS_EQUALITY(length, tLength<>(0.05));
    }
    {
      tFrequency<> frequency;
      serialization::tStringInputStream stream("3MHz");
      stream >> frequency;
      RRLIB_UNIT_TESTS_EQUALITY(frequency, tFrequency<>(3000000));
    }
    {
      tFrequency<> frequency;
      serialization::tStringInputStream stream(" 10 1/s");
      stream >> frequency;
      RRLIB_UNIT_TESTS_EQUALITY(frequency, tFrequency<>(10));
    }
    {
      tVelocity<> velocity;
      serialization::tStringInputStream stream("3.6 km/h");
      stream >> velocity;
      RRLIB_UNIT_TESTS_EQUALITY(velocity, tVelocity<>(1));
    }
    {
      tMass<> mass;
      serialization::tStringInputStream stream("5 t");
      stream >> mass;
      RRLIB_UNIT_TESTS_EQUALITY(mass, tMass<>(5000));
    }
    {
      tMass<> mass;
      serialization::tStringInputStream stream("  5  ");
      stream >> mass;
      RRLIB_UNIT_TESTS_EQUALITY(mass, tMass<>(5));
    }
    {
      tAcceleration<> acceleration;
      serialization::tStringInputStream stream("3 m/s^2");
      stream >> acceleration;
      RRLIB_UNIT_TESTS_EQUALITY(acceleration, tAcceleration<>(3));
    }
  }
};

RRLIB_UNIT_TESTS_REGISTER_SUITE(TestSIUnits);

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
