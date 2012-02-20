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

#include <config.h>
#ifdef ENABLE_DIGITAL_POLLER
#include "WProgram.h"
#include "DigitalPoller.h"



/**
 * Configures the poller module ready to actually read the values by
 * iterating through each DIGITAL_PIN and setting its mode to INPUT
 * and its value to LOW.
 * 
 * For each INVERTED_DIGITAL_PIN, pulls the value high.
 */
bool DigitalPoller::begin(){
	// pins - an array of pin numbers to check the state of
	int pins[]={DIGITAL_PINS};
	// invPins - an array of pin numbers that should be held high
	int invPins[]={INVERT_DIGITAL_PINS};
	// numPins - The number of pins in total.
	int numPins=sizeof(pins)/sizeof(int);
	// numIPins - the number of inverted pins.
	int numIPins=sizeof(invPins)/sizeof(int);

	// Iterate through each pin, set it to an input pin.
	// Hold the pin LOW.
	int i;
	for ( i=0; i<numPins; i++){
		pinMode(pins[i],INPUT);
		digitalWrite(pins[i], LOW);
	}

	// For each pin marked inverted, hold it HIGH.
	for(i=0; i<numIPins; i++){
		digitalWrite(invPins[i], HIGH);
	}
}

/**
 * Reads the value of each digital pin specified and sends a message
 * with the appropriate value.
 */
bool DigitalPoller::poll()
{
	// pins - array of pin numbers to check.
	int pins[]={DIGITAL_PINS};
	// numPins - total number of pins to check.
	int numPins=sizeof(pins)/sizeof(int);
	// m - message object containing each message.
	Message m;
	m.units="Bool";
	int i;			    
	// For each pin, set the nameSpace, the value, then send the 
	// message.
	for (i=0;i<numPins;i++){
		m.nameSpace=String("DigitalInput.Pin")+String(pins[i]);
		m.value=digitalRead(pins[i]) ? "HIGH":"LOW";
		Logger::log(m);
	}
}
#endif

