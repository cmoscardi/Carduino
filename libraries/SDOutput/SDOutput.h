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
 * $Rev: 90 $:   
 * $Author: irvined $: 
 * $Date: 2011-07-28 14:01:25 -0400 (Thu, 28 Jul 2011) $:  

*/

#ifndef SDOutput_h
#define SDOutput_h
#include <config.h>
#ifdef ENABLE_SD_OUTPUT
#include "WProgram.h"
#include "Debug.h"
#include "SD.h"
#include "Message.h"
#include "Logger.h"
	#ifndef SD_ACTIVE_PIN
		#error Define SD_ACTIVE_PIN to the pin that will go high when the SD module is writing to a file.
	#endif

/**
 * A logger implementation that writes data to SD cards using the SD library.
 */
class SDOutput
{
	/**
	 * If the logger was able to open a file on an SD Card, it becomes active.
	 */
    static bool active;
	//! The open file object where the file is being written to.
    static File _File;
    public:
        static bool begin();
        static bool log(Message &msg);
        static bool flush();
};


#endif
#endif

