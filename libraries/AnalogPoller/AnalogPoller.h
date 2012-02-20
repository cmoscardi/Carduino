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
 * $Rev: 90 $   
 * $Author: irvined $ 
 * $Date$  

*/

#ifndef AnalogPoller_h
#define AnalogPoller_h


#include <config.h>

#ifdef ENABLE_ANALOG_POLLER
	#ifndef ANALOG_PINS
		#error ANALOG_PINS is not defined.
	#endif

	#include "WProgram.h"
	#include "Message.h"
	#include "Logger.h"
	/**	
	 * The analog logs the analog value of pins specified in ANALOG_PINS.
	 * It can be configured to use an external reference voltage, this
	 * is the default, behavior.
	 *
	 * Each pin in ANALOG_PINS is queried each poll run, and the value 
	 * logged as a message within the AnalogInput namespace.
	 *
	 * Pin values are in the range of 0-1023, where 0 is 0v, and 1023 is 5v.
	 */
	class AnalogPoller
	{
	    public:
	        static bool begin();
			static bool poll();
	};

#endif
#endif


