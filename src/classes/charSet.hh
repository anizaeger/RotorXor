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
 * @brief Header file for CharSet class.
 *
 */
#ifndef ROTORXOR_CHARSET_H
#define ROTORXOR_CHARSET_H

#include <cstddef>

/// Project namespace.
namespace RotorXor
{
	/// Character set class
	/**
	 * The Rotormite character set is automatically generated when it is
	 * provided with a FIRST and LAST character value.  Rotormite assumes,
	 * or rather, requires, that the characters provided are the ends of a
	 * continuous set of consecutive ASCII values.
	 */
	class CharSet
	{
	public:
		static const char FIRST;		///< First character in set.
		static const char LAST;			///< Final character in set.

		static char pos2val( int );		///< Converts numeric identifier to character.
		static int val2pos( const char );	///< Converts character to numeric identifier.

		/// Returns the number of characters contained within the set.
		/**
		 * @return The number of characters in the character set.
		 */
		static inline size_t
		getLen()
		{
			return (((int)LAST - (int) FIRST ) + 1 );
		}
	};

}
#endif /* ROTORXOR_CHARSET_H */
