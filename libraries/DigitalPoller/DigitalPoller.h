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
 * $Rev: 89 $   
 * $Author: irvined $ 
 * $Date$  

*/


#ifndef DigitalPoller_h
#define DigitalPoller_h


#include <config.h>

#ifdef ENABLE_DIGITAL_POLLER

#ifndef DIGITAL_PINS
	#error DIGITAL_PINS is not defined.
#endif

#include "WProgram.h"
#include "Message.h"
#include "Logger.h"

/**
 * The digital poller reports the state of digital pins each run
 * each pin in the list of DIGITAL_PINS is checked, and a log message
 * created for each pin.
 * 
 * DIGITAL_PINS must be defined in config.h, it is expected to be a list 
 * of pins that will be polled.  The default behavior is to hold the pin
 * low, however in many circumstances it is desirable to hold the pin high, 
 * for example when using a transistor as part of a voltage reduction 
 * circuit.  
 *
 * Subsequently, INVERT_DIGITAL_PINS can be used to set specific pins high
 * these pins should be a subset of DIGITAL_PINS, however no checks are 
 * made.
 * 
 * The value of the message is set to the value of the pin regardless of
 * whether the pin is inverted. 
 */
class DigitalPoller
{
    public:
        static bool begin();
		static bool poll();
};

#endif
#endif


