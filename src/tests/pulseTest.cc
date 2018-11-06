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
 * @brief Pulser Test
 *
 * Creates an instance of the pulser to demonstrate its operation.  Allows the
 * user to generate a new keychain for a pulser with a specified number of
 * rotors, or to import a pre-existing keychain, for which a pulser will be
 * constructed and configured.  The pulser will then generate 1000 pulses,
 * printing the resulting bool array for each pulse to the screen.  Demonstrates
 * the generates of pulses, as well as the deterministic capibilities when used
 * with a previously-generated key.
 *
 */
#include "../classes/pulser.hh"

#include "../includes/basicSys.hh"
#include "../includes/interface.hh"
#include "../includes/keyfile.hh"

#include <iostream>
#include <string>

using namespace RotorXor;
const char CharSet::FIRST = ' ';
const char CharSet::LAST = '_';

typedef KeyFile::Key Key;							///< Type for individual keys.
typedef std::vector< Key* > KeyVec;						///< Type for a vector of pointers to keys.

/**
 *	Run test on Pulser.
 */
int
main( void )
{
	KeyFile keychain;

	if ( choiceBool( "Generate keys" ))
	{
		int numRotors = choiceNum( "How many rotors", 2, 8 );
		for ( int k = 0; k <= numRotors; k++ )
		{
			keychain.genKey();
		}
		std::cout << keychain.expKey() << std::endl;
	}
	else
	{
		std::string inData;
		std::cout << "Please enter your key's base64 string now: ";
		std::cin >> inData;

		keychain.impKey( inData );
	}

	KeyVec keyVec;

	for ( int i = 0; i < keychain.numKeys(); i++ )
	{
		keyVec.push_back( keychain.getKey( i ));
	}

	Pulser* pulser = new Pulser;

	pulser->setKey( keyVec );

	for ( int i = 0; i < 1000; i++ )
	{
		std::vector< bool > pulse = pulser->pulse( pulser->numRotors());
		std::cout << pulser->rotPos() << " - ";
		for ( int i = 0; i < pulse.size(); i++ )
		{
			std::cout << " " << (int)pulse[ i ] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}
