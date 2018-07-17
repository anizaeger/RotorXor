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
 * @brief Character generator test.
 *
 * Demonstrates the capibilities of the random character generator.  Allows a
 * key to be generated at random, or for a previoussly-generated key to be used
 * to demonstrate deterministic capabilities.
 *
 */
#include <iostream>
#include <string>

#include "../classes/charGen.hh"

#include "../includes/keyfile.hh"
#include "../includes/randgen.hh"

#include "../includes/basicSys.hh"
#include "../includes/interface.hh"

using namespace RotorXor;
const char CharSet::FIRST = ' ';
const char CharSet::LAST = '_';

/// Individual keys.
typedef KeyFile::Key Key;

/**
 * Run test on character generator.
 */
int
main( void )
{
	KeyFile keychain;

	if ( choiceBool( "Generate key" ))
	{
		keychain.genKey();
	}
	else
	{
		std::string inData;
		std::cout << "Key data: ";

		std::cin >> inData;

		keychain.impKey( inData );
	}

	Key* newKey = keychain.getKey(0);

	std::cout << keychain.expKey() << std::endl;

	Generator gen;

	gen.init( newKey );

	std::cout << gen.getChar() << std::endl;

	return 0;
}
