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
 * @brief Header file for Rotor class.
 *
 */
#ifndef ROTORXOR_ROTOR_H
#define ROTORXOR_ROTOR_H

#include "drum.hh"

#include "../includes/keyfile.hh"

namespace RotorXor
{
	/// A software implementation of the rotor cipher machine's rotor.
	class Rotor
	: protected Drum
	{
		friend class RotorBank;							///< Rotor List Manager.
	public:
		Rotor();
		~Rotor();

		/// Initializes rotor.
		/**
		 * Initializes rotor with a new key.  Sets the drum's alphabet,
		 * its offset, the rotor's notch position, and its initial
		 * position, which is saved, along with a CSPRNG reset seed.
		 *
		 * @param key A pointer to a key in the primary keychain.
		 */
		inline void init( const KeyFile::Key* const key ) {
			
			setWire( key );
			setOffset();
			setNotch();
			setPos();
			defPos = pos;
			rstVal = Drum::getSeed();
		}

		char encode( const char ) const;					///< Encrypt a character.
		char decode( const char ) const;					///< Decrypt a character.
		int advance();								///< Advance rotor position;
		int retard();								///< Retard rotor position;

		std::string getPos() const;						///< Return the position of the rotor.  Calls the recursive version below.
		std::vector< char > getPos( std::vector< char >& ) const;		///< Recursive function which appends the rotor's current position to a char vector.

		/**
		 * Test if the rotor is a the notch.
		 *
		 * @return True if the rotor position matches the notch position.
		 */
		inline bool atNotch() const
		{
			return notches[ pos ];
		}

		/**
		 * Print the translation alphabet for the rotor to screen.
		 *
		 * @return A string showing the rotor's alphabet.
		 */
		inline std::string getWire() const { return Drum::getWire(); }
		void reset();								/// Reset the rotor to its initial state.
	protected:
		void genKey( const bool = false );					/// Generate a random key for the rotor.
	private:
		int pos = 0;								///< Rotor position.
		int defPos;
		unsigned rstVal;
		std::vector< bool > notches;						///< Vector representing rotor notch(s).
		Rotor* prev = nullptr;							///< Pointer to previous rotor.
		Rotor* next = nullptr;							///< Pointer to next rotor.

		/// Shuffle drum.
		inline void setWire( const KeyFile::Key* key ) { Drum::setWire( key ); }
		int setOffset();							///< Skew rotor outputs.
		int setNotch();								///< Generate rotor notches.
		int setPos();								///< Initial rotor position.
	};

}
#endif /* ROTORXOR_ROTOR_H */
