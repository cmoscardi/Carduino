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

#include <config.h>
#ifdef ENABLE_ANALOG_POLLER
#include "WProgram.h"
#include "AnalogPoller.h"



/**
 * Configures the analog input pins for use.  Configures the external 
 * reference voltage if required.
 */
bool AnalogPoller::begin(){
	#ifndef NO_ANALOG_EXTERN_REF
		analogReference(EXTERNAL);
	#endif
}

/* 
 * Queries each in in ANALOG_PINS and logs the value.  The value is 
 * logged as an integer between 0 and 1023, where 0, is 0v, and 1023 is 5v.
 */
bool AnalogPoller::poll()
{
	int pins[]={ANALOG_PINS};
	int numPins=sizeof(pins)/sizeof(int);
	Message m;
	m.units="Volts*5/1023";
	int i;			    
	for (i=0; i<numPins; i++){
		m.nameSpace=String("AnalogInput.Pin")+String(pins[i]);
		m.value=String(analogRead(pins[i]));
		Logger::log(m);
	}
}
#endif

