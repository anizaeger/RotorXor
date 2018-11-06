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
 * @brief Header file for Handler class.
 *
 */
#ifndef ROTORXOR_HANDLER_HH
#define ROTORXOR_HANDLER_HH

#include "xorer.hh"

#include <iostream>
#include <string>
#include <vector>

namespace RotorXor
{
	/// Input/output handler and RotorXor Management Module.
	/**
	 * The Xorer on its own is only capable of processing individual bytes.
	 * However, most data is communicated using strings or groups of bytes.
	 * The handler extends the Xoror by performing the requisite operations,
	 * breaking up streams into individual bytes for processing by the
	 * xorer.  In addition, the handler also handles translation between raw
	 * cipherdata and base64 encoding, allowing for the encoding of the full
	 * ASCII character set, as well as raw binary data.
	 *
	 * The handler also provides a common interface for all components of
	 * RotorXor, allowing all management functions to be done through a
	 * single object.
	 */
	class Handler
	: protected Xorer
	{
	public:
		inline Handler( int numRotors ) : Xorer( numRotors ) {}		///< Construct a handler with a specific numner of rotors.

		/// Construct a handler with a specific keychain.
		inline Handler( std::vector< KeyFile::Key* >& keyVec )
		: Xorer( keyVec ) {}

		inline ~Handler() {
			KeyFile::clear();
		}

		inline void genKeys() { Xorer::genKeys(); }			///< Generate keys for the rotorXor.

		inline int numRotors() const { return Xorer::numRotors(); }	///< Get number of rotors in RotorXor.

		std::string encode( const std::string& );			///< Encrypts a string and converts it to base64.

		std::string decode( const std::string& );			///< Decrypts base64 to a string.

		std::string cipher( const std::string& );			///< Ciphers/deciphers a string.
		unsigned char cipher( const unsigned char );			///< Passthrough for ciphering single bytes.
	private:
		std::vector< unsigned char > inData;
		std::vector< unsigned char > outData;
	};
}

#endif /* ROTORXOR_HANDLER_HH */
