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
 * $Rev: 86 $:   
 * $Author: irvined $: 
 * $Date: 2011-07-26 15:15:22 -0400 (Tue, 26 Jul 2011) $:  

*/


#ifndef Logger_h
#define Logger_h


#include "config.h"
#include "WProgram.h"
#include "Message.h"
#include "SerialOutput.h"
#include "SDOutput.h"
#include "Debug.h"

#ifndef LOGGER_FLUSH_MAX
	#error "LOGGER_FLUSH_MAX must be defined as an integer value."
#endif

class Logger
{
	static byte flushCount;
	public:
		static void begin();
		static void log(Message &msg);
};




#endif

