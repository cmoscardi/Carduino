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
 * $Rev: 90 $:   
 * $Author: irvined $: 
 * $Date: 2011-07-28 14:01:25 -0400 (Thu, 28 Jul 2011) $:  

*/


#include <config.h>
#ifdef ENABLE_SERIAL_OUTPUT
#include "WProgram.h"
#include "Logger.h"
#include <SerialOutput.h>

//! When the serial device is online, active is set to true.
bool SerialOutput::active;

//! Flushes the serial buffer.
bool SerialOutput::flush(){
    if (active){
        SO_SERIAL_PORT.flush();
		return true;
    }
	return false;
}

/**
 * Initializes the SerialOutput module by setting the BAUD rate on the serial 
 * port. Sets active to true.
 */
bool SerialOutput::begin()
{
    SO_SERIAL_PORT.begin(SO_SERIAL_PORT_SPEED);
    active=true;
    return true;
}


/**
 * Calls the toCSV method on the message and writes the data to the serial 
 * port.
 */
bool SerialOutput::log(Message &msg){
    if (!active){
        return false;
    }
    SO_SERIAL_PORT.println(msg.toCSV());
	return true;
}
#endif

