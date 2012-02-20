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
#ifdef ENABLE_ITG3200_POLLER
#include "ITG3200Poller.h"

//! Records how often the poller has been called.
int ITG3200Poller::called;
bool ITG3200Poller::active;
ITG3200 ITG3200Poller::gyro;

/**
 * Initializes the poller by setting called to zero and initialises
 * the itg3200 library.
 */
bool ITG3200Poller::begin(){
	called=0;
	active=false;
	gyro.begin(ITG3200_ADDRESS);
}

/** 
 * Queries the itg3200 for the X, Y, and Z rates of change and the temperature
 * of the itg3200 board using the onboard temperature sensor.
 */
bool ITG3200Poller::poll()
{
	Message m;

	m.units="Degrees*1000/Second";
	m.nameSpace="Gyro.ITG3200.X";
	m.value=int(gyro.getX()*1000);
	Logger::log(m);

	m.units="Degrees*1000/Second";
	m.nameSpace="Gyro.ITG3200.Y";
	m.value=int(gyro.getY()*1000);
	Logger::log(m);

	m.units="Degrees*1000/Second";
	m.nameSpace="Gyro.ITG3200.Z";
	m.value=int(gyro.getZ()*1000);
	Logger::log(m);

	m.units="Degrees Celsius*1000";
	m.nameSpace="Gyro.ITG3200.Temperature";
	m.value=int(gyro.getTemperature()*1000);
	Logger::log(m);
}
#endif

