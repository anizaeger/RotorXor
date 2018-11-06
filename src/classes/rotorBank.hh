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
 * @brief Header file for RotorBank class.
 *
 */
#ifndef ROTORXOR_ROTORLIST_H
#define ROTORXOR_ROTORLIST_H

#include "rotor.hh"

#include "../includes/keyfile.hh"

#include <memory>
#include <string>
#include <vector>

/// Project namespace
namespace RotorXor
{
	/// Class RotorBank manages a vector of rotors.
	class RotorBank
	{
	public:
		friend class Rotor;

		RotorBank();								///< Construct a blank RotorBank.
		RotorBank( int numRot );						///< Construct a RotorBank and append numRot rotors.
		~RotorBank();
		void append( int numRot );						///< Append numRot rotors to the bank.
		void append( KeyFile::Key* = nullptr );					///< Append a new rotor to the bank, optionally pre-keyed.
		void append( std::vector< KeyFile::Key* > keyVec );			///< Append multiple pre-keyed rotors.

		/// Generate keys for all rotors in the bank.
		/**
		 * @warning DO NOT do this without first clearing existing keys!
		 * Additional keys will be appended onto the current keychain.
		 */
		inline void genKeys() { head->genKey( true ); }				
		void reset();								///< Reset rotors position and CSPRNG to their initial state.
		void clear();								///< Clear all rotors from bank.
		/// Returns the number of rotors in the bank.
		/**
		 * @return How many rotors are in the bank.
		 */
		inline size_t numRotors() const {
			return rotorVec.size();
		}

		inline Rotor* begin() const { return head; }				///< Return a pointer to the first rotor.
		inline Rotor* end() const { return tail; }				///< Return a pointer to the last rotor.

		char encode( const char ) const;					///< Encode a character
		char decode( const char ) const;					///< Decode a character

		std::vector< bool > testNotches() const;				///< Return the state of notches on bank's rotors.
		void step( const std::vector< bool >& steps );				///< Step the rotors as indicated by 'steps'.

		std::string rotPos() const;						///< Return the position of the bank's rotors.

		/*
			OPERATOR OVERLOADS
		*/
		/// Access rotors within RotorBank using array-style notation.
		inline Rotor* operator[]( const int idx ) const { Rotor* retVal = rotorVec[ idx ].get(); return retVal; }
	private:
		typedef std::vector< std::unique_ptr< Rotor > > RotorVec;
		RotorVec rotorVec;							///< Vector holding pointers to individual rotors.
		const int MAX_ROT = 8;
		Rotor* head = nullptr;
		Rotor* tail = nullptr;
	};
}
#endif /* ROTORXOR_ROTORLIST_H */
