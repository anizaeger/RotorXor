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
 * @brief Source code for Handler class.
 *
 */
#include "handler.hh"

#include "charset.hh"

#include "../includes/base64.hh"

using namespace RotorXor;

/********************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 ********************************************************************************/
/**
 * Ciphers a string, then converts the resulting ciphertext into base64.
 *
 * @param plainText Plaintext to be encrypted through the RotorXor.
 *
 * @return Base64-encoded ciphertext.
 */
std::string
Handler::encode( const std::string& plainText )
{
	// Run plaintext through rotorXor.
	std::string cipherText = cipher( plainText );

	// Convert ciphertext into a byte array for conversion to base64.
	std::vector< unsigned char > cipherData( cipherText.begin(), cipherText.end());

	// Base64 encode and return the resulting ciphercode.
	std::string cipherCode = base64Encode( cipherData );
	return cipherCode;
}

/**
 * Accepts and decrypts base64-encoded ciphertext.
 *
 * @param cipherCode Base64-encoded ciphertext.
 *
 * @return Decrypted plaintext.
 */
std::string
Handler::decode( const std::string& cipherCode )
{
	// Convert the base64 encoded string into ciphertext data.
	std::vector< unsigned char > cipherData = base64Decode( cipherCode );

	// Convert the ciphertext byte array into a ciphertext string.
	std::string cipherText( cipherData.begin(), cipherData.end());

	// Run ciphertext through the rotorXor.
	std::string plainText = cipher( cipherText );
	return plainText;
}

/**
 * Encrypts/decrypts plaintext/ciphertext.
 *
 * @param inString Bytestream to be passed through rotorXor.
 *
 * @return RotorXor output.
 */
std::string
Handler::cipher( const std::string& inString )
{
	std::string outString;
	Xorer::reset();
	try
	{
		for ( int c = 0; c < inString.length(); c++ )
		{
			char inChar = inString[ c ];
			char outChar = cipher( inChar );
			outString += outChar;
		}
		return outString;
	}
	catch ( ... )
	{
		throw;
	}
}

/**
 * Encrypts/decrypts plaintext/ciphertext.
 *
 * @param inChar Byte to be passed through rotorXor.
 *
 * @return RotorXor output.
 */
unsigned char
Handler::cipher( const unsigned char inChar )
{
	std::string outString;
	try
	{
		char outChar = Xorer::encode( inChar );
		return outChar;
	}
	catch ( ... )
	{
		throw;
	}
}