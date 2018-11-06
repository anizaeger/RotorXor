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
 * @brief Header file for CharGen class.
 *
 */
#ifndef ROTORXOR_CHARGEN_H
#define ROTORXOR_CHARGEN_H

#include "charSet.hh"

#include "../includes/keyfile.hh"
#include "../includes/randgen.hh"

/// Project namespace
namespace RotorXor
{
	/// Class Generator deterministically generates random characters within the included character set.
	class Generator
	{
	public:
		/// Default constructor.
		/**
		 * Allocates memory for an object of type RandGen.
		 */
		inline
		Generator()
		{
			randGen = new RandGen();
		}

		/// Constructor with seed initializer.
		/**
		 * @param seed The address of the KeyFile::Key object containing the key
		 * values for the CSPRNG.
		 */
		inline
		Generator( const KeyFile::Key* const seed )
		{
			randGen = new RandGen();
			randGen->setKey( seed );
		}

		/// Object destructor.
		/**
		 * Deallocates dynamically-allocated memory set aside for RandGen.
		 */
		inline
		~Generator()
		{
			delete randGen;
		}

		/// Generates a random key.
		/**
		 * Creates a key for the character generator, and adds it to the keyfile.
		 */
		inline void
		genKey()
		{
			init( KeyFile::genKey());
		}

		/// Initializes the random number generator for this component object.
		/**
		 * @param seed The address of the KeyFile::Key object containing the key
		 * values for the CSPRNG.
		 */
		inline void
		init( const KeyFile::Key* const seed )
		{
			randGen->setKey( seed );
		}

		/// Resets the random number generator.
		/**
		 * Reset's the random number generator to its initial state.
		 */
		inline void
		reset()
		{
			randGen->reset();
		}

		/// Generates and returns a random character.
		/**
		 * @return A random character.
		 */
		char
		getChar()
		{
			return CharSet::pos2val( randGen->getRandRange( 0, ( CharSet::getLen())));
		};

		/// Get the size of the character set.
		inline size_t getLen()
		{
			return CharSet::getLen();
		}
	private:
		RandGen* randGen;	///< Pointer to instance's CSPRNG
	};
}
#endif /* ROTORXOR_CHARGEN_H */
