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
 * @brief Header file for main executable manager.
 *
 */

#ifndef ROTORXOR_MAIN_H
#define ROTORXOR_MAIN_H

#include <boost/program_options.hpp>

#include <string>

/*
 * COMMAND LINE OPTIONS
 */
namespace po = boost::program_options;
const std::string OPTS = "hlv";							///< Available command line options.
static po::options_description desc("Options");

/*
 * FUNCTION PROTOTYPES
 */
namespace RotorXor
{
	int parseArg( const int, char* [] );					///< Parse command line arguments if present.
	int mainLoop( const int = -1 );						///< Primary execution loop.
	void show_usage( const int = 0 );					///< Print command-line usage to screen and exit.
}

#endif /* ROTORXOR_MAIN_H */
