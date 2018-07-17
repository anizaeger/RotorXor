/********************************************************************************
 *                                                                              *
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
 * @brief Header file for KeyFile class.
 *
 */
#ifndef NYFNET_KEYFILE_HH
#define NYFNET_KEYFILE_HH

#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

/// A very basic database for Blum Blum Shub CSPRNG keys.
class KeyFile {
#define KEYSIZE sizeof( Key )							///< The size of an initialized Key in bytes.
public:
	/// Type for Primes.
	typedef unsigned short Prime;
	/// Type for Seeds.
	typedef unsigned Seed;

#pragma pack( push, 1 )
	/// Blum Blum Shub CSPRNG Key.
	struct Key {
		Prime p;							///< First Prime for CSPRNG.
		Prime q;							///< Second Prime for CSPRNG.
		Seed s;								///< Seed for CSPRNG.

		/// Wipe all key values before destroying object.
		inline ~Key() {
			p = 0, q = 0, s = 0;
		}
	};
#pragma pack( pop )

	static Key* genKey();							///< Generate new key, and append it to keyFile.

	static std::vector< Key* > genKeys( int num );				///< Generate new keys, and append them to keyFile.

	static std::string expKey();						///< Exports keyFile as base64 string.
	static void impKey( const std::string& );				///< Imports keyFile as base64 string.

	static Key* const getKey( const int );					///< Returns a pointer to a specific key.
	static std::vector< Key* > getKeys();					///< Returns keyFile as a vector of pointers.
	static void printKeys();						///< Print keychain to screen.

	static unsigned checksum();						///< Generate and return the crc64 checksum for the keychain.

	/// Return the number of keys in the keyFile.
	static inline size_t numKeys() {
		return keyFile.size();
	}

	/// Wipes keyFile.
	inline static void clear() {
		keyFile.clear();
	}
private:
	static std::vector< std::unique_ptr< Key > > keyFile;
	static std::random_device keyGen;

	static std::vector< unsigned char > keyFileBytes();

	static Prime genPrime();
	static Seed  genSeed( const Prime, const Prime );

	static bool isBlum( const Prime );
	static bool isPrime( const Prime );
};

#endif /* NYFNET_KEYFILE_HH */
