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
 * $Rev: 71 $
 * $Author: irvined $
 * $Date: 2011-06-28 16:34:19 -0400 (Tue, 28 Jun 2011) $

*/
#include "WProgram.h"
#include "Debug.h"
#include "NMEA.h"
#include "Test.h"



void setup(){
	Serial.begin(9600);

	String message;
	
	message="$GPRMC,081836,A,3751.65,S,14507.36,E,000.0,360.0,130998,011.3,E*62\r\n";
	
	Serial.println("Trying valid sentance.");

	NMEA n;
	int i=0;
	for (i=0;i<message.length();i++){
		if(n.addChar(message.charAt(i))){
		Serial.println("Message validates.");
		}
	}

	test (n.validFix(), "validFix()");
	test ( ( n.getTime()=="081836"), "getTime()");
	test ( ( n.getLatitude()=="3751.65S"), "getLatitude()");
	test ( ( n.getLongitude()=="14507.36E"), "getLongitude()");
	test ( ( n.getSpeed()=="000.0"), "getSpeed()");
	test ( ( n.getCourse()=="360.0"), "getCourse()");
	test ( ( n.getDate()=="130998" ), "getDate()");
}




void loop(){}
