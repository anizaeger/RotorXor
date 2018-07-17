/********************************************************************************
 *                                                                              *
 * A keychain management system for BBS CSPRNGs                                 *
 *                                                                              *
 * Copyright (C) 2018 by Anakin-Marc Zaeger                                     *
 * All Rights Reserved                                                          *
 *                                                                              *
 * This program is free software: you can redistribute it and/or modify         *
 * it under the terms of the GNU General Public License as published by         *
 * the Free Software Foundation, either version 3 of the License, or            *
 * (at your option) any later version.                                          *
 *                                                                              *
 * This program is distributed in the hope that it will be useful,              *
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
 * @brief Source code for KeyFile class.
 *
 */
#include "keyfile.hh"

#include "base64.hh"

#include <boost/crc.hpp>

#include <iostream>
#include <limits>
#include <random>

/********************************************************************************
 * TYPEDEFS
 ********************************************************************************/
/// Keys for the CSPRNG.
typedef KeyFile::Key Key;

/// unique_ptr to Keys.
typedef std::unique_ptr< Key > KeyPtr;


/********************************************************************************
 * STATIC MEMBER INITIALIZATION
 ********************************************************************************/
std::vector< KeyPtr > KeyFile::keyFile;
std::random_device KeyFile::keyGen;

/********************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 ********************************************************************************/
/**
 * Generate a new key, append it to keyFile, and return a pointer to it.
 *
 * @return A pointer to the new key.
 */
Key*
KeyFile::genKey()
{
	KeyPtr key( new Key );
	Key* keyPtr = key.get();
	key->p = genPrime();
	Prime tmpQ;
	do
	{
		tmpQ = genPrime();
	}
	while ( tmpQ == key->p );
	key->q = tmpQ;
	key->s = genSeed( key->p, key->q );
	keyFile.push_back( std::move( key ));
	return keyPtr;
}

/**
 * Generate a new keychain with a specific number of keys.
 *
 * @param num Number of keys to create.
 */
std::vector< Key* >
KeyFile::genKeys( int num )
{
	clear();
	std::vector< Key* > outVec;
	for ( int k = 0; k < num; k++ )
	{
		outVec.push_back( genKey());
	}
	return outVec;
}

/**
 * Retrieves a key from keyFile.
 *
 * @return A pointer to the key requested.
 */
Key* const
KeyFile::getKey( const int keyNum )
{
	Key* keyPtr = ( KeyFile::keyFile[ keyNum ]).get();
	return keyPtr;
}

/**
 * Return a vector of pointers to keys in keyFile.
 *
 * @return keyFile as a vector of raw pointers.
 */
std::vector< Key* >
KeyFile::getKeys()
{
	std::vector< Key* > outVec;
	for ( int i = 0; i < numKeys(); i++ )
	{
		outVec.push_back( getKey( i ));
	}
	return outVec;
}

/**
 * Generate a simple 32 bit checksum of the key.
 *
 * @return The checksum as an unsigned int.
 */
unsigned
KeyFile::checksum()
{
	boost::crc_32_type crc32;

	std::vector< unsigned char > byteVec = keyFileBytes();

	unsigned char keyData[ byteVec.size() ];
	std::copy( byteVec.begin(), byteVec.end(), keyData );

	crc32.process_bytes( keyData, byteVec.size());

	return crc32.checksum();
}

/********************************************************************************
 * PUBLIC MEMBER FUNCTIONS - KEYFILE IMPORT / EXPORT
 ********************************************************************************/
/**
 * Imports a base64-encoded keychain into keyFile.
 *
 * @param inString base64-encoded keychain.
 */
void
KeyFile::impKey( const std::string& inString )
{
	std::vector< unsigned char > buffer;
	buffer = base64Decode( inString );

	size_t keys = buffer.size() / KEYSIZE;

	keyFile.clear();

	for ( int key = 0; key < keys; key++ )
	{
		unsigned char tmpBuf[ KEYSIZE ];
		int bufLoc = key * KEYSIZE;
		for ( int byte = 0; byte < KEYSIZE; byte++ )
		{
			tmpBuf[ byte ] = buffer[ bufLoc + byte ];
		}
		Key* tmpKey = new Key;
		*tmpKey = *(Key*)&tmpBuf;
		std::unique_ptr< Key > keyPtr( tmpKey );
		keyFile.push_back( std::move( keyPtr ));
	}
}

/**
 * Exports keyFle to a base64-encoded string.
 *
 * @return base64-encoded keychain.
 */
std::string
KeyFile::expKey()
{
	std::string outString;
	std::vector< unsigned char > outData;
	if ( keyFile.size() > 0 )
	{
		outData = keyFileBytes();
		outString += base64Encode( outData );
	}
	return outString;
}

/**
 * Prints a keyfile to screen.
 */
void
KeyFile::printKeys()
{
	std::cout << "Key List:" << std::endl;
	for ( int i = 0; i < keyFile.size(); i++ )
	{
		std::cout << "Key " << i << ": p = " << keyFile[ i ]->p << "; q = " << keyFile[ i ]->q << "; s = " << keyFile[ i ]->s << std::endl;
	}
}

/********************************************************************************
 * PRIVATE MEMBER FUNCTIONS - KEY GENERATION
 ********************************************************************************/
/**
 * Generates a random prime.
 *
 * @return A random prime number.
 */
KeyFile::Prime
KeyFile::genPrime()
{
	Prime rnd;
	do
	{
		do
		{
			rnd = keyGen();
		}
		while (! ( isBlum( rnd )));
	}
	while (! ( isPrime( rnd )));
	return rnd;
}

/**
 * Generates a random seed value.
 *
 * @param inP A prime number.
 * @param inQ A prime number
 * @return A random number less than inP * inQ.
 */
KeyFile::Seed
KeyFile::genSeed( const Prime inP, const Prime inQ )
{
	std::uniform_int_distribution< Seed > seedNum( 2, (((Seed)inP * (Seed)inQ ) - 1 ));
	int outS;
	do {
		outS = seedNum( keyGen );
	}
	while ( !( outS % inP ) || !( outS % inQ ) || ( outS < 2 ));
	return outS;
}

/**
 * Tests a number for potential "Blumness".
 *
 * @param inNum Number to be tested.
 * @return 'true' if the number is a in the form of 4t + 3.
 */
bool
KeyFile::isBlum( const Prime inNum )
{
	Prime testVal = inNum - 3;
	return (bool)( !( testVal % 4 ));
}

/**
 * Whether whether or not a number is prime.
 *
 * @param inNum Number to be tested.
 * @return 'true' if the number is prime.
 */
bool
KeyFile::isPrime( const Prime inNum )
{
	bool retVal;
	if (( retVal = (bool)( inNum % 2 )))
	{
		if (( retVal = (bool)( inNum % 3 )))
		{
			for ( long i =  5; i * i < inNum; i = i + 6 )
			{
				if ( !( retVal = (((bool)( inNum % i )) && ((bool)( inNum % ( i + 2 ))))))
				{
					break;
				}
			}
		}
	}
	return retVal;
}

/**
 *
 */
std::vector< unsigned char >
KeyFile::keyFileBytes()
{
	size_t keys = keyFile.size();
	std::vector< unsigned char > buffer;
	std::vector< unsigned char > outData;
	for ( int k = 0; k < keys; k++ )
	{
		buffer.clear();
		buffer = byteify( keyFile[ k ].get(), sizeof( Key ));
		outData.insert( outData.end(), buffer.begin(), buffer.end());
	}
	return outData;
}
