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
 * @brief Demonstrates symmetric key encryption used by the RotorXor.
 *
 * This generates the encryption/decryption capibilities of RotorXor.  Allows a
 * key to be generated at random, or for a previoussly-generated key to be used
 * to demonstrate decryption capilities when used with the ciphertext of a
 * previously-encrypted message.  Any out-of-bounds printable characters are
 * converted to printable characters.  Lowercase letters are capitalized, and
 * various punctuation characters are converted to printable substitutes.
 *
 */
#include "../classes/handler.hh"

#include "../includes/basicSys.hh"
#include "../includes/interface.hh"
#include "../includes/keyfile.hh"

#include <sysexits.h>

#include <iostream>
#include <stdexcept>
#include <string>

using namespace RotorXor;
const char CharSet::FIRST = 0;
const char CharSet::LAST = 127;

typedef KeyFile::Key Key;			///< Individual keys.
typedef std::vector< Key* > KeyVec;		///< Vector of pointers to keys.

/**
* Run test on RotorXor cipher.
*/
int
main( void )
{
	Handler* handler;

	int numRotors = 0;

	if ( choiceBool( "Generate keys" ))
	{
		numRotors = choiceNum( "How many rotors", 2, 8 );
		handler = new Handler( numRotors );
		handler->genKeys(); 
		std::cout << KeyFile::expKey() << std::endl;
	}
	else
	{
		std::string inData;
		std::cout << "Please enter your key's base64 string now: " << std::endl;
		std::cin >> inData;
		clearBuffer();

		KeyFile::impKey( inData );

		KeyVec keyVec = KeyFile::getKeys();
		handler = new Handler( keyVec );
	}

	printf( "Checksum: 0x%X\n", KeyFile::checksum());

	bool plaintext = choiceBool( "Are you entering plaintext");

	std::string inString;
	if ( plaintext )
	{
		std::cout << "Enter the plaintext to be encrypted: " << std::endl;
	}
	else
	{
		std::cout << "Enter the cipher data to be decrypted: " << std::endl;
	}
	std::getline( std::cin, inString );

	std::string outString;

	try
	{
		if ( plaintext )
		{
			outString = handler->encode( inString );
		}
		else
		{
			outString = handler->decode( inString );
		}
	}
	catch ( const std::out_of_range& oor )
	{
		std::string errMsg = "buffer character out of range: %s";
		printError( EX_DATAERR, errMsg.c_str(), oor.what());
	}
	
	std::cout << outString << std::endl;
	endProg( 0 );
}
