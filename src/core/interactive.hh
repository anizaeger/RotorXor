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
 * @brief Header file for interactive components of the RotorXor UI
 *
 */
#ifndef ROTORXOR_INTERACTIVE_HH
#define ROTORXOR_INTERACTIVE_HH

namespace RotorXor
{
	/*
	 * MENUS
	 */
	int doMainMenu( int );							///< Main Menu
	int doConfMenu( int );							///< Configuration Menu
	int doKeyMenu( int );							///< Key Management Menu
	int doCipherMenu( int );						///< Cipher Operations Menu

	/*
	 * ROTORXOR CONFIGURATION
	 */
	void rxInit();
	void rxConf();

	/*
	 * KEYFILE MANAGEMENT
	 */
	void impKey();
	void printKeyData();
	void expKey();

	/*
	 * CIPHER OPERATIONS
	 */
	void encrypt();
	void decrypt();
}

#endif /* ROTORMITE_INTERACTIVE_HH */
