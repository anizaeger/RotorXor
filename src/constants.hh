/********************************************************************************
 *                                                                              *
 * Copyright (C) 2018 by Anakin-Marc Zaeger                                     *
 * All Rights Reserved                                                          *
 *                                                                              *
 * This file is part of RotorXor.                                               *
 *                                                                              *
 * RotorXor is free software: you can redistribute it and/or modify             *
 * it under the terms of the GNU General Public License as published by         *
 * the Free Software Foundation, either version 3 of the License, or            *
 * (at your option) any later version.                                          *
 *                                                                              *
 * RotorXor is distributed in the hope that it will be useful,                  *
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
 * @brief Various constants contained in source and shared with includes.
 *
 */
#ifndef ROTORXOR_CONSTANTS_H
#define ROTORXOR_CONSTANTS_H

#include <string>

// Preprocessor macros to stringify Makefile-provided constants.
//! \{
#define STRINGIFY(x) #x
#define STRINGIFYMACRO(y) STRINGIFY(y)
//! \}

/// Executable name - Preprocessor define P_EXEC should be set in Makefile
const char PROGEXEC[] = STRINGIFYMACRO(P_EXEC);

/// Program name - Preprocessor define P_NAME should be set in Makefile
const char PROGNAME[] = STRINGIFYMACRO(P_NAME);

/// Programmer
const char PROGRAMMER_NAME[] = "Anakin-Marc Zaeger";

/// Major version number
#define MAJOR 0
const int V_MAJOR = MAJOR;			///< Major version number

/// Minor version number
#define MINOR 1
const int V_MINOR = MINOR;			///< Minor version number

/// Full version number - Preprocessor define P_VERSION should be generated and set in Makefile
const char VERSION[] = STRINGIFYMACRO(P_VERSION);

/// Complete program version text string for display
const std::string PROGVER = std::string( PROGEXEC ) + " (" + std::string( PROGNAME ) + ") " + std::string( VERSION );



#endif /* ROTORXOR_CONSTANTS_H */
