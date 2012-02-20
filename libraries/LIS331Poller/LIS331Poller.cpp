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
 * $Rev: 92 $
 * $Author: irvined $
 * $Date$

*/


#include <config.h>
#ifdef ENABLE_LIS331_POLLER
#include <Debug.h>
#include "WProgram.h"
#include "LIS331Poller.h"



//! The LIS331 Device interface
LIS331 LIS331Poller::lis;
//! When set to true, a LIS331 is responding.
bool LIS331Poller::active;
//! The number of iterations that have pased with the device offline.
byte LIS331Poller::timeouts;


/**
 * Configures the LIS331 device for use with the logger. First powers
 * up the device, the default state is off.  Then enable X, Y, and Z 
 * axes.
 *
 * If any steps in the initialization fail, the poller goes inactive.
 *
 */
bool LIS331Poller::begin(){
	bool status;
	Serial.println("START LIS331");
	status=true;
	timeouts=0;

	if(!lis.setPowerStatus(LR_POWER_NORM)){
		debug(ERROR, 
				"Set Power Status NORM failed during LIS331 Initialization");
		status=false;
	}


	if (!lis.setXEnable(true)){
		debug(ERROR,
				"Set X Enable failed during LIS331 Initialization");
		status=false;
	}
	
	if(!lis.setYEnable(true)){
		debug(ERROR,
				"Set YEnable failed during LIS331 Initialization");
		status=false;
	}
	if(!lis.setZEnable(true)){
		debug(ERROR,
				"Set Z Enable failed during IS331 Initialization");
		status=false;
	}

	active=status;
	return status;
}

/**
 * Queries the LIS331 for the values on all axis, logs the values.  If the 
 * poller is active, then the LIS331 is queried for the values of the X, Y and
 * Z axes, and the values logged.
 * 
 * This produces three log messages:
 *  "Accelerometer.LIS331.X"
 *  "Accelerometer.LIS331.Y"
 *  "Accelerometer.LIS331.Z"
 */
bool LIS331Poller::poll(){
	if (!active){
		return false;
	}
	Message m;
	int16_t val;
	m.units="mG";
	
	lis.getXValue(&val);
	m.nameSpace="Accelerometer.LIS331.X";
	m.value=val;
	Logger::log(m);

	lis.getYValue(&val);
	m.nameSpace="Accelerometer.LIS331.Y";
	m.value=val;
	Logger::log(m);

	lis.getZValue(&val);
	m.nameSpace="Accelerometer.LIS331.Z";
	m.value=val;
	Logger::log(m);

}
#endif

