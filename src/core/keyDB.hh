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
 * @brief Header file for key manager.
 *
 */
#ifndef ROTORXOR_KEYMNGR
#define ROTORXOR_KEYMNGR

#include "../includes/keyfile.hh"

#include <string>
#include <vector>

namespace RotorXor
{
	class KeyRec {
	public:
		KeyRec( std::vector< unsigned char >& );
	private:
		
	};

	class KeyDB {
	public:
	private:
		std::vector< KeyRec* > keyDB;
	};
}

#endif /* ROTORXOR_KEYMNGR */
