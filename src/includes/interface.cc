/********************************************************************************
 * Various functions regarding program UI                                       *
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
 * @brief Source code for various functions regarding program UI.
 *
 */
#include "interface.hh"

#include "basicSys.hh"

#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/*******************************************************************************
	USER CHOICE INTERFACE - RETURN TYPE: VARIOUS
*******************************************************************************/
/**
 * Prompts user for a true/false response.
 *
 * @return bool values indicate following:
 * true -> First choice.
 * false -> Second choice.
 */
bool
choiceBool ( const char* prompt, const char TVAL, const char FVAL )
{
	char choice = '\0';
	do
	{
		printf( "%s (%c/%c) ", prompt, TVAL, FVAL );
		std::cin.get( choice );
		choice = tolower( choice );
		if ( choice == tolower( TVAL ))
		{
			clearBuffer();
			return true;
		}
		else if ( choice == tolower( FVAL ))
		{
			clearBuffer();
			return false;
		}
		else
		{
			clearBuffer();
			printf( "Invalid choice.\n\n" );
		}
	}
	while ( true );  // All valid non-default cases return to parent function.  Infinate loop intentional.
}

/**
 * Prompts user for a numerical response.
 *
 * @return int value representing user's choice.
 */
int
choiceNum ( const char* prompt, const int minVal, const int maxVal )
{
	int choice;
	do
	{
		printf( "%s [ %i - %i ]: ", prompt, minVal, maxVal );
		std::cin >> choice;
		if ( choice >= minVal && choice <= maxVal )
		{
			clearBuffer();
			return choice;
		}
		else
		{
			printf( "Invalid choice.  Input must be between %i and %i inclusive.\n\n", minVal, maxVal );
		}
		clearBuffer();
	}
	while ( true );  // All valid non-default cases return to parent function.  Infinate loop intentional.
}

/*******************************************************************************
	FORMAT OUTPUT - RETURN TYPE: VARIOUS
*******************************************************************************/
/**
 * Parse an integer and return it with thousands seperators.  Additionally, trim
 * or pad decimal places if requested.
 *
 * @returns string representing number of thousands seperators added
 */
char*
prettyNum ( long double inNum, char* outNum, const int places, const int grpSize, const char grpSym )
{

	outNum[0] = '\0';

	bool isNeg = ( inNum < 0 );	// Is the number negative?
	
	long long intVal = std::abs(( long long )inNum );	// Integer portion of number
	long double decimalVal = std::abs( inNum ) - intVal;	// Decimal portion of number

	char intTxt[32];	// Integer text
	intTxt[0] = '\0';

	char decTxt[32];
	decTxt[0] = '\0';	// Decimal text

	// Create integer portion
	char tmpNum[32];
	sprintf( tmpNum, "%lld", intVal );
	int numDigits = strlen ( tmpNum );	// Number of digits in integer portion

	for ( int digitPos = 0; digitPos < numDigits; digitPos++ )
	{
		char curDigit = tmpNum[ digitPos ];

		// Determine whether or not to place a group seperator
		if ((( numDigits - digitPos ) % grpSize == 0 ) && ( digitPos != 0 ))
		{
			strcat ( intTxt, &grpSym );
		}

		// Append digit to integer-portion text
		strcat ( intTxt, &curDigit );
	}

	// Create decimal portion
	if ( decimalVal > 0 )
	{
		long long decBuf = (long long)round( decimalVal * pow ( 10, places ));	// 

		sprintf ( decTxt, "%lld", decBuf );	// Transfer formatted decimal to string
	}
	else
	{
		for ( int i = 0; i < places; i++ )
		{
			strcat ( decTxt, "0" );
		}
	}

	// Return formatted number
	// Create sign portion
	if ( isNeg )
	{
		strcat ( outNum, "-" );
	}
	strcat ( outNum, intTxt);
	strcat ( outNum, "." );
	strcat ( outNum, decTxt );
	return outNum;
}
