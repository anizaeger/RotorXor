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
 * @brief Header file for Menu class.
 *
 */
#ifndef NYFNET_MENU_H
#define NYFNET_MENU_H

#include <string>
#include <vector>

/// Type for menu function pointers.
typedef int ( *MenuFunc )( int );

/// Contains data to be passed to Menu class constructor
struct MenuData
{
	std::string title;							///< The title of the menu.
	char headerChar;							///< The type of character to use for header borders.
	std::vector< std::vector< std::string > > menuItems;			///< Choice character and descriptions for menu items.

	MenuData();								///< Initialize members of structure.
};

/// A basic menu interface generator.
class Menu
{

public:
	Menu( const struct MenuData& menuData );				///< Constructor for class Menu.
	void add( const char, const std::string, const MenuFunc );		///< Add menu item with function pointer.
	void add( const char, const std::string, const std::string );		///< Add menu item with class command.
	int doMenu() const;							///< Generate menu and request user input.

private:
	std::string progName;
	int titleLen;
	int prognameLen;
	int authorLen;
	int headerWidth;
	size_t numItems;
	int titleIndent;
	int authorIndent;
	int prognameIndent;
	MenuData menuData;

	std::vector< std::string > menuOpt;
	std::vector< std::string > menuDesc;

	void printMenu() const;
	int getChoice() const;

};

#endif /* NYFNET_MENU_H */
