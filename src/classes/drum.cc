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
 * @brief Source code for Drum class.
 *
 */
#include "drum.hh"

#include "../includes/randgen.hh"

#include <iostream>
#include <random>
#include <string>

using namespace RotorXor;

/// Keys for the CSPRNG.
typedef KeyFile::Key Key;

/********************************************************************************
 * CONSTRUCTORS AND DESTRUCTORS
 ********************************************************************************/
Drum::Drum()
{
	newWire();
}

/**
 * Generates a key for the drum.
 */
void
Drum::genKey()
{
	setWire( KeyFile::genKey());
}

/**
 * Encodes a character by treating inChar as an defacto "index" for
 * subTable.  The value of the element represented by this index is
 * then returned.
 *
 * @param inChar Character to be encoded.
 * @return The encoded character.
 */
char
Drum::encode( const char inChar ) const
{
	try
	{
		char outChar = subTable[ CharSet::val2pos( inChar )];
		return outChar;
	}
	catch( ... )
	{
		throw;
	}
}

/**
 * Decodes a character by treating the inChar as a search value for subTable.
 * The elements of vector subTable are searched until the value matching
 * inChar is located.  The index value is then used to derive a character
 * from the CharSet's alphabet, which is returned.
 *
 * @param value Character to be decoded.
 * @return The decoded character.
 */
char
Drum::decode( const char value ) const
{
	char outChar = 0;
	for ( int pos = 0; pos < CharSet::getLen(); pos++ )
	{
		if ( subTable[ pos ] == value )
		{
			outChar = CharSet::pos2val( pos );
			break;
		}
	}
	return outChar;
}
/**
 * Gets the alphabet currently set for the drum.
 *
 * @return A string showing the drum's currently-set alphabet.
 */
std::string
Drum::getWire() const
{
	std::string outString = "";
	for ( int idx = 0; idx < CharSet::getLen(); idx++ )
	{
		outString += subTable[ idx ];
	}
	return outString;
}

/**
 * 
 */
char
Drum::setIdxVal( const int idx, const char val)
{
	subTable[ idx ] = val;
	return val;
}

/**
 * 
 */
char
Drum::getIdxVal( const int idx ) const {
	return subTable[ idx ];
}

/********************************************************************************
 * DRUM GENERATION
 ********************************************************************************/
/**
 * Reset drum's alphabet to an un-scrambled state.
 */
void
Drum::newWire()
{
	subTable.clear();
	for ( unsigned char c = CharSet::FIRST; c <= CharSet::LAST; c++ ) {
		subTable.push_back( c );
	}
}

/**
 * Deterministically scrambles the alphabet used by the drum for its
 * substitution cipher.  The function makes 7 passes through each element of the
 * subTable vector.  With each pass, it swaps that element with a differnet random
 * but deterministic element
 *
 * @param key The key to use for scrambling the drum.
 */
void
Drum::setWire( const KeyFile::Key* key )
{
	newWire();
	rndGen.setKey( key );
	typename std::vector< char >::iterator subIt;
	typename std::vector< char >::iterator swapIt;
	for ( int pass = 0; pass < 7; pass++ ) {
		for ( subIt = subTable.begin(); subIt != subTable.end(); subIt++ )
		{
			do
			{
				swapIt = subTable.begin() + rndGen.getRandRange( 0, CharSet::getLen());
			}
			while (( subIt == subTable.end()) || ( swapIt == subTable.end()) || subIt == swapIt );
			std::iter_swap( subIt, swapIt );
		}
	}
}
