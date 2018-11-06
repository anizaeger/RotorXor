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
 * @brief Source code for Rotor class.
 *
 */
#include <iostream>

#include "rotor.hh"

using namespace RotorXor;

/********************************************************************************
 * CONSTRUCTORS AND DESTRUCTORS
 ********************************************************************************/
/**
 * Default constructor.  Builds initial notch vector.
 */
Rotor::Rotor()
{
	notches.clear();
	for ( int n = 0; n < CharSet::getLen(); n++ )
	{
		notches.push_back( false );
	}
}

/**
 * Destructor
 */
Rotor::~Rotor()
{
	
}

/********************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 ********************************************************************************/
/**
 * @param inVal Character to be 
 */
char
Rotor::encode( const char inVal ) const
{
	try
	{
		// Calculate proper entrypoint into drum for encoding.
		int inIdx = CharSet::val2pos( inVal );
		inIdx += pos;
		while ( inIdx >= CharSet::getLen())
		{
			inIdx -= ( CharSet::getLen());
		}

		// Encode output
		char cipherVal = Drum::getIdxVal( inIdx );

		// Calculate proper exitpoint from drum for encoding.
		int outIdx = CharSet::val2pos( cipherVal );
		outIdx += pos;
		while ( outIdx >= CharSet::getLen())
		{
			outIdx -= ( CharSet::getLen());
		}

		char outVal = CharSet::pos2val( outIdx );
		if ( next )
		{
			return next->encode( outVal );
		}
		else
		{
			return outVal;
		}
	}
	catch( ... )
	{
		throw;
	}
}

/**
 * 
 */
char
Rotor::decode( const char inVal ) const
{
	try
	{
		// Calculate proper entrypoint into drum for encoding.
		int inIdx = CharSet::val2pos( inVal );
		inIdx -= pos;
		while ( inIdx < 0 )
		{
			inIdx += ( CharSet::getLen());
		}

		// Decode output
		char cipherVal = Drum::decode( CharSet::pos2val( inIdx ));

		// Calculate proper exitpoint from drum for encoding.
		int outIdx = CharSet::val2pos( cipherVal );
		outIdx -= pos;
		while ( outIdx < 0)
		{
			outIdx += ( CharSet::getLen());
		}

		char outVal = CharSet::pos2val( outIdx );
		if ( prev )
		{
			return prev->decode( outVal );
		}
		else
		{
			return outVal;
		}
	}
	catch( ... )
	{
		throw;
	}
}

/**
 * Advance the position of the rotor by one step.
 *
 * @return The rotor's end position.
 */
int
Rotor::advance()
{
	if ( ++pos == CharSet::getLen())
	{
		pos = 0;
	}
	return pos;
}

/**
 * Reverse the position of the rotor by one step.
 *
 * @return The rotor's end position.
 */
int
Rotor::retard()
{
	if ( --pos < 0 )
	{
		pos = CharSet::getLen() - 1;
	}
	return pos;
}

/**
 * Generates a char vector for passing recursive down the bank, then returns
 * the string created by this function's recursive counterpart below.
 *
 * @return A string showing the positions of the rotors in the bank.
 */
std::string
Rotor::getPos() const
{
	std::vector< char > tmp;
	getPos( tmp );
	std::string str( tmp.begin(), tmp.end());
	return str;
}

/**
 * Appends the current rotor's position to a char vector.  If this is the final
 * rotor on the bank, then returns this vector to the caller, otherwise
 * recursively calls this function in the next rotor.
 *
 * @param buffer A char vector holding the rotor positions collected.
 * @return the buffer 
 */
std::vector< char >
Rotor::getPos( std::vector< char >& buffer ) const
{
	char posChar = CharSet::pos2val( pos );
	buffer.push_back( posChar );
	if ( next )
	{
		return next->getPos( buffer );
	}
	else
	{
		return buffer;
	}
}

/**
 * Reset the drum's CSPRNG and pos back to the rotor's startup state.
 */
void
Rotor::reset()
{
	Drum::reset( rstVal );
	pos = defPos;
}
/********************************************************************************
 * PROTECTED MEMBER FUNCTIONS
 ********************************************************************************/
void
Rotor::genKey( const bool parse )
{
	init( KeyFile::genKey());
	if ( parse && next )
	{
		next->genKey( parse );
	}
	else
	{
		return;
	}
}

/********************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 ********************************************************************************/
/**
 * Offset the drum by a deterministically random amount.  This is the equivelent
 * of the Enigma's ring setting.
 *
 * @return The number of elements that the drum has been offset by.
 */
int
Rotor::setOffset()
{
	unsigned offsetVal = getRandChar();
	if ( offsetVal )
	{
		for ( int pass = 0; pass < offsetVal; pass++ )
		{
			char tmpVal = Drum::getIdxVal( 0 );
			for ( int idx = 0; idx < ( CharSet::getLen()); )
			{
				int tmpIdx = idx;
				Drum::setIdxVal( tmpIdx, Drum::getIdxVal( ++idx ));
			}
			Drum::setIdxVal(( CharSet::getLen() - 1 ), tmpVal );
		}
	}
	return offsetVal;
}

/**
 * Set a deterministically random notch position for advancing the next rotor.
 *
 * @return The position of the notch.
 */
int
Rotor::setNotch()
{
	int notch = getRandChar();
	notches[ notch ] = true;
	return notch;
}

/**
 * Set the rotor to a deterministically random position.
 *
 * @return The set position of the rotor.
 */
int
Rotor::setPos()
{
	pos = getRandChar();
	return pos;
}
