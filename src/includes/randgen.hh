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
 * @brief Header file for RandGen class.
 *
 */
#ifndef RANDGEN_H
#define RANDGEN_H

#include "keyfile.hh"

#include <iostream>
#include <random>

/// Class implementing a Blum Blum Shub CSPRNG.
class RandGen {
public:
	typedef bool Bit;							///< An alias to bool, for use to store the value of data bits.
	typedef unsigned char Byte;						///< An alias to unsigned chars, for use to store raw data.
	typedef unsigned short Prime;						///< Type of value to use for CSPRNG primes.
	typedef unsigned Seed;							///< Type for the product of 2 values of type Prime.
	typedef unsigned long RR;						///< Type for the product of 2 values of type Seed.

	/// Clear all seed data when destroying RandGen.
	inline ~RandGen() {
		m = 0; r = 0, s = 0;
	}

	/// Extract data from a Key and load it into the CSPRNG object.
	inline void setKey( const KeyFile::Key* const key ) {
		setPrimes( key->p, key->q );
		setSeed( key->s );
		reset();
	}

	/// Generate a random bit.
	/**
	 * @return A random bit.
	 */
	inline Bit getRandBit() {
		return (bool)( getRandNum() % 2 );
	}

	/// Generate a random byte.
	/**
	 * @return A random byte.
	 */
	inline Byte getRandByte() {
		return (unsigned char)( getRandRange( 0, 0xFF ));
	}

	/// Generate a random number.
	/**
	 * @return A random number.
	 */
	inline Seed getRandNum() {
		step();
		return r;
	}

	/// Return the largest value that this instance of the CSPRNG can generate.
	/**
	 * @return Max possible value, m - 1.
	 */
	inline Seed rand_max() {
		return ( this->m - 1 );
	}

	/// Generate a random number within a given range.
	Seed getRandRange( unsigned, unsigned );

	/// Reset the CSPRNG to its initial seeded state.
	inline void reset() {
		this->r = this->s;
	}

	/// Temporarily change the seed value of the CSPRNG.
	inline void reset( Seed s ) {
		this->r = s;
	}

	/// Set the default seed value.
	inline void setSeed( Seed s ) {
		this->s = s;
	}
private:
	Seed m = 0;	///< The maximum value that should be generated.  This should be the product of 2 prime numbers.
	Seed r = 0;	///< The last randomly-generated number.
	Seed s = 0;	///< Seed value.  This should be less than m.

	inline void setPrimes( Prime p, Prime q ) {
		this->m = (Seed)p * q;
	}

	inline void step() {
		r =  ((RR)r * r ) % m;
	};
};

#endif /* RANDGEN_H */
