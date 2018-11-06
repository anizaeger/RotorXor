#include "../classes/scrambler.hh"

#include "../includes/basicSys.hh"
#include "../includes/interface.hh"
#include "../includes/keyfile.hh"

#include <iostream>
#include <string>

using namespace RotorXor;
const char CharSet::FIRST = ' ';
const char CharSet::LAST = '_';

typedef KeyFile::Key Key;
typedef std::vector< Key* > KeyVec;

/**
 *	
 */
int
main( void )
{
	KeyFile keychain;
	int numRotors = 0;

	if ( choiceBool( "Generate keys" ))
	{
		numRotors = choiceNum( "How many rotors", 2, 8 );
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
	Scrambler scrambler;

	std::vector< bool > steps = { 1, 1, 0, 0, 1, 0, 0, 1 };

	for ( int i = 0; i < keychain.numKeys(); i++ )
	{
		keyVec.push_back( keychain.getKey( i ));
	}

	scrambler.setKey( keyVec );

	for ( int i = 0; i < 100; i++ )
	{
		std::cout << scrambler.rotPos() << ": " << scrambler.genChar() << std::endl;
		scrambler.step( steps );
	}

	return 0;
}
