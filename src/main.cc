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
 * @brief Source code for main executable manager.
 *
 */
#include "main.hh"

#include "constants.hh"

#include "core/interactive.hh"

#include "includes/basicSys.hh"

#include <sysexits.h>
#include <unistd.h>



#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

/**
 * @param argc Number of command line arguments.
 * @param argv Array containing command line arguments.
 * @return Exit code.
 */
int
main( const int argc, char* argv[])
{
	int exitVal = RotorXor::parseArg( argc, argv );

	if ( exitVal < 0 )
	{
		show_banner();
		pauseKey();
		exitVal = RotorXor::mainLoop( exitVal );
		std::cout << std::endl;
		show_version();
	}
	endProg();
}

/**
 * @param argc Number of command line arguments.
 * @param argv Array containing command line arguments.
 */
int
RotorXor::parseArg( const int argc, char* argv[])
{
	std::vector< std::string > options( argv + 1, argv + argc );
	int exitVal = 0;
	desc.add_options()
		( "help,h", "Show help and exit.")
		( "license,l", "Show license information and exit." )
		( "version", "Show version and exit." )

		( "ascii,a", "Input/output is Base64-encoded.")
		( "interactive,I", "Launch interactive interface." )
		( "verbose,v", "Verbose output." )

		( "keyfile,k", po::value< std::string >(), "Filename of rotorxor key." )
		( "keydata", po::value< std::string >(), "Base64 of rotorxor key." )
		( "rotors,r", po::value< int >(), "Default number of rotors." )
	;

	po::variables_map vm;

	po::parsed_options parsed = po::command_line_parser(options).allow_unregistered().options( desc ).run(); 
	po::store( parsed, vm );
	po::notify( vm );

	std::vector<std::string> unrecognizedOptions = po::collect_unrecognized( parsed.options, po::include_positional ); 

	if ( size_t unknowns = unrecognizedOptions.size())
	{
		std::cerr << "Invalid command option:" << std::endl;
		for ( int i = 0; i < unknowns; i++ )
		{
			std::cout << unrecognizedOptions[ i ] << " ";
		}
		std::cout << std::endl;
		show_usage( EX_USAGE );
	}

	if ( vm.count( "help" ))
	{
		show_usage();
		exitVal = 0;
		return exitVal;
	}

	if ( vm.count( "license" ))
	{
		show_license();
		exitVal = 0;
		return exitVal;
	}

	if ( vm.count( "version" ))
	{
		show_banner();
		exitVal = 0;
		return exitVal;
	}

	if ( vm.count( "interactive" ))
	{
		exitVal = -1;
		return exitVal;
	}

	return exitVal;
}

/**
 * Main program loop.
 *
 * @param entryVal Negative value enters interactive mode.  Value equal to or
 * greater than 0 will skip interactive mode be returned to the main function as
 * a program exit value.
 *
 * @return Program exit value.
 */
int
RotorXor::mainLoop( const int entryVal )
{
	int exitVal = entryVal;
	exitVal = doMainMenu( -1 );
	return exitVal;
}

/**
 * Print command-line usage, then exit with possible error number.
 *
 * @param errnum Exit value for program after showing usage.
 */
void
RotorXor::show_usage ( const int errnum )
{
#define USAGE_AVAIL
	show_lic_notice();

	std::cerr << "Usage: " << PROGEXEC << " [options]" << std::endl;

	std::cerr << desc << std::endl;
	exit ( errnum );
}
