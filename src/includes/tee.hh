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
 * @brief Header file for Tee class.
 *
 */
#ifndef NYFNET_TEE_H
#define NYFNET_TEE_H

#include <ostream>
#include <vector>


/// Class to split output stream between multiple destinations.
class Tee {
public:
	///< Default constructor.
	Tee( std::ostream*, ... );

	/// Function template to accept buff, send to *outStreams[ streamNum ], then return buff.
	template< class T > inline Tee&
	operator<< (const T& buff)
	{
		for ( unsigned int streamNum = 0; streamNum < numStreams; streamNum++ )
		{
			*outStreams[ streamNum ] << buff;
		}
		return *this;
	}

	/// Function signature of std::basic_ostream
	typedef std::basic_ostream< char, std::char_traits < char > > OutFileType;

	/// Function signature of stream functions (eg. std::endl, std::flush)
	typedef OutFileType&( *StreamFunc )( OutFileType& );

	/**
	 * Overloaded operator<< for stream functions
	 */
	inline Tee&
	operator<<( Tee::StreamFunc manip )
	{
		// Call StreamFunc(manip), then flush stream.
		for ( unsigned int streamNum = 0; streamNum < Tee::numStreams; streamNum++ )
		{
			manip(*outStreams[ streamNum ]);
			outStreams[ streamNum ]->flush();
		}

		// Return result from StreamFunc.
		return *this;
	}
private:
	size_t numStreams;							///< Number of outgoing streams.
	va_list streamList;							///< List of stream destinations.
	
	/// Output stream destinations
	std::vector<std::ostream*> outStreams;
};

#endif /* NYFNET_TEE_H */
