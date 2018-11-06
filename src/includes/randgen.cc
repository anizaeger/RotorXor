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
 * @brief Source code for RandGen class.
 *
 */
#include "randgen.hh"


/**
 * @param min The inclusive minimum value to return.
 * @param max The exclusive maximum value to return.
 *
 * @return A random number between min inclusive and max exclusive.
 * DEFAULT: false
 *
 * The procedure used to generate the random number is designed to nullify
 * modulus bias, and is based on the code provided by:@n
 * https://zuttobenkyou.wordpress.com/2012/10/18/generating-random-numbers-without-modulo-bias/
 */
KeyFile::Seed
RandGen::getRandRange( const Seed min, const Seed max )
{
	/**
	 * Calculate modulus value for the random number generator.  This step
	 * is the same as is typically done to get a random number in a range.
	 */
	Seed randMod = ( max ) - min;

	/**
	 * Then determine how many possible random numbers can contribute to a
	 * modulus bias.
	 */
	Seed randOver = ( rand_max() % randMod ) + 1;

	/**
	 * The value calculated for randOver will have no effect if any of the
	 * following conditions are met:
	 * - randOver is equal to the modulus value.
	 * - randOver is greater than the maximum value that can be generated
	 * by the CSPRNG.
	 * - randMod is greater than the maxumum value that can be generated by
	 * the CSPRNG.
	 *
	 * If any of these conditions are true, randOver is nullified.
	 */
	if ( randOver == randMod || randOver > rand_max() || randMod > rand_max() ) {
		randOver = 0;
	}

	/**
	 * Set an artificial limit for results from the CSPRNG by subtracting
	 * randOver from rand_max.
	 */
	Seed randLimit = rand_max() - randOver;

	/**
	 * Generate random numbers until the random number generated is less
	 * than the artificial limit.
	 */
	Seed preRand;
	do {
		preRand = getRandNum();
	} while ( preRand > randLimit );

	/**
	 * Finally, calculate the remainder of preRand mod randMod, add min, and
	 * return.
	 */
	Seed randTerm = ( preRand % randMod ) + min;
	return randTerm;
}
