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
 * @brief Header file for Pulser class.
 *
 */
#ifndef ROTORXOR_PULSER_HH
#define ROTORXOR_PULSER_HH

#include <vector>

#include "charSet.hh"
#include "scrambler.hh"

namespace RotorXor
{
	/**
	 * The pulser uses a scrambler to generate stepper "pulses" for another
	 * scrambler.  This pulse is in the form of a bool vector which is then
	 * passed to another scrambler via its "step" function.  The Pulser
	 * itself steps in a fashion similar to that of an odomoter, with the
	 * step position of a rotor being determined by a randomly-positioned
	 * "notch" on the rotor.
	 */
	class Pulser :
	private Scrambler
	{
	public:
		///< Default constructor.
		inline Pulser() {};

		///< Constructs a non-key pulser with numRot rotors.
		inline Pulser( int numRot ) : Scrambler( numRot ) {}

		/// Constructs a keyed pulser based on a provided keychain.
		inline Pulser( std::vector< KeyFile::Key* >& keyVec )
		: Scrambler( keyVec ) {}

		/// Generate keys for the pulser.
		/**
		 * Calls class Scrambler's genKeys function to recursively
		 * generate all necessary keys.
		 */
		inline void genKeys() { Scrambler::genKeys(); }

		/// Reset the pulser to its initial state.
		/**
		 * Calls class Scrambler's reset function to reset the pulser's
		 * character generator and rotor bank to their initial post
		 * configuration state.
		 */
		inline void reset() { Scrambler::reset(); }

		/// Generate a stepper pulse.
		std::vector< bool > pulse( const int numSteps );

		/// Sets keys for the pulser using a provided keychain fragment.
		/**
		 * Calls class Scrambler's setKey function to build its
		 * character generator and rotor bank according to the key set
		 * provided.
		 *
		 * @param keyVec A vector containing pointers keys for use in
		 * the pulser.
		 */
		inline void setKey( std::vector< KeyFile::Key* >& keyVec ) { Scrambler::setKey( keyVec ); }

		/// Gets the number of rotors in the bank.
		/**
		 * Calls, and returns the response of. the Scrambler's numRotors
		 * function.
		 *
		 * @return Integral value indicating how many rotors make up
		 * this pulser.
		 */
		inline size_t numRotors() const { return Scrambler::numRotors(); }

		/// Returns positions of pulser's rotors.
		/**
		 * Calls the Scrambler's rotPos function to recursively retrieve
		 * the positions of its rotors.
		 *
		 * @return A string representation of the positions of the
		 * rotors contained within the pulser.
		 */
		inline std::string rotPos() const { return Scrambler::rotPos(); }

		/// Steps the rotors in the pulser.
		void step();
	};
}

#endif /* ROTORXOR_PULSER_HH */
