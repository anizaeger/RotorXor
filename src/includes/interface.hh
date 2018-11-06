/********************************************************************************
 * Various functions regarding program UI                                       *
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
 * @brief Header file for various functions regarding program UI.
 *
 */
#ifndef NYFNET_INTERFACE_H
#define NYFNET_INTERFACE_H

#define DEFAULT_SIZE 3								///< Default number of digits between thousands seperators.
#define DEFAULT_SYM ','								///< Default character to use as thousands seperator.

#include <ostream>
#include <vector>

// User choice interface
bool choiceBool(const char*, const char = 'Y' , const char = 'N' );
int choiceNum( const char*, const int, const int );

char* prettyNum( long double, char*, const int, const int = DEFAULT_SIZE, const char = DEFAULT_SYM );

#endif /* NYFNET_INTERFACE_H */
