#include "../classes/rotor.hh"

#include "../includes/basicSys.hh"
#include "../includes/interface.hh"
#include "../includes/keyfile.hh"

#include <iostream>
#include <string>

using namespace RotorXor;
const char CharSet::FIRST = ' ';
const char CharSet::LAST = '_';

typedef KeyFile::Key Key;

/**
 *	
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

	Rotor rotor;

	rotor.init( newKey );

	std::cout << rotor.getWire() << std::endl;

	char inChar = 'A';

	for ( int i = 0; i < 10; i++ )
	{
		char ciphChar = rotor.encode( inChar );
		char outChar = rotor.decode( ciphChar );

		std::cout << rotor.getPos() << ": " << inChar << " -> " << ciphChar << " -> " << outChar << std::endl;
		rotor.advance();
	}
	return 0;
}
