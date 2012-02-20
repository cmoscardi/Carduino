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
 * $Rev: 67 $
 * $Author: irvined $
 * $Date: 2011-06-28 15:13:55 -0400 (Tue, 28 Jun 2011) $  

*/

#include "WProgram.h"
#include "Debug.h"
#include "NMEA.h"

NMEA n;
void setup(){
	Serial2.begin(4800);
	Serial.begin(115200);
}

void loop(){
	while (Serial2.available()){
		if (n.addChar(Serial2.read())){
			if (n.validFix()){
			    Serial.print("getTime() ");
				Serial.println( n.getTime());
			
			    Serial.print("getLatitude() ");
			    Serial.println( n.getLatitude());
			
			    Serial.print("getLongitude() ");
				Serial.println( n.getLongitude());

				Serial.print("getSpeed() ");
				Serial.println( n.getSpeed());

				Serial.print("getCourse() ");
				Serial.println( n.getCourse());

				Serial.print("getDate() ");
				Serial.println( n.getDate());
			}
		}
	}
}
