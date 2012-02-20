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
#include <Poller.h>

/* 
 * Initializes the poller layer, so that all subsystems can be polled
 * at a later time. 
 *
 * Iterates through each enabled poller and call the begin() method on them.
 */
void Poller::begin(){
	#ifdef ENABLE_MS_POLLER
		MSPoller::begin();
	#endif
	#ifdef ENABLE_LIS331_POLLER
		LIS331Poller::begin();
	#endif
	#ifdef ENABLE_DUMMY_POLLER
		DummyPoller::begin();
	#endif
	#ifdef ENABLE_GPS_POLLER
		GPSPoller::begin();
	#endif
	#ifdef ENABLE_DIGITAL_POLLER
		DigitalPoller::begin();
	#endif
	#ifdef ENABLE_ANALOG_POLLER
		AnalogPoller::begin();
	#endif
	#ifdef ENABLE_ITG3200_POLLER
		ITG3200Poller::begin();
	#endif
}

/**
 * Responsible for polling all connected hardware and generating log messages.
 * 
 * Iterates through each enabled poller, and calls the poll() method.
 */
void Poller::poll()
{
	#ifdef ENABLE_MS_POLLER
		MSPoller::poll();
	#endif
	#ifdef ENABLE_LIS331_POLLER
		LIS331Poller::poll();
	#endif
	#ifdef ENABLE_DUMMY_POLLER
		DummyPoller::poll();
	#endif
	#ifdef ENABLE_GPS_POLLER
		GPSPoller::poll();
	#endif
	#ifdef ENABLE_DIGITAL_POLLER
		DigitalPoller::poll();
	#endif
	#ifdef ENABLE_ANALOG_POLLER
		AnalogPoller::poll();
	#endif
	#ifdef ENABLE_ITG3200_POLLER
		ITG3200Poller::poll();
	#endif
}
