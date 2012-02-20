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

#ifndef MSPoller_h
#define MSPoller_h
#ifdef ENABLE_MS_POLLER

#include <config.h>
#include "WProgram.h"
#include "Message.h"
#include "MegaSquirt.h"
#include "Logger.h"
#include "Debug.h"

#ifndef MSP_WAIT_TIME
	#error MSP_WAIT_TIME not defined.
#endif
#ifndef MS_STATUS_PIN
	#error MS_STATUS_PIN not defined.
#endif



/**
 * Queries the megasquirt and logs each value retrieved.  The megasquirt device
 * is connected via a serial device, CAN style commands are sent over the serial
 * line and decoded by the MegaSquirtData object.
 *
 * When successful, each metric is logged as a message to the logging system.
 *
 */
class MSPoller
{
	static bool active;//< when active, the megasquirt is online.
	static byte timeouts;//< The number of times since the last attempt to poll.
	static MegaSquirtData d;//< Megasquirt device
	static void systemState();
	static void keyMetrics();
	static void secondaryMetrics();
	static void afrMetrics();
	static void correctionMetrics();
    public:
        static bool begin();
		static bool poll();
};

#endif


#endif

