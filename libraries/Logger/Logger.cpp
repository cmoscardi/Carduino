/* Copyright 2011 David Irvine
 * 
 * This file is part of Loguino
 *
 * Loguino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Loguino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Loguino.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * $Rev: 92 $:   
 * $Author: irvined $: 
 * $Date: 2011-07-31 16:10:04 -0400 (Sun, 31 Jul 2011) $:  

*/


#include <config.h>
#include "WProgram.h"
#include "Logger.h"


byte Logger::flushCount;

//! Sets up the logger, by calling begin on all attached loggers.
void Logger::begin()
{
	flushCount=0;


#ifdef ENABLE_SERIAL_OUTPUT
	SerialOutput::begin();
#endif
#ifdef ENABLE_SD_OUTPUT
	SDOutput::begin();
#endif
}


//! Sends the supplied message object to each logger attached.
//! @param msg - The Message object to log.
void Logger::log(Message &msg)
{
	if (flushCount++ > LOGGER_FLUSH_MAX){
		#ifdef ENABLE_SERIAL_OUTPUT
			debug(INFO, "Logger::log: Flush count reached, flushing SerialOutput");
			SerialOutput::flush();
		#endif
		#ifdef ENABLE_SD_OUTPUT
			debug(INFO, "Logger::log: Flush count reached, flushing SDOutput");
			SDOutput::flush();
		#endif

		flushCount=0;
	}

	#ifdef ENABLE_SERIAL_OUTPUT
		SerialOutput::log(msg);
	#endif
	#ifdef ENABLE_SD_OUTPUT
		SDOutput::log(msg);
	#endif

}

