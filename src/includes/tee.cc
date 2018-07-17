/********************************************************************************
 *                                                                              *
 * Send streams to be sent to multiple destinations.                            *
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
 * @brief Source code for Tee class.
 *
 */
#include "tee.hh"

#include <stdarg.h>

/**
 * Constructor to set output stream destinations.
 *
 * @param firstStream The first outgoing stream.
 * @param ... Any additional outgoing streams.  The final stream MUST be nullptr.
 */
Tee::Tee( std::ostream* firstStream, ... ) {
	numStreams = 0;
	// Set first output stream destination.
	std::ostream* streamPtr = firstStream;
	outStreams.push_back( streamPtr );

	// Set remaining output stream destinations.
	va_start( streamList, firstStream );
	while ( (streamPtr = va_arg( streamList, std::ostream* )) != nullptr ) {
		outStreams.push_back( streamPtr );
	}
	va_end( streamList );

	// Set number of streams to the size of outStreams vector.
	numStreams = outStreams.size();
}
