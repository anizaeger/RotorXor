/********************************************************************************
 * An implementation of the Blum Blum Shub CSPRNG                               *
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
 * @brief Source code for interactive components of the RotorXor UI.
 *
 */
#include "interactive.hh"
#include "core.hh"

#include "../includes/basicSys.hh"
#include "../includes/interface.hh"
#include "../includes/menu.hh"

#include <iostream>
#include <string>

/********************************************************************************
 * MENUS                                                                   *
 ********************************************************************************/

/**
 * Print the main menu, request user input, and redirect control to the proper
 * destination.
 *
 * @param menuTier Assigned tier level for this menu.
 *
 * @return Menu tier level to return control to.
 */
int
RotorXor::doMainMenu( int menuTier )
{
	int destMenuTier = menuTier;
	MenuData mainMenuData;
	mainMenuData.title = "Main Menu";
	mainMenuData.menuItems = {
		{ "a", "RotorXor Configuration" },
		{ "b", "Encode/Decode" },
		{ "c", "Manage Keychain" },
		{ "x", "Exit Program" }
	};

	Menu mainMenu( mainMenuData );
	while ( destMenuTier == menuTier )
	{
		int choice = mainMenu.doMenu();

		if ( choice == ( mainMenuData.menuItems.size() - 1 ))
		{
			destMenuTier++;
		}
		else
		{
			switch( choice )
			{
				case 0:
				destMenuTier = doConfMenu( menuTier - 1 );
				break;
				case 1:
				destMenuTier = doCipherMenu( menuTier - 1 );
				break;
				case 2:
				destMenuTier = doKeyMenu( menuTier - 1 );
				default:
				break;
			}
		}
	}
	return destMenuTier;
}


/**
 * Print the configuration menu, request user input, and redirect control to the
 * proper destination.
 *
 * @param menuTier Assigned tier level for this menu.
 *
 * @return Menu tier level to return control to.
 */
int
RotorXor::doConfMenu( int menuTier )
{
	int destMenuTier = menuTier;
	MenuData confMenuData;
	confMenuData.title = "RotorXor Configuration Menu";
	confMenuData.menuItems = {
		{ "a", "Set Rotors" },
		{ "b", "Display Rotor Configuration" },
		{ "r", "Return to Previous Menu" },
		{ "x", "Exit Program" }
	};

	Menu confMenu( confMenuData );
	while ( destMenuTier == menuTier )
	{

		int choice = confMenu.doMenu();

		if ( choice == ( confMenuData.menuItems.size() - 1 ))
		{
			destMenuTier = 0;
		}
		else if ( choice == ( confMenuData.menuItems.size() - 2 ))
		{
			destMenuTier++;
		}
		else
		{
			switch( choice )
			{
				case 0:
					rxInit();
					break;
				case 1:
					rxConf();
					break;
				default:
					break;
			}
		}
	}
	return destMenuTier;
}

/**
 * Print the key management menu, request user input, and redirect control to
 * the proper destination.
 *
 * @param menuTier Assigned tier level for this menu.
 *
 * @return Menu tier level to return control to.
 */
int
RotorXor::doKeyMenu( int menuTier )
{
	int destMenuTier = menuTier;
	MenuData keyMenuData;
	keyMenuData.title = "Key Management Menu";
	keyMenuData.menuItems = {
		{ "a", "Import Base64 Keychain" },
		{ "b", "Print Key Data" },
		{ "c", "Export Base64 Keychain" },
		{ "r", "Return to Previous Menu" },
		{ "x", "Exit Program" }
	};

	Menu keyMenu( keyMenuData );
	while ( destMenuTier == menuTier )
	{

		int choice = keyMenu.doMenu();

		if ( choice == ( keyMenuData.menuItems.size() - 1 ))
		{
			destMenuTier = 0;
		}
		else if ( choice == ( keyMenuData.menuItems.size() - 2 ))
		{
			destMenuTier++;
		}
		else
		{
			switch( choice )
			{
				case 0:
					impKey();
					break;
				case 1:
					printKeyData();
					break;
				case 2:
					expKey();
					break;
				default:
					break;
			}
		}
	}
	return destMenuTier;
}

