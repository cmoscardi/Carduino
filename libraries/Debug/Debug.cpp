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
 * $Rev: 86 $   
 * $Author: irvined $
 * $Date$

*/

#include <config.h>
#include "WProgram.h"
#include "Debug.h"

void debug(int level, String message){
	if (level<=DEBUG_LEVEL){
		message="# " + message;
		switch (level){
			case FATAL:
				message = "# FATAL: " + message;
				break;
			case ERROR:
				message = "# ERROR: " + message;
				break;
			case WARN:
				message = "#  WARN: " + message;
				break;
			case INFO:
				message = "#  INFO: " + message;
				break;
			case DEBUG: 
				message = "# DEBUG: " + message;
				break;
			case TRACE:
				message = "# TRACE: " + message;
				break;
			default : 
				message = "# BROKE: " + message;
		}
		Serial.println(message);
	}
}


