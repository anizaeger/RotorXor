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
 * @brief Source code for Menu class.
 *
 */
#include "menu.hh"
#include "../constants.hh"

#include "basicSys.hh"

#include <iostream>
#include <string>
#include <vector>

/**
 * Constructor for struct MenuData
 * Sets default values
 */
MenuData::MenuData() {
	// Initialize struct default values
	headerChar = '-';
	title = "MENU";
}

/**
 * Sets initial values for various Menu members
 *
 * @param menuData Data for the menu.
 */
Menu::Menu( const MenuData& menuData ) : menuData(menuData) {
	progName = PROGNAME;
	progName += ", v";
	progName += std::to_string( V_MAJOR );
	progName += '.';
	progName += std::to_string( V_MINOR );
	progName += '.';
	progName += std::to_string( V_REVISION );
	titleLen = menuData.title.length();
	prognameLen = progName.length();
	authorLen = strlen ( PROGRAMMER_NAME );

	// Calculate width of menu header
	if ( titleLen > prognameLen )
	{
		headerWidth = titleLen;
	}
	else
	{
		headerWidth = prognameLen;
	}
	headerWidth *= 2;

	prognameIndent = ( headerWidth / 2 ) - ( prognameLen / 2 );
	authorIndent = ( headerWidth / 2 ) - ( authorLen / 2 );
	titleIndent = ( headerWidth / 2 ) - ( titleLen /2 );

	numItems = menuData.menuItems.size();

	for ( int opt = 0; opt < numItems; opt++ )
	{
		menuOpt.push_back( menuData.menuItems[ opt ][ 0 ]);
		menuDesc.push_back( menuData.menuItems[ opt ][ 1 ]);
	}
}

/**
 * Add menu item to menu including a function pointer.
 *
 * @param choice A character representing the menu choice.
 * @param desc A description of the menu choice.
 * @param funcPtr A pointer to the function to be executed by the menu.
 *
 * @warning This is a future feature and, as of yet, is non-functional.
 */
void
add( const char choice, const std::string desc, const MenuFunc funcPtr )
{
	
}

/**
 * Add menu item to menu including a function pointer.
 *
 * @param choice A character representing the menu choice.
 * @param desc A description of the menu choice.
 * @param command A command to be executed by the menu.
 *
 * @warning This is a future feature and, as of yet, is non-functional.
 */
void
add( const char choice, const std::string desc, const std::string command )
{
	
}
/**
 * Print menu to screen; get, validate, and return user choice
 *
 * @return Character representing choice made by user
 */
int
Menu::doMenu() const
{
	clearScreen();
	printMenu();
	return getChoice();
}

/**
 * Print menu based on data contained within struct MenuData
 */
void
Menu::printMenu() const
{
	clearScreen();
	// Print menu header
	for ( int i = 0; i < headerWidth; i++ )
	{
		printf("%c", menuData.headerChar );
	}
	printf( "\n");
	printf( "%*c%s\n", prognameIndent, ' ', progName.c_str());
	printf( "%*c%s\n", authorIndent, ' ', PROGRAMMER_NAME );
	printf( "%*c%s\n", titleIndent, ' ', menuData.title.c_str());
	for ( int i = 0; i < headerWidth; i++ )
	{
		printf("%c", menuData.headerChar );
	}
	printf( "\n\n\n");

	// Print Menu Options
	for ( unsigned int choiceIdx = 0; choiceIdx < numItems; choiceIdx++ )
	{
		printf( "%c%-7s%*s\n\n", toupper((char)*menuOpt[ choiceIdx ].c_str()), ":\\>", ( headerWidth - 8 ), menuDesc[ choiceIdx ].c_str());
	}
	printf( "\n" );
	for ( int i = 0; i < headerWidth; i++ )
	{
		printf("%c", menuData.headerChar );
	}
	printf( "\n");
}

/**
 * Request user choice, validate choice against accepted values, return valid choice.
 *
 * @return Character representing choice made by user
 */
int
Menu::getChoice() const
{
	char choice = '\0';

	char prompt[ 128 ];
	sprintf( prompt, "Enter your choice [" );
	for ( unsigned int choiceIdx = 0; choiceIdx < numItems; choiceIdx++ )
	{
		sprintf( prompt + strlen ( prompt ), " %c", (char)*menuOpt[ choiceIdx ].c_str());
	}
	sprintf( prompt + strlen ( prompt ), " ]: " );

	int validChoice = -1;

	do {
		printf( "%s", prompt );

		std::cin.get(choice);
		choice = tolower( choice );
		for ( unsigned int choiceIdx = 0; choiceIdx < numItems; choiceIdx++ )
		{
			if ( choice == tolower( (char)*menuOpt[ choiceIdx ].c_str()))
			{
				validChoice = choiceIdx;
				choiceIdx = numItems;
			}
		}
		if ( validChoice < 0 )
		{
			printf( "\n*** INVALID CHOICE ***\n\n" );
		}
		clearBuffer();
	} while ( validChoice < 0 );
	return validChoice;
}
