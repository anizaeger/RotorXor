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
 * @brief Source code for RotorBank class.
 *
 */
#include "rotorBank.hh"

using namespace RotorXor;

/********************************************************************************
 * CONSTRUCTORS AND DESTRUCTORS
 ********************************************************************************/
/**
 * Default Constructor
 */
RotorBank::RotorBank()
{
	
}

/**
 * Construct a new bank, and append numRot rotors.
 *
 * @param numRot Number of rotors to create when constructing bank.
 */
RotorBank::RotorBank( int numRot )
{
	append( numRot );
}

/**
 * Clears all rotors from the bank.
 */
RotorBank::~RotorBank()
{
	clear();
}

/********************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 ********************************************************************************/
/**
 * Appends a number of rotors to the bank.  These rotors are all unkeyed.
 *
 * @param numRot The number of rotors to append to the bank.
 */
void
RotorBank::append( int numRot )
{
	for ( int rot = 0; rot < numRot; rot++ )
	{
		append();
	}
}

/**
 * Appends an optionally pre-keyed rotor to the bank.
 *
 * @param key An optional key to apply to the appended rotor.
 */
void
RotorBank::append( KeyFile::Key* key )
{
	std::unique_ptr< Rotor > tmpPtr( new Rotor());
	Rotor* rawPtr = tmpPtr.get();
	// If rotors already exist, set last rotor's 'next' pointer.
	if ( numRotors() > 0 )
	{
		end()->next = rawPtr;
		rawPtr->prev = end();
	}
	else
	{
		head = rawPtr;
	}

	if ( key )
	{
		rawPtr->init( key );
	}

	rotorVec.push_back( std::move( tmpPtr ));
	tail = rawPtr;
}

/**
 * Appends rotors using a keychain.
 *
 * @param keyVec A vector containing pointers to the keys to assign.
 */
void
RotorBank::append( std::vector< KeyFile::Key* > keyVec )
{
	for ( int k = 0; k < keyVec.size(); k++ )
	{
		append( keyVec[ k ]);
	}
}

/**
 * Clears rotorVec, calling the destructors for each of the associated rotors
 * in the process.
 */
void
RotorBank::clear()
{
	rotorVec.clear();
	head = nullptr;
	tail = nullptr;
}

/**
 * Reset all rotors to their initial state, including positions and associated
 * CSPRNGS.
 */
void
RotorBank::reset()
{
	for ( int r = 0; r < numRotors(); r++ )
	{
		rotorVec[ r ]->reset();
	}
}

/**
 * Show the position of the rotors in the bank.
 */
std::string
RotorBank::rotPos() const
{
	std::string rotPosTxt;

	if ( rotorVec.size() > 0 )
	{
		rotPosTxt = begin()->getPos();
	}

	return rotPosTxt;
}


char
RotorBank::encode( const char inChar ) const
{
	try
	{
		char outChar = inChar;
		if ( rotorVec.size() > 0 )
		{
			outChar = begin()->encode( outChar );
		}
		return outChar;
	}
	catch( ... )
	{
		throw;
	}
}


char
RotorBank::decode( const char inChar ) const
{
	try
	{
		char outChar = inChar;
		if ( rotorVec.size() > 0 )
		{
			outChar = end()->decode( inChar );
		}
		return outChar;
	}
	catch( ... )
	{
		throw;
	}
}

/**
 * Returns a vector indicating whether or not the position of the rotor matches
 * its notch position.
 *
 * @return A bool vector indicating the notch state of rhe respective rotors.
 */
std::vector< bool >
RotorBank::testNotches() const
{
	std::vector< bool > notches;
	for ( int idx = 0; idx < numRotors(); idx++ )
	{
		notches.push_back( rotorVec[ idx ]->atNotch());
	}
	return notches;
}

/**
 * Increment the position of specified rotors in the bank.
 *
 * @param steps A bool vector indicating whether or not to step respective rotors.
 */
void
RotorBank::step( const std::vector< bool >& steps )
{
	size_t stepped = steps.size();
	for ( int r = 0; r < stepped && r < numRotors(); r++ )
	{
		if ( steps[ r ])
		{
			rotorVec[ r ]->advance();
		}
	}
}
