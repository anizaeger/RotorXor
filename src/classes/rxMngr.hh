/********************************************************************************
 * RotorXor Resource Managememt Module                                          *
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
 * @brief Header file for the RotorXor Resource Managememt Module.
 *
 */

#ifndef ROTORXOR_MANAGEMENT_H
#define ROTORXOR_MANAGEMENT_H

#include <string>

#include "handler.hh"

#include "../includes/keyfile.hh"

namespace RotorXor
{
	typedef KeyFile::Key Key;			///< Individual keys.
	typedef std::vector< Key* > KeyVec;		///< Vector of pointers to keys.
	class RxMngr {
	public:
		/// Default constructor for RotorXor.
		RxMngr();

		/// Delete memory allocation for handler.
		inline ~RxMngr()
		{
			wipe();
		}

		/*
		 * Initialize RotorXor with a new key and rotor set.
		 */
		void init( const int );						///< Initialize blank rotor, and generate a new key.
		void init( const std::string& );				///< Initialize using base64-encoded key.
		void init( const KeyVec );					///< Initialize with raw binary key data.

		inline int numRotors() { return handler->numRotors(); }		///< Return the number of RotorXor rotors.

		std::string encode( const std::string& );

		std::string decode( const std::string& );

		std::string cipher( const std::string& );

	private:
		Handler* handler = nullptr;

		inline void wipe()
		{
			if ( handler ) {
				delete handler;
				handler = nullptr;
			}
		}
	};
}

#endif /* ROTORXOR_MANAGEMENT_H */
