/********************************************************************************
 *                                                                              *
 * Basic file manipulation functions.                                           *
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
 * @brief Header file for basic file manipulation functions.
 *
 */
#ifndef NYFNET_FILEIO_H
#define NYFNET_FILEIO_H

#include <fstream>
#include <string>

/// Opens a file for output.
bool fileOpenOut( const std::string&, std::ofstream& );

/// Opens a file for input.
bool fileOpenIn( const std::string&, std::ifstream& );

/// Automatically generates a new filename.
bool newFilename( const std::string&, const std::string&, const std::string&, std::string& );


#endif /* NYFNET_FILEIO_H */
