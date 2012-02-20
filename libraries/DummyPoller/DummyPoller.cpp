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
#ifdef ENABLE_DUMMY_POLLER
#include "WProgram.h"
#include "DummyPoller.h"

//! Records how often the poller has been called.
int DummyPoller::called;

//! Initializes the poller by setting called to zero.
bool DummyPoller::begin(){
	called=0;
}

/** Increments called by one, and logs two messages: Dummy.TimesCalled and 
 * Dummy.Uptime.
 */
bool DummyPoller::poll()
{
	Message m;

	m.units="Times";
	m.nameSpace="Dummy.TimesCalled";
	m.value=called++;
	Logger::log(m);

	m.units="Milliseconds";
	m.nameSpace="Dummy.Uptime";
	m.value=millis();
	Logger::log(m);
}
#endif

