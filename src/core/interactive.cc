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

#include "../includes/menu.hh"
#include <iostream>
#include <string>

using namespace RotorXor;

/**
 * Print the main menu, request user input, and redirect control to the proper
 * destination.
 *
 * @param menuTier Assigned tier level for this menu.
 *
 * @return Menu tier level to return control to.
 */
int RotorXor::doMainMenu( int menuTier )
{
	int destMenuTier = menuTier;
	MenuData mainMenuData;
	mainMenuData.title = "Main Menu";
	mainMenuData.menuItems = {
		{ "a", "Configure Rotormite" },
		{ "b", "Key Management" },
		{ "c", "Encode/Decode" },
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
				destMenuTier = doKeyMenu( menuTier - 1 );
				break;
				case 2:
				destMenuTier = doCipherMenu( menuTier - 1 );
				break;
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
int RotorXor::doConfMenu( int menuTier )
{
	int destMenuTier = menuTier;
	MenuData confMenuData;
	confMenuData.title = "RotorXor Configuration Menu";
	confMenuData.menuItems = {
		{ "a", "Set Rotor Count" },
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
int RotorXor::doKeyMenu( int menuTier )
{
	int destMenuTier = menuTier;
	MenuData keyMenuData;
	keyMenuData.title = "Key Management Menu";
	keyMenuData.menuItems = {
		{ "a", "Generate Keychain" },
		{ "b", "Import Keychain" },
		{ "c", "Export Keychain" },
		{ "d", "Keychain Information" },
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
				break;
				case 1:
				break;
				case 2:
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
int RotorXor::doCipherMenu( int menuTier )
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
				break;
				case 1:
				break;
				default:
				break;
			}
		}
	}
	return destMenuTier;
}
