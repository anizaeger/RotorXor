#include "../classes/xorer.hh"

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
	Xorer* xorer;

	int numRotors = 0;

	if ( choiceBool( "Generate keys" ))
	{
		numRotors = choiceNum( "How many rotors", 2, 8 );
		xorer = new Xorer( numRotors );
		xorer->genKeys(); 
		std::cout << KeyFile::expKey() << std::endl;
	}
	else
	{
		std::string inData;
		std::cout << "Please enter your key's base64 string now: ";
		std::cin >> inData;

		KeyFile::impKey( inData );

		KeyVec keyVec = KeyFile::getKeys();
		xorer = new Xorer( keyVec );
	}

	KeyFile::printKeys();

	srand( 17 );

	std::vector< char > inChar;
	std::vector< char > cipherChar;
	std::vector< char > outChar;
	std::vector< std::string > sPos;
	std::vector< std::string > pPos;

	int numA = (int)'A';
	int numZ = (int)'Z';

	for ( int i = 0; i < 100; i++ )
	{
		sPos.push_back( xorer->sRot());
		pPos.push_back( xorer->pRot());
		char rndChar = ( rand() % ( numZ - numA + 1 )) + numA;
		inChar.push_back( rndChar );
		cipherChar.push_back( xorer->encode( inChar[ i ] ));
		xorer->step();
	}

	xorer->reset();
	for ( int i = 0; i < cipherChar.size(); i++ )
	{
		outChar.push_back( xorer->encode( cipherChar[ i ] ));
		std::cout << sPos[ i ] << ", " << xorer->sRot() << " - "<< inChar[ i ] << " -> " << cipherChar[ i ] << " -> " << outChar[ i ] << " - " << pPos[ i ] << ", " << xorer->pRot() << std::endl;
		xorer->step();
	}

	return 0;
}
