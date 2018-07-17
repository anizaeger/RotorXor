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
 * @brief Header file for Drum class.
 *
 */

#ifndef ROTORXOR_DRUM_H
#define ROTORXOR_DRUM_H

#include "charSet.hh"

#include "../includes/keyfile.hh"
#include "../includes/randgen.hh"

#include <map>
#include <string>
#include <vector>

/// Project namespace
namespace RotorXor
{
	/// The translator drum stores the substitution cipher's alphabet.
	/**
	 * The translator drum emulates the actions of the wiring drum used on old-style
	 * rotor encryption machines.
	 */
	class Drum
	{
	public:
		Drum();								///< Initialize the drum.
		virtual std::string getWire() const;				///< Return a string representing the drum outputs.
		virtual char encode( const char ) const;			///< Encrypt a character.
		virtual char decode( const char ) const;			///< Decrypt a character.
	protected:
		void genKey();							///< Generate a key for the drum.

		/// Get a random number, intended to be used as a post-setWire seed.
		inline unsigned
		getSeed()
		{
			return rndGen.getRandNum();
		}

		/// Set CSPRNG to temporary seed.
		/**
		 * @param n Value to use as new seed.
		 */
		inline void
		reset( unsigned n )
		{
			rndGen.reset( n );
		}

		/// Reset CSPRNG to initial state.
		inline void
		reset()
		{
			rndGen.reset();
		}

		void setWire( const KeyFile::Key* );				///< Shuffle the drum using the provided key.
		char setIdxVal( const int idx, const char val );		///< Set a drum idx to a character val.
		char getIdxVal( const int idx ) const;				///< Get the value of a specific drum idx.

		/**
		 * Get a random value between 0 inclusive and the number of
		 * characters in the set exclusive.  Intended for use as a
		 * random drum index.
		 *
		 * @return A random drum idx value.
		 */
		inline unsigned
		getRandChar()
		{
			return ( rndGen.getRandRange( 0, CharSet::getLen()));
		}

		static const int keys = 1;					///< Number of keys supported by class.
	private:
		RandGen rndGen;
		std::vector< char > subTable;
		void newWire();
	};

}
#endif /* ROTORXOR_DRUM_H */