/**
 * Print the cipher operations menu, request user input, and redirect control to
 * the proper destination.
 *
 * @param menuTier Assigned tier level for this menu.
 *
 * @return Menu tier level to return control to.
 */
int
RotorXor::doCipherMenu( int menuTier )
{
	int destMenuTier = menuTier;
	MenuData cipherMenuData;
	cipherMenuData.title = "Cipher Ops Menu";
	cipherMenuData.menuItems = {
		{ "a", "Encrypt Plaintext" },
		{ "b", "Decrypt Base64 Ciphertxt" },
		{ "r", "Return to Previous Menu" },
		{ "x", "Exit Program" }
	};

	Menu cipherMenu( cipherMenuData );
	while ( destMenuTier == menuTier )
	{
		int choice = cipherMenu.doMenu();

		if ( choice == ( cipherMenuData.menuItems.size() - 1 ))
		{
			destMenuTier = 0;
		}
		else if ( choice == ( cipherMenuData.menuItems.size() - 2 ))
		{
			destMenuTier++;
		}
		else
		{
			switch( choice )
			{
				case 0:
					encrypt();
					break;
				case 1:
					decrypt();
					break;
				default:
				break;
			}
		}
	}
	return destMenuTier;
}

/********************************************************************************
 * ROROTXOR CONFIGURATION                                                       *
 ********************************************************************************/
/**
 * UI initializing RotorXor.
 */
void
RotorXor::rxInit()
{
	int numRotors = choiceNum( "How many rotors", 1, 64 );
	rxMngrPtr->init( numRotors );
}

/**
 * Print RotorXor Configuration.
 */
void
RotorXor::rxConf()
{
	std::cout << "Number of rotors: " << rxMngrPtr->numRotors() << std::endl;
	pauseKey();
}
/********************************************************************************
 * KEY MANAGEMENT                                                               *
 ********************************************************************************/
/**
 * UI for generating keychain based on current RotorXor Configuration.
 */

/**
 * UI for importing a keychain.  Will also resize scramblers if necessary.
 */
void
RotorXor::impKey()
{
	std::string inData;
	std::cout << "Please enter your key's base64 string now: " << std::endl;
	std::cin >> inData;
	clearBuffer();

	rxMngrPtr->init( inData );
	printf( "Checksum: 0x%X\n", KeyFile::checksum());
	pauseKey();
}
/**
 * UI for exporting a keychain.
 */
void
RotorXor::expKey()
{
	std::cout << KeyFile::expKey() << std::endl;
	pauseKey();
}

/**
 * UI for displaying information regarding currently-loaded keychain.
 */
void
RotorXor::printKeyData()
{
	// Display key checksum.
	printf( "Checksum: 0x%X\n", KeyFile::checksum());
	// Display information about scramblers, rotors, generators, etc...
	KeyFile::printKeys();
	pauseKey();
}
/********************************************************************************
 * CIPHER OPERATIONS                                                            *
 ********************************************************************************/
/**
 * UI for encrypting plaintext and returning base64-encoded ciphertext.
 */
void
RotorXor::encrypt()
{
	std::string inString, outData;
	std::cout << "Enter the plaintext to be encrypted: ";
	std::getline( std::cin, inString );
	outData = rxMngrPtr->encode( inString );
	std::cout << outData << std::endl;
	pauseKey();
}
/**
 * UI for decrypting base64-encoded ciphertext and returning plaintext.
 */
void
RotorXor::decrypt()
{
	std::string inData, outString;
	std::cout << "Enter the cipher data to be decrypted: ";
	std::getline( std::cin, inData );
	outString = rxMngrPtr->decode( inData );
	std::cout << outString << std::endl;
	pauseKey();
}