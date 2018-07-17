/********************************************************************************
 *                                                                              *
 * Copyright (C) 2018 by Anakin-Marc Zaeger                                     *
 * All Rights Reserved                                                          *
 *                                                                              *
 * This file is part of RotorXor.                                               *
 *                                                                              *
 * RotorXor is free software: you can redistribute it and/or modify             *
 * it under the terms of the GNU General Public License as published by         *
 * the Free Software Foundation, either version 3 of the License, or            *
 * (at your option) any later version.                                          *
 *                                                                              *
 * RotorXor is distributed in the hope that it will be useful,                  *
 * but WITHOUT ANY WARRANTY; without even the implied warranty                  *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                *
 * GNU General Public License for more details.                                 *
 *                                                                              *
 * You should have received a copy of the GNU General Public License            *
 * along with RotorXor.  If not, see <http://www.gnu.org/licenses/>.            *
 *                                                                              *
 ********************************************************************************/
/**
 * @file
 * @author Anakin-Marc Zaeger
 *
 * @brief Source code for Pulser class.
 *
 */
#include <string>

#include "pulser.hh"

using namespace RotorXor;

/// Vector of pointers to keys in the primary keychain.
typedef std::vector< KeyFile::Key* > Keys;

/**
 * Generates a bool vector which can be used to step another scrambler.
 *
 * @param numSteps Number of rotors to step
 * @return Bool vector representing scrambler rotors to be stepped.
 */
std::vector< bool >
Pulser::pulse( const int numSteps )
{
	/**
	 * The steps are stored in a bool vector, which will be later returned
	 * to the caller.  Its intended use is for stepping a scrambler, where
	 * each element represents a rotor within said scambler.
	 */
	size_t numRotors = Scrambler::numRotors();
	std::vector< bool > outVec( numRotors );
	std::string buffer;

	/**
	 * Steps originate as random characters generated by the pulser's own
	 * scrambler.
	 */
	for ( int c = 0; c < numSteps; c++ )
	{
		buffer += genChar();
	}

	/**
	 * Then determine which rotor will be stepped by each character, setting
	 * that rotor's element in outVec to 'true'.
	 */
	for ( int c = 0; c < buffer.length(); c++ )
	{
		int charIdx = CharSet::val2pos( buffer[ c ]);
		charIdx %= numRotors;
		outVec[ charIdx ] = true;
	}

	step();				/// Finally, step the pulser's rotors.

	return outVec;
}

/**
 * Steps the rotors in the pulser's scrambler.  The pulser itself uses odometer
 * type stepping.
 */
void
Pulser::step()
{
	/// This is done by first testing notch states, then stepping the first rotor.
	std::vector< bool > notches = testNotches();
	std::vector< bool > step = { true };

	int rot = 0;

	/**
	 * Each rotor in the pulser is then conditionally tested.
	 */
	while ( rot < notches.size()		/// If the rotor being tested is valid,
		 && step[ rot ] == true		/// and if it is stepping
		 && notches[ rot++ ] == true )	/// and if it is in its notch position,
	{
		step.push_back( true );		/// then next rotor is stepped and tested.
	}

	Scrambler::step( step );
}
