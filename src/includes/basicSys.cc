/********************************************************************************
 *                                                                              *
 * Various helper functions.                                                    *
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
 * @brief Source code for various helper functions.
 *
 */
#include "basicSys.hh"

#include "../constants.hh"

#include <sysexits.h>
#include <unistd.h>

#include <cstring>
#include <ctime>
#include <iostream>
#include <string>

/********************************************************************************
 * CLEAR INPUT/OUTPUT - RETURN TYPE: VOID
 ********************************************************************************/
/**
 * Makes OS-specific system call to clear the screen.
 */
void
clearScreen( void )
{
	// Clear the screen
	system( "clear" );
}

/**
 * Clear the cin buffer.
 */
void
clearBuffer( void )
{
	std::cin.clear();
	std::cin.ignore();
}


/*******************************************************************************
 * PAUSE PROGRAM EXECUTION - RETURN TYPE: VOID
*******************************************************************************/
/**
 * Sleep for a given time interval.
 *
 * @param sleepTime Number of seconds to sleep.
 */
void
pauseTime( int sleepTime )
{
	usleep(sleepTime * 1000000);
}

/**
 * Press [ENTER] to continue...
 *
 * @param prompt The prompt to present the user with.
 * DEFAULT: "Press [ENTER] to continue..."
 */
void
pauseKey( const char* prompt )
{
	printf("%s", prompt);
	std::cin.ignore(( std::numeric_limits<std::streamsize>::max )(),'\n');
}

/*******************************************************************************
	STRING FORMATTING AND MANIPULATION - RETURN TYPE: STRING
*******************************************************************************/
/**
 * A version of the printf which returns a string object.  The function is
 * identical to @c printf.
 */
std::string
rprintf( const char* format, ... )
{
	char buffer[ 127 ];	// Create string buffer

	va_list args;	
	va_start( args, format );
	vsnprintf( buffer, sizeof( buffer ), format, args );
	va_end( args );
	
	return std::string( buffer );
}

/********************************************************************************
 * BASIC INFORMATION - RETURN TYPE: STRING
 ********************************************************************************/
/**
 * Generate timestamp
 *
 * @param format The format to use for the timestamp.
 * DEFAULT: "%Y-%m-%dT%H:%M:%S%z"
 *
 * @return formatted timestamp
 */
std::string
genTimeStamp( const std::string format )
{
	// Retrieve number of seconds since 1970-01-01T00:00:00-0000
	time_t unixtime;
	time( &unixtime );

	// Create tm data structure, and populate with local time
	struct tm * timeinfo;
	timeinfo = localtime( &unixtime );

	// Create character buffer to hold current time
	const size_t buffSize = 25;
	char buff[ buffSize ];

	// Set timestamp format to %Y-%m-%dT%H:%M:%S%z

	// Convert data in struct tm into string format based on format[]
	strftime( buff, sizeof( buff ), format.c_str(), timeinfo );

	std::string str( buff );

	return str;
}

/**
 * Prints an error message to stderr.
 *
 * @param errLvl A number representing the error.
 * @param errMsg A message describing the nature of the error.
 */
void
printError( const int errLvl, const char* errMsg, ... )
{
	char errLvlName[ 16 ];
	char msgBuf[ 256 ] = "\0";
	switch ( errLvl ) {
		case EX_USAGE:
		case EX_DATAERR:
		case EX_NOUSER:
		case EX_NOHOST:
		case -1:
			strcpy ( errLvlName, "NOTICE" );
			break;
		case EX_NOINPUT:
		case EX_CANTCREAT:
		case EX_TEMPFAIL:
		case EX_PROTOCOL:
		case EX_NOPERM:
		case EX_CONFIG:
		case -2:
			strcpy ( errLvlName, "WARNING" );
			break;
		case EX_UNAVAILABLE:
		case EX_OSERR:
		case EX_OSFILE:
		case EX_IOERR:
			strcpy ( errLvlName, "ERROR" );
			break;
		case EX_SOFTWARE:
			strcpy ( errLvlName, "BUG" );
			break;
		default:
			fprintf ( stderr,  "*** BUG - Invalid errLvl %d for debugging.\n", errLvl );
			endProg ( EX_SOFTWARE );
			break;
	}

	va_list errArgs;
	va_start ( errArgs, errMsg );
	vsnprintf( msgBuf, sizeof ( msgBuf ), errMsg, errArgs );
	va_end ( errArgs );

	fprintf ( stderr, "*** %s: %s\n", errLvlName, msgBuf );

	if ( errLvl >= 0 && errLvl != EX_USAGE )
	{
		endProg ( errLvl );
	}
#ifdef USAGE_AVAIL
	else if ( errLvl == EX_USAGE )
	{
		show_usage ( errLvl );
	}
#endif /* USAGE_AVAIL */
}

/**
 * Print the program's version and copyright information to the screen.
 */
void
show_version()
{
	std::cout << PROGVER << std::endl;
	std::cout << "Copyright (C) 2018 " << PROGRAMMER_NAME << std::endl;
	std::cout << "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>" << std::endl;
}

/**
 * Print basic license information to the screen.
 */
void
show_lic_notice()
{
	printf( "This is free software, and you are welcome to redistribute it under certain conditions.\n" );
	printf( "This program comes with ABSOLUTELY NO WARRANTY, to the extent permitted by law.\n" );
}

/**
 * Show the program banner.
 */
void
show_banner()
{
	show_version();
	show_lic_notice();
}

/**
 * Print additional license information to the screen.
 */
void
show_license()
{
	show_version();
	std::cout << std::endl;
	show_copying();
	show_warranty();
	show_gpl();
}

/**
 * Prints source-code modification and redistribution information to the screen.
 */
void
show_copying()
{
	printf( "This program is free software: you can redistribute it and/or modify\n" );
	printf( "it under the terms of the GNU General Public License as published by\n" );
	printf( "the Free Software Foundation, either version 3 of the License, or\n" );
	printf( "(at your option) any later version.\n" );
	std::cout << std::endl;
}

/**
 * Prints detailed information about the warranty, or lack thereof, to the screen.
 */
void
show_warranty()
{
	printf( "This program is distributed in the hope that it will be useful,\n" );
	printf( "but WITHOUT ANY WARRANTY; without even the implied warranty of\n" );
	printf( "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n" );
	printf( "GNU General Public License for more details.\n" );
	std::cout << std::endl;
}

/**
 * Print information about obtaining the text of the GPL license to the screen.
 */
void
show_gpl()
{
	printf( "You should have received a copy of the GNU General Public License\n" );
	printf( "along with this program.  If not, see <https://www.gnu.org/licenses/>.\n" );
	std::cout << std::endl;
}

/**
 * Prints copyright information to the screen, then exits the program.
 *
 * @param exitCode Exit code for program.
 */
void
endProg ( int exitCode )
{
	exit ( exitCode );
}
