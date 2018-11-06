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
 * @brief Source code for Scrambler class.
 *
 */
#include "scrambler.hh"

using namespace RotorXor;

/// Vector of pointers to keys in the primary keychain.
typedef std::vector< KeyFile::Key* > Keys;
/********************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 ********************************************************************************/
void
Scrambler::setKey( Keys& keyVec )
{
	if ( keyVec.size())
	{
		Generator::init( keyVec.back());
		keyVec.pop_back();
		RotorBank::clear();
		while ( keyVec.size())
		{
			RotorBank::append( keyVec.back());
			keyVec.pop_back();
		}
	}
}

char
Scrambler::genChar()
{
	char data = Generator::getChar();
	data = RotorBank::encode( data );
	return data;
}
