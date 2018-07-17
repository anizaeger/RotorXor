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
 * @brief Header file for Scrambler class.
 *
 */
#ifndef ROTORXOR_SCRAMBLER_HH
#define ROTORXOR_SCRAMBLER_HH

#include "charGen.hh"
#include "rotorBank.hh"

#include "../includes/keyfile.hh"

#include <string>
#include <vector>

namespace RotorXor
{
	/// Random character scrambler.
	/**
	 * The Scrambler generates a random character, then passes it through a RotorBank
	 * for further scrambling before returning it.
	 *
	 */
	class Scrambler :
		private Generator,
		private RotorBank
	{
	public:
		/// Default constructor.
		Scrambler()
		{
			
		}

		/// Constructor which accepts a number of rotors to create.
		Scrambler( int numRot ) : RotorBank( numRot )
		{
			
		}

		/// Constructor which creates scrambler based on a provided key.
		Scrambler( std::vector< KeyFile::Key* >& keyVec )
		{
			setKey( keyVec );
		}

		/// Deallocate gen and bank before destroying Scrambler.
		~Scrambler()
		{
			
		}

		/// Automatically create a new keychain for an existing scrambler.
		inline void genKeys() {
			RotorBank::genKeys();
			Generator::genKey();
		}

		void setKey( std::vector< KeyFile::Key* >& );			///< Configure the scrambler based on a provided key.

		/// Reset the scrambler to its initial state.
		inline void reset() {
			Generator::reset();
			RotorBank::reset();
		}

		char genChar();							///< Generate a random character.

		/// Returns the number of rotors in the scrambler.
		inline int numRotors() const { return RotorBank::numRotors(); }

		/// Returns a bool vector indicating whether each rotor is at its notch position.
		inline std::vector< bool > testNotches() const { return RotorBank::testNotches(); }

		/// Increments the rotors' positions.
		inline void step( const std::vector< bool >& stepVec ) { RotorBank::step( stepVec ); }

		/// Returns a string indicating the position of each rotor.
		inline std::string rotPos() const { return RotorBank::rotPos(); }

		/// Returns the number of characters in the generator character set.
		inline size_t getLen() { return Generator::getLen(); }
	private:
	};
}

#endif /* ROTORXOR_SCRAMBLER_HH */
