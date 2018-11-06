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
 * @brief Source code for the RotorXor Resource Managememt Module.
 *
 */

#include "rxMngr.hh"

using namespace RotorXor;

/// Keys for the CSPRNG.
typedef KeyFile::Key Key;

RxMngr::RxMngr()
{
	
}

void
RxMngr::init( const int numRotors )
{
	wipe();
	handler = new Handler( numRotors );
	handler->genKeys();
}

void
RxMngr::init( const std::string& keyTxt )
{
	KeyFile::impKey( keyTxt );
	init( KeyFile::getKeys());
}

void
RxMngr::init( KeyVec keyData )
{
	wipe();
	handler = new Handler( keyData );
}

std::string
RxMngr::encode( const std::string& inString )
{
	std::string outString = "";
	if ( handler ) {
		outString = handler->encode( inString );
	}
	return outString;
}

std::string
RxMngr::decode( const std::string& inString )
{
	std::string outString = "";
	if ( handler ) {
		outString = handler->decode( inString );
	}
	return outString;
}

std::string
RxMngr::cipher( const std::string& inString )
{
	std::string outString = "";
	if ( handler ) {
		outString = handler->cipher( inString );
	}
	return outString;
}