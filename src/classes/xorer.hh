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
 * @brief Header file for Xorer class.
 *
 */
#ifndef ROTORXOR_XORER_HH
#define ROTORXOR_XORER_HH

#include "pulser.hh"
#include "scrambler.hh"

#include "../includes/keyfile.hh"

#include <string>
#include <vector>

namespace RotorXor
{
	/// Class Xorer manages the character XORing protocal used by RotorXor.
	class Xorer
	{
	public:
		/// Default constructor for Xorer.
		/**
		 * Constructs a blank Xoror object for later initialization.
		 */
		inline Xorer() {
			scrambler = new Scrambler;
			pulser = new Pulser;
		}

		/// Xorer constructor which accepts a number of rotors to add.
		Xorer( int );

		/// Xorer constructor which constructs object based on supplied keychain.
		/**
		 * @param keyVec A vector containing pointers to keys in the main keychain.
		 */
		inline Xorer( std::vector< KeyFile::Key* >& keyVec ) {
			setKeys( keyVec );
		}

		/// Deletes memory allocation for scrambler and pulser.
		inline ~Xorer()
		{
			delete pulser;
			delete scrambler;
		}

		/// Generate new keychain for RotorXor.
		inline void genKeys() {
			scrambler->genKeys();
			pulser->genKeys();
		}

		/// Resets the Xorer to its initial state.
		inline void reset() {
			scrambler->reset();
			pulser->reset();
		}

		/// Initializes a blank Xorer.
		void setKeys( std::vector< KeyFile::Key* >& keyVec );

		/// Encode a character;
		char encode( char );

		/// Steps the pulser and scrambler.
		void step();

		/// Get scrambler rotor positions.
		/**
		 * @return String indicating the scrambler rotor positions.
		 */
		inline std::string sRot() const { return scrambler->rotPos(); }

		/// Get pulser rotor positions.
		/**
		 * @return String indicating the pulser rotor positions.
		 */
		inline std::string pRot() const { return pulser->rotPos(); }
	private:
		/// Perform final XOR encoding.
		/**
		 * @return		Returns the char value which results from XORing the two inputs.
		 * @param inChar	Character to be encoded.
		 * @param xChar		Character to XOR inChar against.
		 */
		inline char calc( const char inChar, const char xChar ) const
		{
			try
			{
				char outChar = CharSet::pos2val( CharSet::val2pos( inChar ) ^ CharSet::val2pos( xChar ));
				return outChar;
			}
			catch( ... )
			{
				throw;
			}
		}
		Scrambler* scrambler = nullptr;
		Pulser* pulser = nullptr;
	};
}
#endif /* ROTORXOR_XORER_HH */
