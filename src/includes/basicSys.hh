/********************************************************************************
 *                                                                              *
 * Various helper functions.                                                    *
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
 * @brief Header file for various helper functions.
 *
 */

#ifndef NYFNET_BASICSYS_H
#define NYFNET_BASICSYS_H

#include <memory>
#include <string>

// Clear input/output
void clearScreen( void );
void clearBuffer( void );

// Pause program execution
void pauseTime( int );
void pauseKey( const char* = "Press [ ENTER ] to continue..." );

// Basic information
std::string rprintf( const char*, ... );
std::string genTimeStamp( std::string = "%Y-%m-%dT%H:%M:%S%z" );

void printError( const int, const char*, ... );
extern void show_usage ( const int = 0 );					///< Prints command-line usage information to screen.
void show_version();
void show_lic_notice();
void show_banner();
void show_license();
void show_copying();
void show_warranty();
void show_gpl();
void endProg( int = 0 );

#endif /* NYFNET_BASICSYS_H */
