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

#ifndef DummyPoller_h
#define DummyPoller_h


#include <config.h>

#ifdef ENABLE_DUMMY_POLLER
#include "WProgram.h"
#include "Message.h"
#include "Logger.h"

/**
 * Logs a series of useless log messages for testing purposes.  Each polling 
 * run it generates two log messages, the first: Dummy.TimesCalled equates to 
 * the number of poll runs made. The second: Dummy.Uptime logs the uptime
 * in millis since the arduino was started.
 *
 * This is primarily meant for testing the output system, as it enables data
 * to be sent to the loggers without any sensors connected.  It can also be
 * used for profiling as you can work out the time per poll based on the 
 * two metrics provided.
 */
class DummyPoller
{
	static int called;
    public:
        static bool begin();
		static bool poll();
};

#endif
#endif


