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
 * @brief Source code for CharSet class.
 *
 */
#include "charSet.hh"

#include <string>
#include <stdexcept>

using namespace RotorXor;

/**
 * Accepts a position number in the character set's alphabet, and returns the
 * value of the character at that position.
 *
 * @param inNum Numeric character identifier.
 *
 * @return Character value of identifier.
 */
char
CharSet::pos2val( int inNum )
{
	int maxNum = getLen();
	while ( inNum < 0 ) {
		inNum += maxNum;
	}
	int charNum = inNum % maxNum;
	char outChar = char( charNum + FIRST );
	return outChar;
}
/**
 * Accpets a character from the configured character set and returns its
 * position in the character set's alphabet.
 *
 * @param inChar A character within the set.
 *
 * @return The character's identifier.
 *
 * @exception std::string isn't in the configured character set.
 */
int
CharSet::val2pos( const char inChar )
{
	try {
		int charNum = (int)inChar - (int)FIRST;
		if ( charNum < 0 || charNum >= getLen())
		{
			std::string errMsg = "Character '";
			errMsg += inChar;
			errMsg += "' not in character set!";
			throw std::out_of_range( errMsg );
		}
		return charNum;
	}
	catch( ... )
	{
		throw;
	}
}
