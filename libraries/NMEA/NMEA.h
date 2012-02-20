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
 * $Rev: 64 $
 * $Author: irvined $
 * $Date: 2011-06-27 12:17:25 -0400 (Mon, 27 Jun 2011) $

*/


#ifndef NMEA_H
#define NMEA_H
#include "WProgram.h"
#include "Debug.h"



class NMEA{
	String getField(int field);
	char sumMsg(String &message);
	String readSentence;
	String activeSentence;
	int state;
	public:
		bool addChar(char c);
		bool validFix();
		String getTime();
		char fixType();
		String getLatitude();
		String getLongitude();
		String getSpeed();
		String getCourse();
		String getDate();
};



#endif
