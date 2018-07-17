/********************************************************************************
 *                                                                              *
 * A simple base64 converter.                                                   *
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
 * @author Unknown, public domain.
 * Based on code originally made available online at:
 * https://en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64
 *
 * @brief Header file for base64 converter.
 *
 */
#ifndef NYFNET_BASE64_H
#define NYFNET_BASE64_H

#include <vector>
#include <string>

//! \{
#define TCHAR char
#define TEXT(x) x
#define DWORD long
#define BYTE unsigned char
//! \}

/// Lookup table for encoding.  If you want to use an alternate alphabet, change the characters here.
const static TCHAR encodeLookup[] = TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");

const static TCHAR padCharacter = TEXT('=');					///< Character to use for padding base64 string.

std::basic_string< TCHAR > base64Encode(std::vector< BYTE > inputBuffer);	///< Encode data as a base64 string.
std::vector< BYTE > base64Decode(const std::basic_string< TCHAR >& input);	///< Decode a base64 string into a char vector.

/**
 * Takes a type of data as input, breaks it into bytes
 * @param inData Data to be converted into bytes.
 * @param size Size of data type being bytified.
 */
template< typename T >
std::vector< BYTE > byteify( T* inData, size_t size )
{
	std::vector< BYTE > outData;
	BYTE* dataPtr = (BYTE*)inData;
	for ( int byte = 0; byte < size; byte++ )
	{
		outData.push_back( dataPtr[ byte ]);
	}
	return outData;
}

#endif /* NYFNET_BASE64_H */
